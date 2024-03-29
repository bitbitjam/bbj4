#include "Print.h"
#include "BankManager.h"
#include "Scroll.h"

#include <stdarg.h>

UINT8 print_x = 0;
UINT8 print_y = 0;
UINT8 font_idx = 128;
UINT8 print_target = PRINT_BKG;

#ifdef PRINT_HEX_ENABLED
// The following function is not part of the original ZGB engine and was added by InfectedBytes
void UIntToHexString(UINT16 n, unsigned char* str) {
	UINT16 tmp = n;
	UINT8 size = 0;
	unsigned char c;

	if (n == 0) {
		str[0] = '0';
		str[1] = '\0';
	} else {
		while (tmp) {
			tmp >>= 4;
			size++;
		}
		str[size--] = '\0';
		while (n) {
			c = n & 0xF;
			if (c < 0xA) str[size--] = '0' + c;
			else str[size--] = 'A' + c - 0xA;
			n >>= 4;
		}
	}
}
#endif

void UIntToString(UINT16 n, unsigned char* str) {
	UINT16 tmp = n;
	UINT8 size = 0;

	if(n == 0) {
		str[0] ='0';
		str[1] = '\0';
	} else {
		while(tmp) {
			tmp /= 10;
			size ++;
		}
		str[size] = '\0';
		size --;

		while(n) {
			str[size] = (n % 10) + '0';
			n /= 10;
			size --;
		}
	}
}

#ifdef PRINT_SIGNED_ENABLED
void IntToString(INT16 n, unsigned char* str) {
	int tmp = n;
	UINT8 size = 0;

	if(n < 0){
		n = 0xFFFF - n + 1; //I tried -n but it doesn't work
		str[0] = '-';
		str ++;
	}

	UIntToString(n, str);
}
#endif

void Printf(const char* txt, ...){
	UINT8 idx = 0;
	unsigned char c;
	unsigned char tmp[10];
	va_list list;

	va_start(list, txt); 
	while(*txt) {
		if(*txt == ' ') {
			c = font_idx;
		} else if(*txt >= 'A' && *txt <= 'Z'){
			c = font_idx +  1 + *txt - 'A';
		} else if(*txt >= 'a' && *txt <= 'z') {
			c = font_idx +  1 + *txt - 'a';
		} else if(*txt >= '0' && *txt <= '9') {
			c = font_idx + 27 + *txt - '0';
		} else {
			switch(*txt) {
				case  '!': c = font_idx + 37; break;
				case '\'': c = font_idx + 38; break;
				case  '(': c = font_idx + 39; break;
				case  ')': c = font_idx + 40; break;
				case  '-': c = font_idx + 41; break;
				case  '.': c = font_idx + 42; break;
				case  ':': c = font_idx + 43; break;
				case  '?': c = font_idx + 44; break;
				case  '*': c = font_idx + 45; break;
				case  '�': c = font_idx + 46; break;
				case  '@': c = font_idx + 47; break;
				case  '_': c = font_idx + 48; break;
				case  '%':
					switch(*(txt + 1)) {
#ifdef PRINT_SIGNED_ENABLED
						case 'd':
						case 'i':
							IntToString(va_arg(list, INT16), tmp);
							Printf(tmp);
							txt += 2;
							continue;
#endif

						case 'u':
							UIntToString(va_arg(list, UINT16), tmp);
							Printf(tmp);
							txt += 2;
							continue;
#ifdef PRINT_HEX_ENABLED
						case 'x':
							UIntToHexString(va_arg(list, UINT16), tmp);
							Printf(tmp);
							txt += 2;
							continue;
#endif
					}
					break;
			}
		}
		if(print_target == PRINT_BKG)
			set_bkg_tiles(0x1F & (print_x + scroll_offset_x), 0x1F & (print_y + scroll_offset_y), 1, 1, &c);
		else
			set_win_tiles(print_x, print_y, 1, 1, &c);

		print_x ++;
		txt ++;
	}
	va_end(list);
}
