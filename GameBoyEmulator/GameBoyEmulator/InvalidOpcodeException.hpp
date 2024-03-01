#ifndef INVALIDOPCODEEXCEPTION_H
#define INVALIDOPCODEEXCEPTION_H

#include <exception>
#include <string>

class InvalidOpcodeException : public std::exception {
private:
    std::string message;

public:
    InvalidOpcodeException(uint8_t opcode) {
        message = "Invalid Opcode Encountered: 0x" + to_hex_string(opcode);
    }

    virtual const char* what() const throw() {
        return message.c_str();
    }

private:
    std::string to_hex_string(uint8_t opcode) {
        //std::stringstream ss;
        //ss << std::hex << static_cast<int>(opcode);
        //return ss.str();
    }
};

#endif
