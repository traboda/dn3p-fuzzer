#include "DNP3.cc"
#include "DNP3.h"
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

    analyzer::dnp3::DNP3_Base dnp3Base;
    dnp3Base.ProcessData(size, data, false);

    return 0;
}
