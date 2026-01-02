#pragma once
#include <Windows.h>

BOOL PaddBuffer(IN PBYTE InputBuffer, IN SIZE_T InputBufferSize, OUT PBYTE* OutputPaddedBuffer, OUT SIZE_T* OutputPaddedSize);

VOID AesTinyEncryption(IN PBYTE Data, OUT PBYTE OutputData, OUT PSIZE_T OutputDataSize);

BOOL ReportError(const char* ApiName);

BOOL ReadPayloadFile(const char* FileInput, PDWORD sPayloadSize, unsigned char** pPayloadData);

BOOL WritePayloadFile(const char* FileInput, DWORD sPayloadSize, unsigned char* pPayloadData);

INT PrintHelp(IN CHAR* _Argv0);

VOID GenerateRandomBytes(PBYTE pByte, SIZE_T sSize);

VOID PrintHexData(LPCSTR Name, PBYTE Data, SIZE_T Size);

VOID PrintDecodeFunctionality();
