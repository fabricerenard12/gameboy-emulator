#include "Memory.hpp"

Memory::Memory(FileHandler& fileHandler) {
    loadROM(fileHandler);
    ram.resize(0x2000); // Allocating 8KB of RAM as an example
}

uint8_t Memory::read(uint16_t address) const {
    // Read from ROM or RAM based on address
    if (address < rom.size()) {
        return rom[address];
    }
    // Adjust the address for RAM access
    address -= rom.size();
    if (address < ram.size()) {
        return ram[address];
    }
    // Add more conditions for other memory areas as needed
    return 0xFF; // Return a default value if address is out of bounds
}

void Memory::write(uint16_t address, uint8_t data) {
    // Write to RAM or other writable areas based on address
    // ROM is typically read-only, but RAM is writable
    // Adjust the address for RAM access
    address -= rom.size();
    if (address < ram.size()) {
        ram[address] = data;
    }
    // Add conditions for other writable areas as needed
}

void Memory::loadROM(FileHandler& fileHandler) {
    // Assuming FileHandler can provide the ROM data as a vector of uint8_t
    rom = fileHandler.getROMData(); // Implement this method in FileHandler to expose ROM data
}
