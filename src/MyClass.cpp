#include "MyClass.h"
#include <iostream>

#include "linux_nfc_api.h"

MyClass::MyClass() {
    // Constructor
}

void MyClass::sayHello() {
    nfcManager_doInitialize();

    std::cout << "Hello, World!" << std::endl;
}