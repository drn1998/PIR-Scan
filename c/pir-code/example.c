#include "pir.h"
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	char out[PIR_CODE_LENGTH];

	setlocale(LC_ALL, "");

	write_pir_code(L"lyssavirus", out);
	wprintf(L"%.*s\n", PIR_CODE_LENGTH, out);
	
	return 0;
}