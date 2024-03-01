#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "FileHandler.hpp"
#include "InvalidOpcodeException.hpp"
#include "Memory.hpp"

class CPU {
private:
    // Helper methods to manage and update flags
    void setFlagZ(bool set);
    void setFlagN(bool set);
    void setFlagH(bool set);
    void setFlagC(bool set);

    bool getFlagZ() const;
    bool getFlagN() const;
    bool getFlagH() const;
    bool getFlagC() const;

    uint32_t getCycles() const;

    // Instruction set methods

    // 8-bit Arithmetic and Logic Instructions
    void adcR8toA(const uint8_t& r8);
    void adcHLtoA();
    void adcN8toA(const uint8_t& n8);
    void addR8toA(const uint8_t& r8);
    void addHLtoA();
    void addN8toA(const uint8_t& n8);
    void andR8toA(const uint8_t& r8);
    void andHLtoA();
    void andN8toA(const uint8_t& n8);
    void cpR8toA(const uint8_t& r8);
    void cpHLtoA();
    void cpN8toA(const uint8_t& n8);
    void decR8(uint8_t& r8);
    void decHL();
    void incR8(uint8_t& r8);
    void incHL();
    void orR8toA(const uint8_t& r8);
    void orHLtoA();
    void orN8toA(const uint8_t& n8);
    void sbcR8fromA(const uint8_t& r8);
    void sbcHLfromA();
    void sbcN8fromA(const uint8_t& n8);
    void subR8fromA(const uint8_t& r8);
    void subHLfromA();
    void subN8fromA(const uint8_t& n8);
    void xorR8withA(const uint8_t& r8);
    void xorHLwithA();
    void xorN8withA(const uint8_t& n8);

    // 16-bit Arithmetic Instructions
    void addR16toHL(const uint16_t& r16);
    void decR16(uint16_t& r16);
    void incR16(uint16_t& r16);

    // Bit Operations Instructions
    void bitU3inR8(uint8_t bit, uint8_t& r8);
    void bitU3inHL(uint8_t bit);
    void resU3inR8(uint8_t bit, uint8_t& r8);
    void resU3inHL(uint8_t bit);
    void setU3inR8(uint8_t bit, uint8_t& r8);
    void setU3inHL(uint8_t bit);
    void swapInR8(uint8_t& r8);
    void swapInHL();

    // Bit Shift Instructions
    void rl(uint8_t& r8);
    void rlHL();
    void rla();
    void rlc(uint8_t& r8);
    void rlcHL();
    void rlca();
    void rr(uint8_t& r8);
    void rrHL();
    void rra();
    void rrc(uint8_t& r8);
    void rrcHL();
    void rrca();
    void sla(uint8_t& r8);
    void slaHL();
    void sra(uint8_t& r8);
    void sraHL();
    void srl(uint8_t& r8);
    void srlHL();

    // Load Instructions
    void ldR8R8(uint8_t& dest, const uint8_t& src);
    void ldR8N8(uint8_t& r8, uint8_t n8);
    void ldR16N16(uint16_t& r16, uint16_t n16);
    void ldHLR8(const uint8_t& r8);
    void ldHLN8(uint8_t n8);
    void ldR8HL(uint8_t& r8);
    void ldR16A(const uint16_t& r16);
    void ldN16A(uint16_t n16);
    void ldhN16A(uint8_t n8);
    void ldhAN16(uint8_t n8);
    void ldhCA();
    void ldhAC();
    void ldHLIA();
    void ldAHLI();
    void ldHLDA();
    void ldAHLD();

    // Jumps and Subroutines
    void callN16(uint16_t n16);
    void callCCN16(bool condition, uint16_t n16);
    void jpHL();
    void jpN16(uint16_t n16);
    void jpCCN16(bool condition, uint16_t n16);
    void jrN16(int8_t n8);
    void jrCCN16(bool condition, int8_t n8);
    void retCC(bool condition);
    void ret();
    void reti();
    void rst(uint8_t vec);
    void push(uint16_t value);
    uint16_t pop();

    // Stack Operations Instructions
    void addHLSP();
    void addSPE8(int8_t e8);
    void decSP();
    void incSP();
    void ldSPN16(uint16_t n16);
    void ldN16SP(uint16_t n16);
    void ldHLSPE8(int8_t e8);
    void ldSPHL();
    void popAF();
    void popR16(uint16_t& r16);
    void pushAF();
    void pushR16(const uint16_t& r16);

    // Miscellaneous Instructions
    void CCF();
    void CPL();
    void DAA();
    void DI();
    void EI();
    void HALT();
    void NOP();
    void SCF();
    void STOP();


    // Game Boy CPU registers
    union {
        struct {
            uint8_t F; // Flag register
            uint8_t A; // Accumulator
        };
        uint16_t AF; // AF register pair
    };

    union {
        struct {
            uint8_t C; // General purpose
            uint8_t B; // General purpose
        };
        uint16_t BC; // BC register pair
    };

    union {
        struct {
            uint8_t E; // General purpose
            uint8_t D; // General purpose
        };
        uint16_t DE; // DE register pair
    };

    union {
        struct {
            uint8_t L; // General purpose
            uint8_t H; // General purpose
        };
        uint16_t HL; // HL register pair
    };

    uint16_t SP; // Stack Pointer
    uint16_t PC; // Program Counter

    uint32_t cyclesCounter; // Cycles counter
    FileHandler fileHandler;
    Memory memory;

public:
    CPU();
    // Constructor
    void executeInstruction(uint8_t opcode); // Execute a single instruction
    uint8_t fetch();
};

#endif
