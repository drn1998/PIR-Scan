#include "pir.h"
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	char out[5];

	setlocale(LC_ALL, "");

	write_pir_code(L"lyssavirus", out);
	wprintf(L"%.5s\n", out);
	
	return 0;
}