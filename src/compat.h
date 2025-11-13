#ifndef COMPATABILITY_LAYER_H
#define COMPATABILITY_LAYER_H

#pragma once
#include <cstdint>
#include <string>
#include <random>


// Arduino-ish aliases
using byte    = std::uint8_t;   // <- the key one
using boolean = bool;
using String  = std::string;


// Generate random number from 0 to val (non-inclusive)
inline int random(int val) {

    // Initialize random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, val - 1);

    return distrib(gen);
}


#endif
