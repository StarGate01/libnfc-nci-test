#include <cstdint>
#include <cstdio>

#include "linux_nfc_api.h"


static nfcTagCallback_t g_TagCB;

int main()
{   
    // g_TagCB.onTagArrival = onTagArrival;
    // g_TagCB.onTagDeparture = onTagDeparture;

    nfcManager_doInitialize();
    int fw = nfcManager_getFwVersion();
    uint8_t rom_code_version = (fw >> 16) & 0xFF;
    uint8_t major_version = (fw >> 8) & 0xFF;
    uint8_t minor_version = fw & 0xFF;
    printf("NFC hardware ROM: %d, FW: %d.%d", rom_code_version, major_version, minor_version);

    return 0;
}