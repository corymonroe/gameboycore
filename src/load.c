
#include "load.h"

int ldAA(struct Core* core)
{
	core->AF.A = core->AF.A;
	return 0;
}

int ldAB(struct Core* core)
{
	core->AF.A = core->BC.B;
	return 0;
}

int ldAC(struct Core* core)
{
	core->AF.A = core->BC.C;
	return 0;
}

int ldAD(struct Core* core)
{
	core->AF.A = core->DE.D;
	return 0;
}

int ldAE(struct Core* core)
{
	core->AF.A = core->BC.B;
	return 0;
}

int ldAH(struct Core* core)
{
	core->AF.A = core->HL.H;
	return 0;
}

int ldAL(struct Core* core)
{
	core->AF.A = core->HL.L;
	return 0;
}

int ldAHL(struct Core* core)
{
	core->AF.A = core->mem[core->HL.val];
	return 0;
}

int ldABC(struct Core* core)
{
	core->AF.A = core->mem[core->BC.val];
	return 0;
}

int ldADE(struct Core* core)
{
	core->AF.A = core->mem[core->DE.val];
	return 0;
}

int ldAWord(struct Core* core)
{
	core->AF.A = core->mem[getNextWord(&core->PC, core->mem)];
	return 0;
}

int ldBA(struct Core* core)
{
	core->BC.B = core->AF.A;
	return 0;
}

int ldBB(struct Core* core)
{
	core->BC.B = core->BC.B;
	return 0;
}

int ldBC(struct Core* core)
{
	core->BC.B = core->BC.C;
	return 0;
}

int ldBD(struct Core* core)
{
	core->BC.B = core->DE.D;
	return 0;
}

int ldBE(struct Core* core)
{
	core->BC.B = core->DE.D;
	return 0;
}

int ldBH(struct Core* core)
{
	core->BC.B = core->HL.H;
	return 0;
}

int ldBL(struct Core* core)
{
	core->BC.B = core->HL.L;
	return 0;
}

int ldBHL(struct Core* core)
{
	core->BC.B = core->mem[core->HL.val];
	return 0;
}

int ldCA(struct Core* core)
{
	core->BC.C = core->AF.A;
	return 0;
}

int ldCB(struct Core* core)
{
	core->BC.C = core->BC.B;
	return 0;
}

int ldCC(struct Core* core)
{
	core->BC.C = core->BC.C;
	return 0;
}

int ldCD(struct Core* core)
{
	core->BC.C = core->DE.D;
	return 0;
}

int ldCE(struct Core* core)
{
	core->BC.C = core->DE.E;
	return 0;
}

int ldCH(struct Core* core)
{
	core->BC.C = core->HL.L;
	return 0;
}

int ldCL(struct Core* core)
{
	core->BC.C = core->HL.L;
	return 0;
}

int ldCHL(struct Core* core)
{
	core->BC.C = core->mem[core->HL.val];
	return 0;
}

int ldDA(struct Core* core)
{
	core->DE.D = core->AF.A;
	return 0;
}

int ldDB(struct Core* core)
{
	core->DE.D = core->BC.B;
	return 0;
}

int ldDC(struct Core* core)
{
	core->DE.D = core->BC.C;
	return 0;
}

int ldDD(struct Core* core)
{
	core->DE.D = core->DE.D;
	return 0;
}

int ldDE(struct Core* core)
{
	core->DE.D = core->DE.E;
	return 0;
}

int ldDH(struct Core* core)
{
	core->DE.D = core->HL.H;
	return 0;
}

int ldDL(struct Core* core)
{
	core->DE.D = core->HL.L;
	return 0;
}

int ldDHL(struct Core* core)
{
	core->DE.D = core->mem[core->HL.val];
	return 0;
}

int ldEA(struct Core* core)
{
	core->DE.E = core->AF.A;
	return 0;
}

int ldEB(struct Core* core)
{
	core->DE.E = core->BC.B;
	return 0;
}

int ldEC(struct Core* core)
{
	core->DE.E = core->BC.C;
	return 0;
}

int ldED(struct Core* core)
{
	core->DE.E = core->DE.D;
	return 0;
}

int ldEE(struct Core* core)
{
	core->DE.E = core->DE.E;
	return 0;
}

int ldEH(struct Core* core)
{
	core->DE.E = core->HL.H;
	return 0;
}

int ldEL(struct Core* core)
{
	core->DE.E = core->HL.L;
	return 0;
}

int ldEHL(struct Core* core)
{
	core->DE.E = core->mem[core->HL.val];
	return 0;
}

int ldHA(struct Core* core)
{
	core->HL.H = core->AF.A;
	return 0;
}

int ldHB(struct Core* core)
{
	core->HL.H = core->BC.B;
	return 0;
}

int ldHC(struct Core* core)
{
	core->HL.H = core->BC.C;
	return 0;
}

int ldHD(struct Core* core)
{
	core->HL.H = core->DE.D;
	return 0;
}

int ldHE(struct Core* core)
{
	core->HL.H = core->DE.E;
	return 0;
}

int ldHH(struct Core* core)
{
	core->HL.H = core->HL.H;
	return 0;
}

int ldHL(struct Core* core)
{
	core->HL.H = core->HL.L;
	return 0;
}

int ldHHL(struct Core* core)
{
	core->HL.H = core->mem[core->HL.val];
	return 0;
}

int ldLA(struct Core* core)
{
	core->HL.L = core->AF.A;
	return 0;
}

int ldLB(struct Core* core)
{
	core->HL.L = core->BC.B;
	return 0;
}

int ldLC(struct Core* core)
{
	core->HL.L = core->BC.C;
	return 0;
}

int ldLD(struct Core* core)
{
	core->HL.L = core->DE.D;
	return 0;
}

int ldLE(struct Core* core)
{
	core->HL.L = core->DE.E;
	return 0;
}

int ldLH(struct Core* core)
{
	core->HL.L = core->HL.H;
	return 0;
}

int ldLL(struct Core* core)
{
	core->HL.L = core->HL.L;
	return 0;
}

int ldLHL(struct Core* core)
{
	core->HL.L = core->mem[core->HL.val];
	return 0;
}

int ldHLA(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->AF.A);
		return;

	core->mem[core->HL.val] = core->AF.A;
	return 0;
}

int ldHLB(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->BC.B);
		return;

	core->mem[core->HL.val] = core->BC.B;
	return 0;
}

int ldHLC(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->BC.C);
		return;
	core->mem[core->HL.val] = core->BC.C;
	return 0;
}

int ldHLD(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->DE.D);
		return;
	core->mem[core->HL.val] = core->DE.D;
	return 0;
}

int ldHLE(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->DE.E);
		return;
	core->mem[core->HL.val] = core->DE.E;
	return 0;
}

int ldHLH(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->HL.H);
		return;
	core->mem[core->HL.val] = core->HL.H;
	return 0;
}

int ldHLL(struct Core* core)
{
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->HL.L);
		return;
	core->mem[core->HL.val] = core->HL.L;
	return 0;
}

int ldAByte(struct Core* core)
{
	core->AF.A = core->mem[++core->PC];
	return 0;
}

int ldBByte(struct Core* core)
{
	core->BC.B = core->mem[++core->PC];
	return 0;
}

int ldCByte(struct Core* core)
{
	core->BC.C = core->mem[++core->PC];
	return 0;
}

int ldDByte(struct Core* core)
{
	core->DE.D = core->mem[++core->PC];
	return 0;
}

int ldEByte(struct Core* core)
{
	core->DE.E = core->mem[++core->PC];
	return 0;
}

int ldHByte(struct Core* core)
{
	core->HL.H = core->mem[++core->PC];
	return 0;
}

int ldLByte(struct Core* core)
{
	core->HL.L = core->mem[++core->PC];
	return 0;
}

int ldHLByte(struct Core* core)
{
	uint8_t byte = core->mem[++core->PC];
	if(core->HL.val > PERMANENT_ROM_BANK_START && core->HL.val < PERMANENT_ROM_BANK_END) 
		swap(core, byte);
		return;
	core->mem[core->HL.val] = byte;
	return 0;
}

int ldBCA(struct Core* core)
{
	uint8_t byte = core->mem[++core->PC];
	if(core->BC.val > PERMANENT_ROM_BANK_START && core->BC.val < PERMANENT_ROM_BANK_END) 
		swap(core, byte);
		return;
	core->mem[core->BC.val] = core->AF.A;
	return 0;
}

int ldDEA(struct Core* core)
{
	if(core->DE.val > PERMANENT_ROM_BANK_START && core->DE.val < PERMANENT_ROM_BANK_END) 
		swap(core, core->AF.A);
		return;
	core->mem[core->DE.val] = core->AF.A;
	return 0;
}

int ldAddrA(struct Core* core)
{
	uint16_t addr = getNextWord(&core->PC, core->mem);
	if(addr > PERMANENT_ROM_BANK_START && addr < PERMANENT_ROM_BANK_END) 
		swap(core, core->AF.A);
		return;
	core->mem[addr] = core->AF.A;
	return 0;
}

/* 16 bit */

int ldBCWord(struct Core* core)
{
	core->BC.val = getNextWord(&core->PC, core->mem);
	return 0;
}

int ldDEWord(struct Core* core)
{
	core->DE.val = getNextWord(&core->PC, core->mem);
	return 0;
}

int ldHLWord(struct Core* core)
{
	core->HL.val = getNextWord(&core->PC, core->mem);
	return 0;
}

int ldSPWord(struct Core* core)
{
	core->SP = getNextWord(&core->PC, core->mem);
	return 0;
}

int ldHLAddr(struct Core* core)
{
	core->HL.val = core->mem[getNextWord(&core->PC, core->mem)];
	return 0;
}

int ldBCAddr(struct Core* core)
{
	core->BC.val = core->mem[getNextWord(&core->PC, core->mem)];
	return 0;
}

int ldDEAddr(struct Core* core)
{
	core->DE.val = core->mem[getNextWord(&core->PC, core->mem)];
	return 0;
}

int ldAddrHL(struct Core* core)
{
	uint16_t addr = getNextWord(&core->PC, core->mem);
	if(addr > PERMANENT_ROM_BANK_START && addr < PERMANENT_ROM_BANK_END) 
		swap(core, core->HL.val);
		return;
	core->mem[addr] = core->HL.val;
	return 0;
}

int ldSPHL(struct Core* core)
{
	core->SP = core->HL.val;
	return 0;
}