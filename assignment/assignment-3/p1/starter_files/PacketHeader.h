#ifndef __PACKET_HEADER_H__
#define __PACKET_HEADER_H__

#include <chrono>
#include <sstream>
#include <string>

// number to indicate packet type
enum struct PacketType : unsigned int {
    START = 0,
    END = 1,
    DATA = 2,
    ACK = 3,
};

struct PacketHeader {
    PacketType type;       // 0: START; 1: END; 2: DATA; 3: ACK
    unsigned int seqNum;   // Described below
    unsigned int length;   // Length of data; 0 for ACK packets
    unsigned int checksum; // 32-bit CRC
    char data[0];
};

constexpr auto WTP_MTU = 1500ull - 20 - 8; // structure size per packet
constexpr auto WTP_MDS = WTP_MTU - sizeof(PacketHeader); // data size per packet
constexpr auto WTP_TIMEOUT = std::chrono::milliseconds{500}; // re-transmission timeout

inline std::string to_string(PacketHeader const &hdr) {
    // <type> <seqNum> <length> <checksum>
    auto ret = std::ostringstream{};
    ret << static_cast<unsigned>(hdr.type) << " " << hdr.seqNum << " "
        << hdr.length << " " << hdr.checksum;
    return ret.str();
}

inline std::ostream &operator<<(std::ostream &out, PacketHeader const &p) {
    out << to_string(p);
    return out;
}

#endif
