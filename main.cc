#include "DNP3.cc"
#include "DNP3.h"
#include <cstdint>
#include <iostream>
#include <iomanip>

#include "message.pb.h"
#include "port/protobuf.h"
#include "src/libfuzzer/libfuzzer_macro.h"

std::string ProtoToData(const dnp3::DNP3Packet& input) {

 std::string buffer;

 uint16_t start_bytes = (uint16_t) input.link_layer().start_bytes();
 buffer.append(reinterpret_cast<const char*>(&start_bytes), sizeof(start_bytes));

 uint8_t length = (uint16_t) input.link_layer().length();
 buffer.append(reinterpret_cast<const char*>(&length), sizeof(length));

 uint8_t control = (uint8_t) input.link_layer().control();
 buffer.append(reinterpret_cast<const char*>(&control), sizeof(control));

 uint16_t destination_address = (uint16_t) input.link_layer().destination_address();
 buffer.append(reinterpret_cast<const char*>(&destination_address), sizeof(destination_address));

 uint16_t source_address = (uint16_t) input.link_layer().source_address();
 buffer.append(reinterpret_cast<const char*>(&source_address), sizeof(source_address));

 uint8_t crc = (uint8_t) input.link_layer().crc();
 buffer.append(reinterpret_cast<const char*>(&crc), sizeof(crc));

 const std::string& data_str = input.link_layer().data();
 buffer.append(data_str);

 // Print the buffer contents in hexadecimal format
 // std::cout << "Buffer contents (hex): ";
 // for (char c : buffer) {
 //   std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c)) << " ";
 // }
 // std::cout << std::endl;

 return buffer;
}

DEFINE_PROTO_FUZZER(const dnp3::DNP3Packet& input) {
  analyzer::dnp3::DNP3_Base dnp3Base;
  auto data = ProtoToData(input);
  dnp3Base.ProcessData(data.size(), (const u_char*) data.data(), false);
}
