#include "pir.h"
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	pir_t out;
	wchar_t comp[255];

	setlocale(LC_ALL, "");

	if(argc != 2) {
		return -1;
	}

	swprintf(comp, 255, L"%s", argv[1]);

	pir_code_init(&out);
	pir_code_write(comp, &out);

	wprintf(L"%.*s\n", PIR_CODE_LENGTH, out.pir);
	
	return 0;
}