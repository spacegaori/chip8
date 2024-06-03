#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <cstdint>
#include <stack>

constexpr

constexpr std::array<uint8_t, 80> gFontSet {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
};

constexpr std::size_t gMemorySize{ 4096 };
constexpr std::size_t gScreenWidth { 64 };
constexpr std::size_t gScreenHeight { 32 };
constexpr std::size_t gStackSize{ 16 };
constexpr std::size_t gRegisterCount{ 16 };

class chip8 {
private:
    // 4096 (0x1000) memory locations of 8 bits (1 byte).
    std::array<uint8_t, gMemorySize> mMemory{};                // Memory
    // 16 8-bit data registers named V0 to VF where the VF register doubles as a flag.
    std::array<uint8_t, gRegisterCount> mRegisters{};
    // The stack is only used to store return addresses when subroutines are called.
    std::array<uint16_t, gStackSize> mStack{};                 // Stack
    uint8_t mDelayTimer{};
    uint8_t mAudioTimer{};
    std::array<bool, gScreenWidth * gScreenHeight> mDisplay{}; // Display
    uint16_t mProgramCounter{ 0x200 };                         // Program Counter
    uint16_t mIndex{};

public:
};



#endif //CHIP8_H
