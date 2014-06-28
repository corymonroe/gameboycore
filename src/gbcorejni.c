
#include "com_nnarain_gb_resource_GBCore.h"
#include "gbapi.h"
#include <stdlib.h>

JNIEXPORT jlong JNICALL Java_com_nnarain_gb_resource_GBCore_createCore(JNIEnv *env, jclass clazz)
{
	struct Core* core = (struct Core*) malloc( sizeof(struct Core) );
	initCore(core);

	return (long) core;
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_step(JNIEnv *env, jclass clazz, jlong handle)
{
	struct Core* core = (struct Core*) ((long)handle);
	execute(core, core->mem[++core->PC]);
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_loadROMBank0(JNIEnv *env, jclass c, jlong handle, jbyteArray rom)
{
	struct Core* core = (struct Core*) ((long)handle);
	int i;

	const int len = (*env)->GetArrayLength(env, rom);
	jbyte* romElements = (*env)->GetByteArrayElements(env, rom, 0);

	for(i = 0; i < len; i++){
		core->mem[i] = (uint8_t) romElements[i];
	}

}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_swapROM(JNIEnv *env, jclass c, jlong handle, jbyteArray rom)
{
	struct Core* core = (struct Core*) ((long)handle);
	int i;
	int j;
	jbyte* romElements;

	const int len = SWITCHABLE_ROM_BANK_END - SWITCHABLE_ROM_BANK_START;
	romElements = (*env)->GetByteArrayElements(env, rom, 0);

	for(i = SWITCHABLE_ROM_BANK_START, j = 0; j < len; i++, j++){
		core->mem[i] = romElements[j];
	}
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_resource_GBCore_loadBanks(JNIEnv *env, jclass c, jlong hCore, jlong hData)
{
	struct Core* core = (struct Core*)((long)hCore);
	struct GBROMData* data = (struct GBROMData*)((long)hData);

	initBanks(core, data->nBanks);
	loadBanks(core, data->banks, data->nBanks);
}