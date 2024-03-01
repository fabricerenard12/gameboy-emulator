#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>
#include "FileHandler.hpp"

class Memory {
private:
    std::vector<uint8_t> rom; // ROM data loaded from the file
    std::vector<uint8_t> ram; // General purpose RAM

public:
    Memory(FileHandler& fileHandler);

    uint8_t read(uint16_t address) const; // Read a byte from memory
    void write(uint16_t address, uint8_t data); // Write a byte to memory

    void loadROM(FileHandler& fileHandler); // Load ROM data from file
};

#endif
