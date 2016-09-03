
#include "gameboy/cpu.h"

#define WORD(hi, lo) ( (((hi) & 0xFFFF) << 8) | ((lo) & 0xFFFF) )

uint8_t cycles1[] = { 0 };
uint8_t cycles2[] = { 0 };

namespace gb
{
	CPU::CPU() :
		mmu_(),
		halted_(false),
		cycle_count_(0)
	{
		reset();
	}

	void CPU::tick()
	{
		// fetch next opcode
		uint8_t opcode = mmu_.read(pc_.val++);
		uint8_t cycles;

		// $CB means decode from the second page of instructions
		if (opcode != 0xCB)
		{
			// decode from first page
			decode1(opcode);

			// look up the number of cycles for this opcode
			cycles = cycles1[opcode];
		}
		else
		{
			// read the second page opcode
			opcode = mmu_.read(pc_.val++);
			// decode from second page
			decode2(opcode);

			// look up the number of cycles for this opcode
			cycles = cycles2[opcode];
		}

		cycle_count_ += cycles;

		// TODO: determine what interrupts should fire
	}

	void CPU::decode1(uint8_t opcode)
	{
		switch (opcode)
		{
		case 0x00:
			// NOP
			break;

			// Load Instructions

			// 8 bit loads immediate
		case 0x3E: // LD A,d8
			af_.hi = load8Imm();
			break;
		case 0x06: // LD B,d8
			bc_.hi = load8Imm();
			break;
		case 0x0E: // LD C,d8
			bc_.lo = load8Imm();
			break;
		case 0x16: // LD D,d8
			de_.hi = load8Imm();
			break;
		case 0x1E: // LD E,d8
			de_.lo = load8Imm();
			break;
		case 0x26: // LD H,d8
			hl_.hi = load8Imm();
			break;
		case 0x2E: // LD L,d8
			hl_.lo = load8Imm();
			break;

			// load 16 bit immediate
		case 0x01: // LD BC,d16
			bc_.val = load16Imm();
			break;
		case 0x11: // LD DE,d16
			de_.val = load16Imm();
			break;
		case 0x21: // LD HL,d16
			hl_.val = load16Imm();
			break;
		case 0x31: // LD SP,d16
			sp_.val = load16Imm();
			break;

			// transfer (Register to register, memory to register)
		case 0x40: // LD B,B
			bc_.hi = bc_.hi;
			break;
		case 0x41: // LD B,C
			bc_.hi = bc_.lo;
			break;
		case 0x42: // LD B,D
			bc_.hi = de_.hi;
			break;
		case 0x43: // LD B,E
			bc_.hi = de_.lo;
			break;
		case 0x44: // LD B,H
			bc_.hi = hl_.hi;
			break;
		case 0x45: // LD B,L
			bc_.hi = hl_.lo;
			break;
		case 0x46: // LD B,(HL)
			bc_.hi = mmu_.read(hl_.val);
			break;
		case 0x47: // LD B,A
			bc_.hi = af_.hi;
			break;
		case 0x48: // LD C,B
			bc_.lo = bc_.hi;
			break;
		case 0x49: // LD C,C
			bc_.lo = bc_.lo;
			break;
		case 0x4A: // LD C,D
			bc_.lo = de_.hi;
			break;
		case 0x4B: // LD C,E
			bc_.lo = de_.lo;
			break;
		case 0x4C: // LD C,H
			bc_.lo = hl_.hi;
			break;
		case 0x4D: // LD C,L
			bc_.lo = hl_.lo;
			break;
		case 0x4E: // LD C,(HL)
			bc_.lo = mmu_.read(hl_.val);
			break;
		case 0x4F: // LD C,A
			bc_.lo = af_.hi;
			break;

		case 0x50: // LD D,B
			de_.hi = bc_.hi;
			break;
		case 0x51: // LD D,C
			de_.hi = bc_.lo;
			break;
		case 0x52: // LD D,D
			de_.hi = de_.hi;
			break;
		case 0x53: // LD D,E
			de_.hi = de_.lo;
			break;
		case 0x54: // LD D,H
			de_.hi = hl_.hi;
			break;
		case 0x55: // LD D,L
			de_.hi = hl_.lo;
			break;
		case 0x56: // LD D,(HL)
			de_.hi = mmu_.read(hl_.val);
			break;
		case 0x57: // LD D,A
			de_.hi = af_.hi;
			break;
		case 0x58: // LD E,B
			de_.lo = bc_.hi;
			break;
		case 0x59: // LD E,C
			de_.lo = bc_.lo;
			break;
		case 0x5A: // LD E,D
			de_.lo = de_.hi;
			break;
		case 0x5B: // LD E,E
			de_.lo = de_.lo;
			break;
		case 0x5C: // LD E,H
			de_.lo = hl_.hi;
			break;
		case 0x5D: // LD E,L
			de_.lo = hl_.lo;
			break;
		case 0x5E: // LD E,(HL)
			de_.lo = mmu_.read(hl_.val);
			break;
		case 0x5F: // LD E,A
			de_.lo = af_.hi;
			break;

		case 0x60: // LD H,B
			hl_.hi = bc_.hi;
			break;
		case 0x61: // LD H,C
			hl_.hi = bc_.lo;
			break;
		case 0x62: // LD H,D
			hl_.hi = de_.hi;
			break;
		case 0x63: // LD H,E
			hl_.hi = de_.lo;
			break;
		case 0x64: // LD H,H
			hl_.hi = hl_.hi;
			break;
		case 0x65: // LD H,L
			hl_.hi = hl_.lo;
			break;
		case 0x66: // LD H,(HL)
			hl_.hi = mmu_.read(hl_.val);
			break;
		case 0x67: // LD H,A
			hl_.hi = af_.hi;
			break;
		case 0x68: // LD L,B
			hl_.lo = bc_.hi;
			break;
		case 0x69: // LD L,C
			hl_.lo = bc_.lo;
			break;
		case 0x6A: // LD L,D
			hl_.lo = de_.hi;
			break;
		case 0x6B: // LD L,E
			hl_.lo = de_.lo;
			break;
		case 0x6C: // LD L,H
			hl_.lo = hl_.hi;
			break;
		case 0x6D: // LD L,L
			hl_.lo = hl_.lo;
			break;
		case 0x6E: // LD L,(HL)
			hl_.lo = mmu_.read(hl_.val);
			break;
		case 0x6F: // LD L,A
			hl_.lo = af_.hi;
			break;

		case 0x78: // LD A,B
			af_.hi = bc_.hi;
			break;
		case 0x79: // LD A,C
			af_.hi = bc_.lo;
			break;
		case 0x7A: // LD A,D
			af_.hi = de_.hi;
			break;
		case 0x7B: // LD A,E
			af_.hi = de_.lo;
			break;
		case 0x7C: // LD A,H
			af_.hi = hl_.hi;
			break;
		case 0x7D: // LD A,L
			af_.hi = hl_.lo;
			break;
		case 0x7E: // LD A,(HL)
			af_.hi = mmu_.read(hl_.val);
			break;
		case 0x7F: // LD A,A
			af_.hi = af_.hi;
			break;

			// register to memory
		case 0x70: // LD (HL),B
			mmu_.write(bc_.hi, hl_.val);
			break;
		case 0x71: // LD (HL),C
			mmu_.write(bc_.lo, hl_.val);
			break;
		case 0x72: // LD (HL),D
			mmu_.write(de_.hi, hl_.val);
			break;
		case 0x73: // LD (HL),E
			mmu_.write(de_.lo, hl_.val);
			break;
		case 0x74: // LD (HL),H
			mmu_.write(hl_.hi, hl_.val);
			break;
		case 0x75: // LD (HL),L
			mmu_.write(hl_.lo, hl_.val);
			break;
		case 0x77: // LD (HL),A
			mmu_.write(af_.hi, hl_.val);
			break;

			// Load Increment/Decrement
			// (HL+/-) <- A & A <- (HL+/-)
		case 0x22: // LD (HL+),A
			mmu_.write(af_.hi, hl_.val++);
			break;
		case 0x32: // LD (HL-),A
			mmu_.write(af_.hi, hl_.val--);
			break;
		case 0x2A: // LD A,(HL+)
			af_.hi = mmu_.read(hl_.val++);
			break;
		case 0x3A: // LD A,(HL-)
			af_.hi = mmu_.read(hl_.val--);
			break;

		// IN/OUT Instructions. Load and Store to IO Registers (immediate or using C register). IO Offset is $FF00
		case 0xE0: // LDH (a8),A
			out(load8Imm());
			break;
		case 0xF0: // LDH A,(a8)
			in(load8Imm());
			break;
		case 0xE2: // LD (C),A
			out(bc_.lo);
			break;
		case 0xF2: // LD A,(C)
			in(bc_.lo);
			break;
		case 0xEA: // LD (a16),A
			out(load16Imm());
			break;
		case 0xFA: // LD A,(a16)
			in(load16Imm());
			break;

		case 0x76:
			halted_ = true;
			break;
		}
	}

	void CPU::decode2(uint8_t opcode)
	{
		switch (opcode)
		{
		case 0x00:
			break;
		default:
			break;
		}
	}

	uint8_t CPU::load8Imm()
	{
		return mmu_.read(pc_.val++);
	}

	uint16_t CPU::load16Imm()
	{
		uint8_t lo = load8Imm();
		uint8_t hi = load8Imm();

		return WORD(hi, lo);
	}

	void CPU::in(uint16_t offset)
	{
		// read from offset into IO registers
		af_.hi = mmu_.read(0xFF00 + offset);
	}

	void CPU::out(uint16_t offset)
	{
		// write out to the IO registers given the offset
		mmu_.write(af_.hi, 0xFF00 + offset);
	}

	void CPU::reset()
	{
		af_.val = 0;
		bc_.val = 0;
		de_.val = 0;
		hl_.val = 0;
		sp_.val = memorymap::HIGH_RAM_END;
		pc_.val = memorymap::PROGRAM_START;

		cycle_count_ = 0;
		halted_ = false;
	}

    bool CPU::isHalted() const
    {
        return halted_;
    }

    const MMU& CPU::getMMU() const
    {
        return mmu_;
    }
	MMU& CPU::getMMU()
	{
		return mmu_;
	}

	CPU::Status CPU::getStatus() const
	{
		Status status;
		status.af = af_;
		status.bc = bc_;
		status.de = de_;
		status.hl = hl_;
		status.sp = sp_;
		status.pc = pc_;

		return status;
	}

}
