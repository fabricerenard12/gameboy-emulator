#include "Graphics.hpp"

Graphics::Graphics(Memory& mem) : memory(mem), modeClock(0), mode(2) {
    frameBuffer.fill(0); // Initialize the frame buffer with a default value, e.g., 0 for black
}

void Graphics::update(int cycles) {
    // Update the mode clock with the CPU cycles that have passed
    modeClock += cycles;

    switch (mode) {
    case 2: // OAM Read mode, lasts about 80 cycles
        if (modeClock >= 80) {
            modeClock = 0;
            mode = 3;
        }
        break;
    case 3: // VRAM Read mode, lasts about 172 cycles
        if (modeClock >= 172) {
            modeClock = 0;
            mode = 0;
            renderScanline();
        }
        break;
    case 0: // H-Blank, lasts about 204 cycles
        if (modeClock >= 204) {
            modeClock = 0;
            // Move to the next scanline
            // If we've reached the end of the visible scanlines, switch to V-Blank mode
            // Otherwise, go back to OAM Read mode for the next scanline
        }
        break;
    case 1: // V-Blank, lasts about 4560 cycles (10 scanlines)
        if (modeClock >= 456) {
            modeClock = 0;
            // Move to the next scanline
            // If we've finished all V-Blank scanlines, switch back to OAM Read mode
        }
        break;
    }
}

void Graphics::renderScanline() {
    // Here you would read tile data from memory and render it to the frame buffer
    // This is a simplified placeholder implementation
    for (int x = 0; x < 160; ++x) {
        frameBuffer[x] = 1; // Just a placeholder to change the pixel value
    }
}
