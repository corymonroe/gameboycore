
package com.nnarain.gb.resource;

/**
* Native interface to the underlying C struct Core
*
* @author Natesh Narain
**/
public class GBCore extends GBNativeResource{

	public GBCore(){
		super(createCore());
	}

	/**
	* Executes the next instruction
	*/
	public void step(){
		step(this.handle);
	}

	/**
	* Loads the permament ROM Bank of GBCore
	*/
	//public void loadROMBank0(byte[] rom){
	//	loadROMBank0(this.handle, rom);
	//}

	//public void loadBanks(GBROMParser parser){
	//	loadBanks(handle, parser.getHandle());
	//}


	public void release(){
		release(handle);
	}

	/* Native Functions */

	private static native long createCore();

	//private static native void loadBanks(long hCore, long hData);

	//private static native void loadROMBank0(long handle, byte[] rom);
	//private static native void swapROM(long handle, byte[] rom);

	private static native void step(long handle);
	private static native void release(long handle);

}


