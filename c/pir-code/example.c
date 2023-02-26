#include "pir.h"
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	pir_t out;

	setlocale(LC_ALL, "");

	pir_code_init(&out);
	pir_code_write(L"Lyssavirus", &out);

	wprintf(L"%.*s\n", PIR_CODE_LENGTH, &out);
	
	return 0;
}