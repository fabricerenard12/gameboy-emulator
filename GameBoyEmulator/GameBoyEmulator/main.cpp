#include "CPU.hpp"
#include "Memory.hpp"
// Include other necessary headers...

int main() {
    // Initialize memory and load the ROM
    Memory memory;
    FileHandler fileHandler("path/to/rom.gb");
    memory.loadROM(fileHandler);

    // Initialize the CPU with a reference to memory
    CPU cpu(memory);

    // Main emulation loop
    while (true) {
        cpu.executeNextInstruction();

        // Handle interrupts, if any are pending
        cpu.handleInterrupts();

        // Update other components like the GPU and timers based on elapsed CPU cycles
        // gpu.update(cpu.getLastInstructionCycles());
        // timer.update(cpu.getLastInstructionCycles());

        // Check for conditions to exit the loop (e.g., user input, reaching a breakpoint)
        if (shouldExit()) {
            break;
        }
    }

    return 0;
}
