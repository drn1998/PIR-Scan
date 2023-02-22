#include "pir.h"

wchar_t latinize_lowercase(wchar_t wc) {
	switch(wc) {
		case L'ä':
		case L'Ä':
		case L'â':
		case L'Â':
		case L'á':
		case L'Á':
		case L'à':
		case L'À':
			return L'a';
		case L'ö':
		case L'Ö':
		case L'ô':
		case L'Ô':
		case L'ó':
		case L'Ó':
		case L'ò':
		case L'Ò':
			return L'o';
		case L'ü':
			return L'u';
		default:
			return wc;
	}
}

const wchar_t * verb[] = {
		L" ", L"sch", L"ver", L"ab", L"ag", L"am", L"au", L"be", L"ch", L"ck", L"de",
		L"fr", L"ge", L"kl", L"ma", L"mi", L"nd", L"ng", L"nt", L"qu", L"ra",
		L"sp", L"st", L"tr", L"tz", L"un", L"wa", L"wi", L"e", L"n", L"i", L"s",
		L"a", L"b", L"d", L"f", L"g", L"h", L"k", L"l", L"m", L"o", L"p", L"r",
		L"t", L"u", L"v", L"w", L"z", L"ß", L"c", L"j", L"q", L"x", L"y"
	};

const char * code[] = {
		"950", "80", "89", "51", "52", "53", "54", "56", "57", "58", "60", "62", "64",
		"67", "70", "71", "72", "73", "74", "77", "79", "81", "82", "84", "85", "87",
		"91", "92", "1", "2", "3", "4", "50", "55", "59", "61", "63", "65", "66", "68",
		"69", "75", "76", "78", "83", "86", "88", "90", "93", "962", "963", "964", "965",
		"966", "967"
	};

void write_pir_code(const wchar_t * s, char c[PIR_CODE_LENGTH]) {
	unsigned short digits[PIR_CODE_LENGTH] = {0};
	size_t digits_pos = 0;

	register unsigned int i, j;
	register unsigned int offset = 0;

	wchar_t cp[256];

	if(wcslen(s) > 255) { return; }

	wcscpy(cp, s);

	for(i = 0; i < wcslen(cp); i++) {
		cp[i] = latinize_lowercase(cp[i]);
		cp[i] = towlower(cp[i]);
	}

	while(offset < wcslen(cp)) {
		for(i = 0; i < sizeof(code)/sizeof(char*); i++) {
			if(wcspfx(cp + offset, verb[i])) {
				for(j = 0; j < strlen(code[i]); j++) {
					digits[digits_pos % PIR_CODE_LENGTH] = (digits[digits_pos % PIR_CODE_LENGTH] + (code[i][j] - '0')) % 10;
					digits_pos++;
				}
				offset += wcslen(verb[i]);
				break;
			}
			if(1 + i == sizeof(code)/sizeof(char*)) {
				offset++;	// Skip unrecognized character
			}
		}
	}

	for(i = 0; i < PIR_CODE_LENGTH; i++) {
		c[i] = '0' + digits[i];
	}
}