

#ifndef GB_EMULATOR
#define GB_EMULATOR

#include "GBCore.h"

//typedef int (*InstructionImpl)(Core*);

struct Instruction{
	int (*impl)(struct Core*);
	uint8_t cycles;
};

void bootCore(struct Core* core);
uint8_t* getAddress(struct Core*, uint16_t);

int addAA(struct Core*);
int addAB(struct Core*);
int addAC(struct Core*);
int addAD(struct Core*);
int addAE(struct Core*);
int addAH(struct Core*);
int addAL(struct Core*);
int addAHL(struct Core*);
int addAByte(struct Core*);

int execute(struct Core*, uint8_t);

int transfer(uint8_t* to, uint8_t* from);

/* Core functions */

int NOP(struct Core*);

int decBC(struct Core*);
int decDE(struct Core*);
int decHL(struct Core*);
int decSP(struct Core*);

int ldAA(struct Core*);
int ldAB(struct Core*);
int ldAC(struct Core*);
int ldAD(struct Core*);
int ldAE(struct Core*);
int ldAH(struct Core*);
int ldAL(struct Core*);
int ldAHL(struct Core*);
int ldABC(struct Core*);
int ldADE(struct Core*);
int ldAWord(struct Core*);
int ldBA(struct Core*);
int ldBB(struct Core*);
int ldBC(struct Core*);
int ldBD(struct Core*);
int ldBE(struct Core*);
int ldBH(struct Core*);
int ldBL(struct Core*);
int ldBHL(struct Core*);
int ldCA(struct Core*);
int ldCB(struct Core*);
int ldCC(struct Core*);
int ldCD(struct Core*);
int ldCE(struct Core*);
int ldCH(struct Core*);
int ldCL(struct Core*);
int ldCHL(struct Core*);
int ldDA(struct Core*);
int ldDB(struct Core*);
int ldDC(struct Core*);
int ldDD(struct Core*);
int ldDE(struct Core*);
int ldDH(struct Core*);
int ldDL(struct Core*);
int ldDHL(struct Core*);
int ldEA(struct Core*);
int ldEB(struct Core*);
int ldEC(struct Core*);
int ldED(struct Core*);
int ldEE(struct Core*);
int ldEH(struct Core*);
int ldEL(struct Core*);
int ldEHL(struct Core*);
int ldHA(struct Core*);
int ldHB(struct Core*);
int ldHC(struct Core*);
int ldHD(struct Core*);
int ldHE(struct Core*);
int ldHL(struct Core*);
int ldHHL(struct Core*);
int ldLA(struct Core*);
int ldLB(struct Core*);
int ldLC(struct Core*);
int ldLD(struct Core*);
int ldLE(struct Core*);
int ldLH(struct Core*);
int ldLHL(struct Core*);
int ldHLA(struct Core*);
int ldHLB(struct Core*);
int ldHLC(struct Core*);
int ldHLD(struct Core*);
int ldHLE(struct Core*);
int ldHLH(struct Core*);
int ldHLL(struct Core*);
int ldAByte(struct Core*);
int ldBByte(struct Core*);
int ldCByte(struct Core*);
int ldDByte(struct Core*);
int ldEByte(struct Core*);
int ldHByte(struct Core*);
int ldLByte(struct Core*);
int ldHLByte(struct Core*);




#endif // Z80_INSTRUCTION_SET
