#include "pir.h"
#include <wchar.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	char out[5];
	
	write_pir_code(L"Lyssavirus", out);
	wprintf(L"%.5s\n", out);
	
	return 0;
}