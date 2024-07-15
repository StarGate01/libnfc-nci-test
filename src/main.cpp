#include <cstdint>
#include <cstdio>
#include <semaphore.h>
#include <signal.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <linux_nfc_api.h>


static sem_t sem;
static nfc_tag_info_t tag;
static nfcTagCallback_t tagCb;


void onTagArrival(nfc_tag_info_t *pTag)
{
    tag = *pTag;
    sem_post(&sem);
}

void onTagDeparture(void)
{
    printf("Tag lost\n");
}


void sigint_handler(int s)
{
    printf("Shutting down\n");
    sem_destroy(&sem);
    nfcManager_disableDiscovery();
    nfcManager_deregisterTagCallback();
    nfcManager_doDeinitialize ();
    exit(0);
}

void print_buffer(uint8_t* buf, size_t buf_len)
{
    for(size_t i=0; i < buf_len; i++)
    {
        printf("%02X ", buf[i]);
    }
}

void transmit(uint8_t* tx_buf, size_t tx_len)
{
    printf("Send %ld bytes: ", tx_len);
    print_buffer(tx_buf, tx_len);
    printf("\n");
    uint8_t rx_buf[255];
    size_t rx_len = nfcTag_transceive(tag.handle, tx_buf, tx_len, rx_buf, 255, 1000);
    printf("Received %ld bytes: ", rx_len);
    print_buffer(rx_buf, rx_len);
    printf("\n");
}

int main()
{
    printf("Starting NFC-NCI test app\n");
    sem_init(&sem, 0, 0);

    nfcManager_doInitialize ();
    int fw = nfcManager_getFwVersion();
    printf("NFC hardware ROM: %d, FW: %d.%d\n", (fw >> 16) & 0xFF, (fw >> 8) & 0xFF, fw & 0xFF);
    tagCb.onTagArrival = onTagArrival;
    tagCb.onTagDeparture = onTagDeparture;
    nfcManager_registerTagCallback(&tagCb);
    nfcManager_enableDiscovery(DEFAULT_NFA_TECH_MASK, 1, 0, 0);

    struct sigaction sigint;
    sigint.sa_handler = sigint_handler;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = 0;
    sigaction(SIGINT, &sigint, NULL);

    while(true)
    {
        sem_wait(&sem);

        printf("Tag found!\n");

        printf("UID %d bytes: ", tag.uid_length);
        print_buffer((uint8_t*)tag.uid, tag.uid_length);
        printf("\n");

        if(tag.protocol == NFA_PROTOCOL_ISO_DEP)
        {
            printf("ATS %d bytes: ", tag.param.pa.ats_res_len);
            print_buffer((uint8_t*)tag.param.pa.ats_res, tag.param.pa.ats_res_len);
            printf("\n");
        }
        
        uint8_t select[] = { 0x00, 0xA4, 0x04, 0x00, 0x07, 0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01, 0x00 };
        transmit(select, sizeof(select) / sizeof(uint8_t));

        printf("Reconnecting...\n");
        nfcTag_reconnect();
        printf("Reconnected.\n");

        uint8_t vk_ver[] = { 0x80, 0xF4, 0x99, 0x99, 0x00 };
        transmit(vk_ver, sizeof(vk_ver) / sizeof(uint8_t));

        transmit(select, sizeof(select) / sizeof(uint8_t));
        transmit(vk_ver, sizeof(vk_ver) / sizeof(uint8_t));

        uint8_t select_cc[] = { 0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x03 };
        transmit(select_cc, sizeof(select_cc) / sizeof(uint8_t));
        uint8_t read_cc[] = { 0x00, 0xB0, 0x00, 0x00, 0x0F };
        transmit(read_cc, sizeof(read_cc) / sizeof(uint8_t));
    }
  
    return 0;
}