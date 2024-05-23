#include "DNP3.cc"

int main() {

    int len = 10;
    const u_char* data = nullptr;
    bool orig = true;

    DNP3_Base dnp3_base;

    bool result = dnp3_base.ProcessData(len, data, orig);

    return 0;
}

