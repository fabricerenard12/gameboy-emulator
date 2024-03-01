#include "CPU.hpp"

CPU::CPU() : AF(0), BC(0), DE(0), HL(0), SP(0xFFFE), PC(0x0100), cyclesCounter(0), fileHandler("C:\\Users\\fabri\\Downloads\\Super Mario Land (World)\\Super Mario Land (World).gb"), memory(fileHandler) {
    // Initialize CPU state
}

void CPU::setFlagZ(bool set) { 
    if (set) F |= 0x80; else F &= ~0x80;
}

void CPU::setFlagN(bool set) { 
    if (set) F |= 0x40; else F &= ~0x40;
}

void CPU::setFlagH(bool set) { 
    if (set) F |= 0x20; else F &= ~0x20;
}

void CPU::setFlagC(bool set) { 
    if (set) F |= 0x10; else F &= ~0x10;
}

bool CPU::getFlagZ() const { 
    return F & 0x80;
}

bool CPU::getFlagN() const { 
    return F & 0x40;
}

bool CPU::getFlagH() const { 
    return F & 0x20;
}

bool CPU::getFlagC() const { 
    return F & 0x10;
}

uint32_t CPU::getCycles() const { 
    return cyclesCounter;
}

void CPU::adcR8toA(const uint8_t& r8) {
    uint16_t temp = r8 + static_cast<uint8_t>(getFlagC());
    setFlagH(((A & 0xF) + (temp & 0xF)) > 0xF); // Review this

    temp += A;

    setFlagZ((temp & 0xFF) == 0);
    setFlagN(0);
    setFlagC(temp > 0xFF);

    A = temp & 0xFF;
    cyclesCounter += 1;
};

void CPU::adcHLtoA() {
    uint16_t temp = HL + static_cast<uint8_t>(getFlagC());
    setFlagH(((A & 0xF) + (temp & 0xF)) > 0xF);

    temp += A;

    setFlagZ((temp & 0xFF) == 0);
    setFlagN(0);
    setFlagC(temp > 0xFF);

    A = temp & 0xFF;
    cyclesCounter += 2;
}

void CPU::adcN8toA(const uint8_t& n8) {
    uint16_t temp = n8 + static_cast<uint8_t>(getFlagC());
    setFlagH(((A & 0xF) + (temp & 0xF)) > 0xF);

    temp += A;

    setFlagZ((temp & 0xFF) == 0);
    setFlagN(0);
    setFlagC(temp > 0xFF);

    A = temp & 0xFF;
    cyclesCounter += 2;
};

void CPU::addR8toA(const uint8_t& r8) {
    uint16_t result = static_cast<uint8_t>(A) + r8;

    setFlagH(((A & 0xF) + (r8 & 0xF)) > 0xF);
    A = result & 0xFF;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagC(result > 0xFF);
}

void CPU::addHLtoA() {
    uint16_t result = static_cast<uint8_t>(A) + HL;

    setFlagH(((A & 0xF) + (HL & 0xF)) > 0xF);
    A = result & 0xFF;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagC(result > 0xFF);
}

void CPU::addN8toA(const uint8_t& n8) {
    uint16_t result = static_cast<uint8_t>(A) + n8;

    setFlagH(((A & 0xF) + (n8 & 0xF)) > 0xF);
    A = result & 0xFF;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagC(result > 0xFF);
}

void CPU::andR8toA(const uint8_t& r8) {
    A &= r8;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(1);
    setFlagC(0);

    cyclesCounter += 1;
}

void CPU::andHLtoA() {
    A &= HL;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(1);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::andN8toA(const uint8_t& n8) {
    A &= n8;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(1);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::cpR8toA(const uint8_t& r8) {
    uint16_t temp = static_cast<uint16_t>(A) - r8;

    setFlagZ((temp & 0xFF) == 0);
    setFlagN(1);
    setFlagH((A & 0xF) < (r8 & 0xF));
    setFlagC(r8 > A);

    cyclesCounter += 1;
}

void CPU::cpHLtoA() {
    uint16_t temp = static_cast<uint16_t>(A) - HL;

    setFlagZ((temp & 0xFF) == 0);
    setFlagN(1);
    setFlagH((A & 0xF) < (HL & 0xF));
    setFlagC(HL > A);

    cyclesCounter += 2;
}

void CPU::cpN8toA(const uint8_t& n8) {
    uint16_t temp = static_cast<uint16_t>(A) - n8;

    setFlagZ((temp & 0xFF) == 0);
    setFlagN(1);
    setFlagH((A & 0xF) < (n8 & 0xF));
    setFlagC(n8 > A);

    cyclesCounter += 2;
}

void CPU::decR8(uint8_t& r8) {
    bool halfCarryNeeded = (r8 & 0xF) == 0;

    r8--;

    setFlagZ(r8 == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);

    cyclesCounter += 1;
}

void CPU::decHL() {
    bool halfCarryNeeded = (HL & 0xF) == 0;

    HL--;

    setFlagZ(HL == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);

    cyclesCounter += 3;
}

void CPU::incR8(uint8_t& r8) {
    bool halfCarryNeeded = (r8 & 0xF) == 0xF;

    r8++;

    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(halfCarryNeeded);

    cyclesCounter += 1;
}

void CPU::incHL() {
    bool halfCarryNeeded = (HL & 0xF) == 0xF;

    HL++;

    setFlagZ(HL == 0);
    setFlagN(0);
    setFlagH(halfCarryNeeded);

    cyclesCounter += 3;
}

void CPU::orR8toA(const uint8_t& r8) {
    A |= r8;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 1;
}

void CPU::orHLtoA() {
    A |= HL;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::orN8toA(const uint8_t& n8) {
    A |= n8;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::sbcR8fromA(const uint8_t& r8) {
    uint16_t r8_with_carry = r8 + getFlagC();
    bool halfCarryNeeded = (A & 0xF) < (r8_with_carry & 0xF);
    uint16_t result = static_cast<uint16_t>(A) - r8_with_carry;

    setFlagZ((result & 0xFF) == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);
    setFlagC(result > 0xFF);

    A = static_cast<uint8_t>(result);

    cyclesCounter += 1;
}

void CPU::sbcHLfromA() {
    uint16_t HL_with_carry = HL + getFlagC();
    bool halfCarryNeeded = (A & 0xF) < (HL_with_carry & 0xF);
    uint16_t result = static_cast<uint16_t>(A) - HL_with_carry;

    setFlagZ((result & 0xFF) == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);
    setFlagC(result > 0xFF);

    A = static_cast<uint8_t>(result);

    cyclesCounter += 2;
}

void CPU::sbcN8fromA(const uint8_t& n8) {
    uint16_t n8_with_carry = n8 + getFlagC();
    bool halfCarryNeeded = (A & 0xF) < (n8_with_carry & 0xF);
    uint16_t result = static_cast<uint16_t>(A) - n8_with_carry;

    setFlagZ((result & 0xFF) == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);
    setFlagC(result > 0xFF);

    A = static_cast<uint8_t>(result);

    cyclesCounter += 2;
}

void CPU::subR8fromA(const uint8_t& r8) {
    bool halfCarryNeeded = (A & 0xF) < (r8 & 0xF);
    uint16_t result = static_cast<uint16_t>(A) - r8;

    setFlagZ((result & 0xFF) == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);
    setFlagC(result > 0xFF);

    A = static_cast<uint8_t>(result);

    cyclesCounter += 1;
}

void CPU::subHLfromA() {
    bool halfCarryNeeded = (A & 0xF) < (HL & 0xF);
    uint16_t result = static_cast<uint16_t>(A) - HL;

    setFlagZ((result & 0xFF) == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);
    setFlagC(result > 0xFF);

    A = static_cast<uint8_t>(result);

    cyclesCounter += 2;
}

void CPU::subN8fromA(const uint8_t& n8) {
    bool halfCarryNeeded = (A & 0xF) < (n8 & 0xF);
    uint16_t result = static_cast<uint16_t>(A) - n8;

    setFlagZ((result & 0xFF) == 0);
    setFlagN(1);
    setFlagH(halfCarryNeeded);
    setFlagC(result > 0xFF);

    A = static_cast<uint8_t>(result);

    cyclesCounter += 2;
}

void CPU::xorR8withA(const uint8_t& r8) {
    A ^= r8;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 1;
}

void CPU::xorHLwithA() {
    A ^= HL;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::xorN8withA(const uint8_t& n8) {
    A ^= n8;

    setFlagZ(A == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::addR16toHL(const uint16_t& r16) {
    bool halfCarry = ((HL & 0x0FFF) + (r16 & 0x0FFF)) > 0x0FFF;
    HL += r16;

    setFlagN(0);
    setFlagH(halfCarry);
    setFlagC(HL < r16);

    cyclesCounter += 2;
}

void CPU::decR16(uint16_t& r16) {
    r16--;
    cyclesCounter += 2;
}

void CPU::incR16(uint16_t& r16) {
    r16++;
    cyclesCounter += 2;
}

void CPU::bitU3inR8(uint8_t bit, uint8_t& r8) {
    bool bitValue = r8 & (1 << bit);
    setFlagZ(!bitValue);
    setFlagN(0);
    setFlagH(1);

    cyclesCounter += 2;
}

void CPU::bitU3inHL(uint8_t bit) {
    uint8_t value = HL;
    bitU3inR8(bit, value);

    cyclesCounter += 3;
}

void CPU::resU3inR8(uint8_t bit, uint8_t& r8) {
    r8 &= ~(1 << bit);
    cyclesCounter += 2;
}

void CPU::resU3inHL(uint8_t bit) {
    uint8_t value = HL;
    resU3inR8(bit, value);
    //memory.write(HL, value);

    cyclesCounter += 4;
}

void CPU::setU3inR8(uint8_t bit, uint8_t& r8) {
    r8 |= (1 << bit);
    cyclesCounter += 2;
}

void CPU::setU3inHL(uint8_t bit) {
    uint8_t value = HL;
    setU3inR8(bit, value);
    //memory.write(HL, value);

    cyclesCounter += 4;
}

void CPU::swapInR8(uint8_t& r8) {
    r8 = (r8 << 4) | (r8 >> 4);
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);

    cyclesCounter += 2;
}

void CPU::swapInHL() {
    uint8_t value = HL;
    swapInR8(value);
    //memory.write(HL, value);i wanI

    cyclesCounter += 4;
}

// Rotate Left through Carry
void CPU::rl(uint8_t& r8) {
    uint8_t carry = getFlagC();
    setFlagC(r8 & 0x80);
    r8 = (r8 << 1) | carry;
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::rlHL() {
    uint8_t value = memory.read(HL);
    rl(value);
    memory.write(HL, value);
}

// Rotate Left Accumulator
void CPU::rla() {
    rl(A);
    setFlagZ(0);
}

// Rotate Left Circular
void CPU::rlc(uint8_t& r8) {
    setFlagC(r8 & 0x80);
    r8 = (r8 << 1) | (r8 >> 7);
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::rlcHL() {
    uint8_t value = memory.read(HL);
    rlc(value);
    memory.write(HL, value);
}

// Rotate Left Circular Accumulator
void CPU::rlca() {
    rlc(A);
    setFlagZ(0);
}

// Rotate Right through Carry
void CPU::rr(uint8_t& r8) {
    uint8_t carry = getFlagC();
    setFlagC(r8 & 0x01);
    r8 = (r8 >> 1) | (carry << 7);
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::rrHL() {
    uint8_t value = memory.read(HL);
    rr(value);
    memory.write(HL, value);
}

// Rotate Right Accumulator
void CPU::rra() {
    rr(A);
    setFlagZ(0);
}

// Rotate Right Circular
void CPU::rrc(uint8_t& r8) {
    setFlagC(r8 & 0x01);
    r8 = (r8 >> 1) | (r8 << 7);
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::rrcHL() {
    uint8_t value = memory.read(HL);
    rrc(value);
    memory.write(HL, value);
}

// Rotate Right Circular Accumulator
void CPU::rrca() {
    rrc(A);
    setFlagZ(0);
}

// Shift Left Arithmetic
void CPU::sla(uint8_t& r8) {
    setFlagC(r8 & 0x80);
    r8 <<= 1;
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::slaHL() {
    uint8_t value = memory.read(HL);
    sla(value);
    memory.write(HL, value);
}

// Shift Right Arithmetic
void CPU::sra(uint8_t& r8) {
    setFlagC(r8 & 0x01);
    r8 = (r8 & 0x80) | (r8 >> 1);
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::sraHL() {
    uint8_t value = memory.read(HL);
    sra(value);
    memory.write(HL, value);
}

// Shift Right Logical
void CPU::srl(uint8_t& r8) {
    setFlagC(r8 & 0x01);
    r8 >>= 1;
    setFlagZ(r8 == 0);
    setFlagN(0);
    setFlagH(0);
}

void CPU::srlHL() {
    uint8_t value = memory.read(HL);
    srl(value);
    memory.write(HL, value);
}

// Load 8-bit register to 8-bit register
void CPU::ldR8R8(uint8_t& dest, const uint8_t& src) {
    dest = src;
}

// Load 8-bit immediate value to 8-bit register
void CPU::ldR8N8(uint8_t& r8, uint8_t n8) {
    r8 = n8;
}

// Load 16-bit immediate value to 16-bit register
void CPU::ldR16N16(uint16_t& r16, uint16_t n16) {
    r16 = n16;
}

// Store 8-bit register to memory location pointed by HL
void CPU::ldHLR8(const uint8_t& r8) {
    memory.write(HL, r8);
}

// Store 8-bit immediate value to memory location pointed by HL
void CPU::ldHLN8(uint8_t n8) {
    memory.write(HL, n8);
}

// Load value from memory location pointed by HL to 8-bit register
void CPU::ldR8HL(uint8_t& r8) {
    r8 = memory.read(HL);
}

// Store A in memory location pointed by a 16-bit register (BC, DE, HL)
void CPU::ldR16A(const uint16_t& r16) {
    memory.write(r16, A);
}

// Store A in memory location specified by a 16-bit immediate value
void CPU::ldN16A(uint16_t n16) {
    memory.write(n16, A);
}

// Special load from A to memory location 0xFF00 + 8-bit immediate value
void CPU::ldhN16A(uint8_t n8) {
    memory.write(0xFF00 + n8, A);
}

// Special load from memory location 0xFF00 + 8-bit immediate value to A
void CPU::ldhAN16(uint8_t n8) {
    A = memory.read(0xFF00 + n8);
}

// Special load from A to memory location 0xFF00 + C
void CPU::ldhCA() {
    memory.write(0xFF00 + C, A);
}

// Special load from memory location 0xFF00 + C to A
void CPU::ldhAC() {
    A = memory.read(0xFF00 + C);
}

// Load A into [HL] and increment HL
void CPU::ldHLIA() {
    memory.write(HL++, A);
}

// Load [HL] into A and increment HL
void CPU::ldAHLI() {
    A = memory.read(HL++);
}

// Load A into [HL] and decrement HL
void CPU::ldHLDA() {
    memory.write(HL--, A);
}

// Load [HL] into A and decrement HL
void CPU::ldAHLD() {
    A = memory.read(HL--);
}

// Adds the value of SP to HL
void CPU::addHLSP() {
    setFlagH((HL & 0x0FFF) + (SP & 0x0FFF) > 0x0FFF);
    setFlagC(HL + SP > 0xFFFF);
    HL += SP;
    setFlagN(0);
}

// Adds an 8-bit signed value to SP
void CPU::addSPE8(int8_t e8) {
    int result = static_cast<int>(SP) + static_cast<int>(e8);
    setFlagC((SP ^ e8 ^ (result & 0xFFFF)) & 0x100);
    setFlagH((SP ^ e8 ^ (result & 0xFFFF)) & 0x10);
    SP = static_cast<uint16_t>(result);
    setFlagZ(0);
    setFlagN(0);
}

// Decrements SP
void CPU::decSP() {
    SP--;
}

// Increments SP
void CPU::incSP() {
    SP++;
}

// Loads a 16-bit immediate value into SP
void CPU::ldSPN16(uint16_t n16) {
    SP = n16;
}

// Stores SP at the address specified by a 16-bit immediate value
void CPU::ldN16SP(uint16_t n16) {
    memory.write(n16, SP & 0xFF);
    memory.write(n16 + 1, SP >> 8);
}

// Loads HL with the value of SP plus an 8-bit signed immediate value
void CPU::ldHLSPE8(int8_t e8) {
    int result = static_cast<int>(SP) + static_cast<int>(e8);
    setFlagC((SP ^ e8 ^ (result & 0xFFFF)) & 0x100);
    setFlagH((SP ^ e8 ^ (result & 0xFFFF)) & 0x10);
    HL = static_cast<uint16_t>(result);
    setFlagZ(0);
    setFlagN(0);
}

// Loads SP with the value of HL
void CPU::ldSPHL() {
    SP = HL;
}

// Pops two bytes off the stack into AF
void CPU::popAF() {
    F = memory.read(SP++) & 0xF0; // Ensure unused bits are 0
    A = memory.read(SP++);
}

// Pops two bytes off the stack into a 16-bit register
void CPU::popR16(uint16_t& r16) {
    uint8_t lo = memory.read(SP++);
    uint8_t hi = memory.read(SP++);
    r16 = (hi << 8) | lo;
}

// Pushes AF onto the stack
void CPU::pushAF() {
    memory.write(--SP, A);
    memory.write(--SP, F & 0xF0); // Ensure unused bits are 0
}

// Pushes a 16-bit register onto the stack
void CPU::pushR16(const uint16_t& r16) {
    memory.write(--SP, r16 >> 8);
    memory.write(--SP, r16 & 0xFF);
}

// CALL n16: Call subroutine at n16
void CPU::callN16(uint16_t n16) {
    push(PC);
    PC = n16;
}

// CALL cc,n16: Conditionally call subroutine at n16
void CPU::callCCN16(bool condition, uint16_t n16) {
    if (condition) {
        callN16(n16);
        // Additional cycles might be necessary here depending on your CPU timing implementation
    }
}

// JP HL: Jump to address contained in HL
void CPU::jpHL() {
    PC = HL;
}

// JP n16: Jump to address n16
void CPU::jpN16(uint16_t n16) {
    PC = n16;
}

// JP cc,n16: Conditionally jump to address n16
void CPU::jpCCN16(bool condition, uint16_t n16) {
    if (condition) {
        jpN16(n16);
    }
}

// JR n16: Relative jump by n16
void CPU::jrN16(int8_t n8) { // n8 is a signed 8-bit integer for relative jumps
    PC += n8;
}

// JR cc,n16: Conditionally relative jump by n16
void CPU::jrCCN16(bool condition, int8_t n8) {
    if (condition) {
        jrN16(n8);
    }
}

// RET cc: Conditionally return from subroutine
void CPU::retCC(bool condition) {
    if (condition) {
        ret();
    }
}

// RET: Return from subroutine
void CPU::ret() {
    PC = pop(); // Pop the return address off the stack
}

// RETI: Return from interrupt, enabling interrupts after returning
void CPU::reti() {
    ret();
    // Enable interrupts here
}

// RST vec: Call subroutine at address vec
void CPU::rst(uint8_t vec) {
    push(PC);
    PC = vec;
}

// Utility methods for pushing and popping from the stack
void CPU::push(uint16_t value) {
    memory.write(--SP, value >> 8);
    memory.write(--SP, value & 0xFF);
}

uint16_t CPU::pop() {
    uint16_t lo = memory.read(SP++);
    uint16_t hi = memory.read(SP++);
    return (hi << 8) | lo;
}

uint8_t CPU::fetch() {
    return memory.read(PC++); // Fetch the opcode and increment the PC
}

void CPU::executeInstruction(uint8_t opcode) {
    switch (opcode) {
    case 0x00: // NOP
        NOP();
        break;
    case 0x01: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x02: // LD BC,d16
        
        break;
    case 0x03: // LD BC,d16
        
        break;
    case 0x04: // LD BC,d16
        
        break;
    case 0x05: // LD BC,d16
        
        break;
    case 0x06: // LD BC,d16
        
        break;
    case 0x07: // LD BC,d16
        
        break;
    case 0x08: // LD BC,d16
        
        break;
    case 0x09: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x0A: // LD BC,d16
        
        break;
    case 0x0B: // LD BC,d16
        
        break;
    case 0x0C: // LD BC,d16
        
        break;
    case 0x0D: // LD BC,d16
        
        break;
    case 0x0E: // LD BC,d16
        
        break;
    case 0x0F: // LD BC,d16
        
        break;
    case 0x10: // NOP
        break;
    case 0x11: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x12: // LD BC,d16
        
        break;
    case 0x13: // LD BC,d16
        
        break;
    case 0x14: // LD BC,d16
        
        break;
    case 0x15: // LD BC,d16
        
        break;
    case 0x16: // LD BC,d16
        
        break;
    case 0x17: // LD BC,d16
        
        break;
    case 0x18: // LD BC,d16
        
        break;
    case 0x19: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x1A: // LD BC,d16
        
        break;
    case 0x1B: // LD BC,d16
        
        break;
    case 0x1C: // LD BC,d16
        
        break;
    case 0x1D: // LD BC,d16
        
        break;
    case 0x1E: // LD BC,d16
        
        break;
    case 0x1F: // LD BC,d16
        
        break;
    case 0x20: // NOP
        break;
    case 0x21: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x22: // LD BC,d16
        
        break;
    case 0x23: // LD BC,d16
        
        break;
    case 0x24: // LD BC,d16
        
        break;
    case 0x25: // LD BC,d16
        
        break;
    case 0x26: // LD BC,d16
        
        break;
    case 0x27: // LD BC,d16
        
        break;
    case 0x28: // LD BC,d16
        
        break;
    case 0x29: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x2A: // LD BC,d16
        
        break;
    case 0x2B: // LD BC,d16
        
        break;
    case 0x2C: // LD BC,d16
        
        break;
    case 0x2D: // LD BC,d16
        
        break;
    case 0x2E: // LD BC,d16
        
        break;
    case 0x2F: // LD BC,d16
        
        break;
    case 0x30: // NOP
        break;
    case 0x31: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x32: // LD BC,d16
        
        break;
    case 0x33: // LD BC,d16
        
        break;
    case 0x34: // LD BC,d16
        
        break;
    case 0x35: // LD BC,d16
        
        break;
    case 0x36: // LD BC,d16
        
        break;
    case 0x37: // LD BC,d16
        
        break;
    case 0x38: // LD BC,d16
        
        break;
    case 0x39: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x3A: // LD BC,d16
        
        break;
    case 0x3B: // LD BC,d16
        
        break;
    case 0x3C: // LD BC,d16
        
        break;
    case 0x3D: // LD BC,d16
        
        break;
    case 0x3E: // LD BC,d16
        
        break;
    case 0x3F: // LD BC,d16
        
        break;
    case 0x40: // NOP
        break;
    case 0x41: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x42: // LD BC,d16
        
        break;
    case 0x43: // LD BC,d16
        
        break;
    case 0x44: // LD BC,d16
        
        break;
    case 0x45: // LD BC,d16
        
        break;
    case 0x46: // LD BC,d16
        
        break;
    case 0x47: // LD BC,d16
        
        break;
    case 0x48: // LD BC,d16
        
        break;
    case 0x49: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x4A: // LD BC,d16
        
        break;
    case 0x4B: // LD BC,d16
        
        break;
    case 0x4C: // LD BC,d16
        
        break;
    case 0x4D: // LD BC,d16
        
        break;
    case 0x4E: // LD BC,d16
        
        break;
    case 0x4F: // LD BC,d16
        
        break;
    case 0x50: // NOP
        break;
    case 0x51: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x52: // LD BC,d16
        
        break;
    case 0x53: // LD BC,d16
        
        break;
    case 0x54: // LD BC,d16
        
        break;
    case 0x55: // LD BC,d16
        
        break;
    case 0x56: // LD BC,d16
        
        break;
    case 0x57: // LD BC,d16
        
        break;
    case 0x58: // LD BC,d16
        
        break;
    case 0x59: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x5A: // LD BC,d16
        
        break;
    case 0x5B: // LD BC,d16
        
        break;
    case 0x5C: // LD BC,d16
        
        break;
    case 0x5D: // LD BC,d16
        
        break;
    case 0x5E: // LD BC,d16
        
        break;
    case 0x5F: // LD BC,d16
        
        break;
    case 0x60: // NOP
        break;
    case 0x61: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x62: // LD BC,d16
        
        break;
    case 0x63: // LD BC,d16
        
        break;
    case 0x64: // LD BC,d16
        
        break;
    case 0x65: // LD BC,d16
        
        break;
    case 0x66: // LD BC,d16
        
        break;
    case 0x67: // LD BC,d16
        
        break;
    case 0x68: // LD BC,d16
        
        break;
    case 0x69: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x6A: // LD BC,d16
        
        break;
    case 0x6B: // LD BC,d16
        
        break;
    case 0x6C: // LD BC,d16
        
        break;
    case 0x6D: // LD BC,d16
        
        break;
    case 0x6E: // LD BC,d16
        
        break;
    case 0x6F: // LD BC,d16
        
        break;
    case 0x70: // NOP
        break;
    case 0x71: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x72: // LD BC,d16
        
        break;
    case 0x73: // LD BC,d16
        
        break;
    case 0x74: // LD BC,d16
        
        break;
    case 0x75: // LD BC,d16
        
        break;
    case 0x76: // LD BC,d16
        
        break;
    case 0x77: // LD BC,d16
        
        break;
    case 0x78: // LD BC,d16
        
        break;
    case 0x79: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x7A: // LD BC,d16
        
        break;
    case 0x7B: // LD BC,d16
        
        break;
    case 0x7C: // LD BC,d16
        
        break;
    case 0x7D: // LD BC,d16
        
        break;
    case 0x7E: // LD BC,d16
        
        break;
    case 0x7F: // LD BC,d16
        
        break;
    case 0x80: // NOP
        break;
    case 0x81: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x82: // LD BC,d16
        
        break;
    case 0x83: // LD BC,d16
        
        break;
    case 0x84: // LD BC,d16
        
        break;
    case 0x85: // LD BC,d16
        
        break;
    case 0x86: // LD BC,d16
        
        break;
    case 0x87: // LD BC,d16
        
        break;
    case 0x88: // LD BC,d16
        
        break;
    case 0x89: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x8A: // LD BC,d16
        
        break;
    case 0x8B: // LD BC,d16
        
        break;
    case 0x8C: // LD BC,d16
        
        break;
    case 0x8D: // LD BC,d16
        
        break;
    case 0x8E: // LD BC,d16
        
        break;
    case 0x8F: // LD BC,d16
        
        break;
    case 0x90: // NOP
        break;
    case 0x91: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x92: // LD BC,d16
        
        break;
    case 0x93: // LD BC,d16
        
        break;
    case 0x94: // LD BC,d16
        
        break;
    case 0x95: // LD BC,d16
        
        break;
    case 0x96: // LD BC,d16
        
        break;
    case 0x97: // LD BC,d16
        
        break;
    case 0x98: // LD BC,d16
        
        break;
    case 0x99: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0x9A: // LD BC,d16
        
        break;
    case 0x9B: // LD BC,d16
        
        break;
    case 0x9C: // LD BC,d16
        
        break;
    case 0x9D: // LD BC,d16
        
        break;
    case 0x9E: // LD BC,d16
        
        break;
    case 0x9F: // LD BC,d16
        
        break;
    case 0xA0: // NOP
        break;
    case 0xA1: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xA2: // LD BC,d16
        
        break;
    case 0xA3: // LD BC,d16
        
        break;
    case 0xA4: // LD BC,d16
        
        break;
    case 0xA5: // LD BC,d16
        
        break;
    case 0xA6: // LD BC,d16
        
        break;
    case 0xA7: // LD BC,d16
        
        break;
    case 0xA8: // LD BC,d16
        
        break;
    case 0xA9: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xAA: // LD BC,d16
        
        break;
    case 0xAB: // LD BC,d16
        
        break;
    case 0xAC: // LD BC,d16
        
        break;
    case 0xAD: // LD BC,d16
        
        break;
    case 0xAE: // LD BC,d16
        
        break;
    case 0xAF: // LD BC,d16
        
        break;
    case 0xB0: // NOP
        break;
    case 0xB1: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xB2: // LD BC,d16
        
        break;
    case 0xB3: // LD BC,d16
        
        break;
    case 0xB4: // LD BC,d16
        
        break;
    case 0xB5: // LD BC,d16
        
        break;
    case 0xB6: // LD BC,d16
        
        break;
    case 0xB7: // LD BC,d16
        
        break;
    case 0xB8: // LD BC,d16
        
        break;
    case 0xB9: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xBA: // LD BC,d16
        
        break;
    case 0xBB: // LD BC,d16
        
        break;
    case 0xBC: // LD BC,d16
        
        break;
    case 0xBD: // LD BC,d16
        
        break;
    case 0xBE: // LD BC,d16
        
        break;
    case 0xBF: // LD BC,d16
        
        break;
    case 0xC0: // NOP
        break;
    case 0xC1: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xC2: // LD BC,d16
        
        break;
    case 0xC3: // LD BC,d16
        
        break;
    case 0xC4: // LD BC,d16
        
        break;
    case 0xC5: // LD BC,d16
        
        break;
    case 0xC6: // LD BC,d16
        
        break;
    case 0xC7: // LD BC,d16
        
        break;
    case 0xC8: // LD BC,d16
        
        break;
    case 0xC9: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xCA: // LD BC,d16
        
        break;
    case 0xCB: // LD BC,d16
        
        break;
    case 0xCC: // LD BC,d16
        
        break;
    case 0xCD: // LD BC,d16
        
        break;
    case 0xCE: // LD BC,d16
        
        break;
    case 0xCF: // LD BC,d16
        
        break;
    case 0xD0: // NOP
        break;
    case 0xD1: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xD2: // LD BC,d16
        
        break;
    case 0xD3: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xD4: // LD BC,d16
        
        break;
    case 0xD5: // LD BC,d16
        
        break;
    case 0xD6: // LD BC,d16
        
        break;
    case 0xD7: // LD BC,d16
        
        break;
    case 0xD8: // LD BC,d16
        
        break;
    case 0xD9: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xDA: // LD BC,d16
        
        break;
    case 0xDB: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xDC: // LD BC,d16
        
        break;
    case 0xDD: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xDE: // LD BC,d16
        
        break;
    case 0xDF: // LD BC,d16
        
        break;
    case 0xE0: // NOP
        break;
    case 0xE1: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xE2: // LD BC,d16
        
        break;
    case 0xE3: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xE4: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xE5: // LD BC,d16
        
        break;
    case 0xE6: // LD BC,d16
        
        break;
    case 0xE7: // LD BC,d16
        
        break;
    case 0xE8: // LD BC,d16
        
        break;
    case 0xE9: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xEA: // LD BC,d16
        
        break;
    case 0xEB: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xEC: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xED: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xEE: // LD BC,d16
        
        break;
    case 0xEF: // LD BC,d16
        
        break;
    case 0xF0: // NOP
        break;
    case 0xF1: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xF2: // LD BC,d16
        
        break;
    case 0xF3: // LD BC,d16
        
        break;
    case 0xF4: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xF5: // LD BC,d16
        
        break;
    case 0xF6: // LD BC,d16
        
        break;
    case 0xF7: // LD BC,d16
        
        break;
    case 0xF8: // LD BC,d16
        
        break;
    case 0xF9: // LD BC,d16
        
        break;
        // Add more opcodes as needed
    case 0xFA: // LD BC,d16
        
        break;
    case 0xFB: // LD BC,d16
        
        break;
    case 0xFC: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xFD: // LD BC,d16
        throw InvalidOpcodeException(opcode);
        break;
    case 0xFE: // LD BC,d16
        
        break;
    case 0xFF: // LD BC,d16
        
        break;
    default:
        // Handle unknown opcode
        break;
    }
}