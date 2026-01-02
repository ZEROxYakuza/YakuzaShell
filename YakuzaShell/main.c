#include <Windows.h>
#include <stdio.h>
#include "Functions.h"

#define AESKEYSIZE 32
#define AESIVSIZE 16

INT PrintHelp(IN CHAR* _Argv0) {
	printf("\t\t\t ################################\n");
	printf("\t\t\t # YakuzaShell - By ZEROxYakuza #\n");
	printf("\t\t\t ################################\n\n");

	printf("[!] Usage: %s <Option>\n", _Argv0);
	printf("[i] Options Can Be : \n");
	printf("\t1.>>> \"aes\"     ::: Output The File As A Encrypted File Using Aes-256 Algorithm With Random Key And Iv \n");
	printf("\t[i] Usage for aes option: %s aes <Input Payload FileName> <Output FileName>\n", _Argv0);

	printf("\n[i] ");
	system("PAUSE");
	return -1;

}


int main(int argc, char* argv[]) {


	PBYTE	pPayloadInput = NULL;
	DWORD	dwPayloadSize = NULL;

	PVOID	pCipherText = NULL;
	DWORD	dwCipherSize = NULL;

	if (argc != 4) {
		return PrintHelp(argv[0]);
	}


	if (strcmp(argv[1], "aes") != 0) {
		printf("<<<!>>> \"%s\" Is not Valid Input <<<!>>>\n", argv[2]);
		return PrintHelp(argv[0]);
	}

	if (!ReadPayloadFile(argv[2], &dwPayloadSize, &pPayloadInput)) {
		return -1;
	}


	if (strcmp(argv[1], "aes") == 0) {

		CHAR	KEY[AESKEYSIZE], KEY2[AESKEYSIZE];
		CHAR	IV[AESIVSIZE], IV2[AESIVSIZE];

		srand(time(NULL));
		GenerateRandomBytes(KEY, AESKEYSIZE);
		srand(time(NULL) ^ KEY[0]);
		GenerateRandomBytes(IV, AESIVSIZE);

		memcpy(KEY2, KEY, AESKEYSIZE);
		memcpy(IV2, IV, AESIVSIZE);

		AesTinyEncryption(pPayloadInput, &pCipherText, &dwCipherSize);

		PrintDecodeFunctionality();

		if (!WritePayloadFile(argv[3], dwCipherSize, pCipherText)) {
			MessageBoxA(NULL, "Failed To Write The Encrypted Bin File", "ERROR !", MB_OK | MB_ICONERROR);
		}

		goto _EndOfFunction;
	}



_EndOfFunction:
	if (pPayloadInput != NULL)
		HeapFree(GetProcessHeap(), 0, pPayloadInput);
	if (pCipherText != NULL)
		HeapFree(GetProcessHeap(), 0, pCipherText);
	return 0;
}

