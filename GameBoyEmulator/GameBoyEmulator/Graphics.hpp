#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cstdint>
#include <array>
#include "Memory.hpp"

class Graphics {
private:
    Memory& memory; // Reference to the Memory class to access VRAM, OAM, etc.

    std::array<uint8_t, 160 * 144> frameBuffer; // Frame buffer for the display, Gameboy resolution is 160x144

    uint32_t modeClock; // Clock for tracking time spent in current GPU mode
    uint8_t mode; // Current GPU mode

public:
    Graphics(Memory& mem);

    void update(int cycles); // Update graphics based on CPU cycles
    void renderScanline(); // Render a single scanline
};

#endif
