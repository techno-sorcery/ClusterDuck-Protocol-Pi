#ifndef DUCKPACKET_H_
#define DUCKPACKET_H_

#include "../CdpPacket.h"
// #include "Arduino.h"
#include "DuckUtils.h"
#include "cdpcfg.h"
#include "bloomfilter.h"
// #include <CRC32.h>
#include <array>

/**
 * @brief Use this DUID to send to all PapaDucks
 * 
 */
static std::array<std::byte,8> ZERO_DUID = {std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00},
                                      std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}};

/**
 * @brief Use this DUID to be received by every duck in the network
 * 
 */
static std::array<std::byte,8> BROADCAST_DUID = {std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF},
                                           std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF}};

/**
 * @brief Use this DUID to be received by every duck in the network
 * 
 */
static std::array<std::byte,8> PAPADUCK_DUID = {std::byte{0x50}, std::byte{0x61}, std::byte{0x70}, std::byte{0x61},
                                           std::byte{0x44}, std::byte{0x75}, std::byte{0x63}, std::byte{0x6B}};

/**
 * @brief Encapsulate the protocol packet attributes and operations
 * 
 */
class DuckPacket {

public:

    /**
     * @brief Construct a new Duck Packet object.
     * 
     */
    DuckPacket() {
        buffer.reserve(256);
    }

    /**
     * @brief Construct a new Duck Packet object.
     * 
     * @param duid a duck device unique id
     * @param filter a bloom filter
     */
        DuckPacket(std::array<std::byte,8> duid)
        : duid(duid) {
            buffer.reserve(256);
            }

    ~DuckPacket() {}
    /**
     * @brief Set device Id.
     *
     * @param duid a duck device unique id
     */
    void setDeviceId(std::array<std::byte,8> duid) { this->duid = duid; }

    /**
     * @brief Get device Id.
     *
     * @returns a duck device unique id
     */
    std::array<std::byte,8> getDeviceId() { return this->duid = duid; }
    /**
     * @brief Build a packet from the given topic and provided byte buffer.
     *
     * @param targetDevice the target device DUID to receive the message
     * @param topic a message topic
     * @param app_data a byte buffer that contains the packet data section
     * @returns DUCK_ERR_NONE if the operation was successful, otherwise an error code.
     */
    int prepareForSending(BloomFilter *filter, const std::array<std::byte,8> targetDevice,
                          std::byte duckType, std::byte topic, std::vector<std::byte> app_data);

    /**
     * @brief Update a received packet if it needs to be relayed in the mesh.
     * 
     * @param filter The bloom filter describing what packets have already been seen
     * @param dataBuffer buffer containing the packet data
     * @returns true if the packet needs to be relayed
     * @returns false if the packet does not need to be replayed
     */
    bool prepareForRelaying(BloomFilter *filter, std::vector<std::byte> dataBuffer);
    
    /**
     * @brief Get the Cdp Packet byte array.
     * 
     * @returns a array of bytes representing the cdp packet
     */
    std::vector<std::byte> getBuffer() { return buffer;}

    /**
     * @brief Resets the packet byte buffer.
     *
     */
    void reset() {
      buffer.clear();
    }

    std::byte getTopic() { return buffer[TOPIC_POS]; }

  private: 
    std::array<std::byte,8> duid;
    std::vector<std::byte> buffer;
    static void getUniqueMessageId(BloomFilter * filter, std::array<uint8_t,MUID_LENGTH> &message_id);

};

#endif

