# libnfc-nci-test

Test application to interface libnfc-nci

## Requirements

Get and install the (forked) libnfc-nci library from https://github.com/StarGate01/linux_libnfc-nci/ , which works with the kernel driver from https://github.com/jr64/nxp-pn5xx .

Other requirements are `gcc`, `cmake`, `pkg-config`, and `make` .

## Building

```
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Running

Make sure the libnfc-nci library is properly configured for your chip. Then, execute the test via `./build/src/nci-test` .
