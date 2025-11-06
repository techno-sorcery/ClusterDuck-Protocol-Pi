#ifndef COMPATABILITY_LAYER_H
#define COMPATABILITY_LAYER_H

#pragma once
#include <cstdint>
#include <string>

// Arduino-ish aliases
using byte    = std::uint8_t;   // <- the key one
using boolean = bool;
using String  = std::string;

template<typename T = uint32_t>
class Timer {
    public:
        Timer() {}
};


#endif
