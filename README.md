# libnfc-nci-test

Test application to interface libnfc-nci

## Requirements

Get and install the libnfc-nci library from https://github.com/NXPNFCLinux/linux_libnfc-nci/ , which works with the kernel driver from https://github.com/jr64/nxp-pn5xx .

Other requirements are `gcc`, `cmake`, `pkg-config`, and `make` .

## Building

```
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Running

Make sure the libnfc-nci library is properly configured for your chip. Then, execute the test via `./build/src/nci-test` .
