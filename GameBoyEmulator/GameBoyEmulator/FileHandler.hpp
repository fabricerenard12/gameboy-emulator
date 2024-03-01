#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileHandler {
private:
    std::ifstream romFile;
    std::string title;
    uint8_t cartridgeType;
    uint8_t romSize;
    uint8_t ramSize;

public:
    FileHandler(const std::string& filePath);
    ~FileHandler();

    void readHeader();
    std::vector<uint8_t> getROMData();
    std::string getTitle() const;
    uint8_t getCartridgeType() const;
    uint8_t getRomSize() const;
    uint8_t getRamSize() const;
};

#endif
