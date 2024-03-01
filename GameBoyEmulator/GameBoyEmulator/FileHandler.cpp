#include "FileHandler.hpp"

FileHandler::FileHandler(const std::string& filePath) {
    romFile.open(filePath, std::ios::binary);
    if (!romFile.is_open()) {
        throw std::runtime_error("Failed to open ROM file: " + filePath);
    }
    readHeader();
}

FileHandler::~FileHandler() {
    if (romFile.is_open()) {
        romFile.close();
    }
}

void FileHandler::readHeader() {
    romFile.seekg(0x0134, std::ios::beg);
    char titleBuffer[17] = { 0 };
    romFile.read(titleBuffer, 16);
    title = titleBuffer;

    romFile.seekg(0x0147, std::ios::beg);
    romFile.read(reinterpret_cast<char*>(&cartridgeType), 1);
    romFile.read(reinterpret_cast<char*>(&romSize), 1);
    romFile.read(reinterpret_cast<char*>(&ramSize), 1);
}

std::vector<uint8_t> FileHandler::getROMData() {
    std::vector<uint8_t> data;

    // Ensure the file stream is open and at the beginning
    if (!romFile.is_open()) {
        romFile.open(filePath, std::ios::binary);
    }

    if (romFile.is_open()) {
        // Move to the beginning of the file
        romFile.seekg(0, std::ios::end);
        size_t size = romFile.tellg();
        romFile.seekg(0, std::ios::beg);

        // Resize the vector to the size of the ROM and read the data
        data.resize(size);
        romFile.read(reinterpret_cast<char*>(data.data()), size);

        // It might be a good idea to close the file after reading, or you can leave it open
        // if you plan to read from it again later.
        romFile.close();
    }
    else {
        std::cerr << "Failed to open ROM file: " << filePath << std::endl;
    }

    return data;
}


std::string FileHandler::getTitle() const {
    return title;
}

uint8_t FileHandler::getCartridgeType() const {
    return cartridgeType;
}

uint8_t FileHandler::getRomSize() const {
    return romSize;
}

uint8_t FileHandler::getRamSize() const {
    return ramSize;
}