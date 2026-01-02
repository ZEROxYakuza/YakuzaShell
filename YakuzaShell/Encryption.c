#include <Windows.h>
#include <stdio.h>
#include "aes.h"
#include "Functions.h"

#define KEYSIZE 32
#define IVSIZE 16

VOID GenerateRandomBytes(PBYTE pByte, SIZE_T sSize) {

	for (int i = 0; i < sSize; i++) {
		pByte[i] = (BYTE)rand() % 0xFF;
	}

}


VOID PrintHexData(LPCSTR Name, PBYTE Data, SIZE_T Size) {

	printf("unsigned char %s[] = {", Name);

	for (int i = 0; i < Size; i++) {
		if (i % 16 == 0) {
			printf("\n\t");
		}
		if (i < Size - 1) {
			printf("0x%0.2X, ", Data[i]);
		}
		else {
			printf("0x%0.2X ", Data[i]);
		}
	}

	printf("};\n\n\n");

}

BOOL PaddBuffer(IN PBYTE InputBuffer, IN SIZE_T InputBufferSize, OUT PBYTE* OutputPaddedBuffer, OUT SIZE_T* OutputPaddedSize) {

	PBYTE	PaddedBuffer = NULL;
	SIZE_T	PaddedSize = NULL;

	PaddedSize = InputBufferSize + 16 - (InputBufferSize % 16);
	PaddedBuffer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, PaddedSize);
	if (!PaddedBuffer) {
		return FALSE;
	}

	ZeroMemory(PaddedBuffer, PaddedSize);
	memcpy(PaddedBuffer, InputBuffer, InputBufferSize);
	*OutputPaddedBuffer = PaddedBuffer;
	*OutputPaddedSize = PaddedSize;

	return TRUE;
}

VOID AesTinyEncryption(IN PBYTE Data, OUT PBYTE OutputData, OUT PSIZE_T OutputDataSize) {
	
	struct AES_ctx ctx;


	BYTE pKey[KEYSIZE];                            
	BYTE pIv[IVSIZE];                              


	srand(time(NULL));                              
	GenerateRandomBytes(pKey, KEYSIZE);             

	srand(time(NULL) ^ pKey[0]);                    
	GenerateRandomBytes(pIv, IVSIZE);               

	PrintHexData("pKey", pKey, KEYSIZE);
	PrintHexData("pIv", pIv, IVSIZE);

	AES_init_ctx_iv(&ctx, pKey, pIv);


	PBYTE	PaddedBuffer = NULL;
	SIZE_T	PAddedSize = NULL;

	if (sizeof(Data) % 16 != 0) {
		PaddBuffer(Data, sizeof(Data), &PaddedBuffer, &PAddedSize);
		AES_CBC_encrypt_buffer(&ctx, PaddedBuffer, PAddedSize);
		PrintHexData("CipherText", PaddedBuffer, PAddedSize);
	}

	else {
		AES_CBC_encrypt_buffer(&ctx, Data, sizeof(Data));
		PrintHexData("CipherText", Data, sizeof(Data));
	}

	if (PaddedBuffer != NULL) {
		HeapFree(GetProcessHeap(), 0, PaddedBuffer);
	}
}
