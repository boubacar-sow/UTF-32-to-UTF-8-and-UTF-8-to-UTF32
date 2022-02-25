#include "unicode.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

size_t utf8_codepoint_size(const uint8_t byte) {
	if (byte < 0x80) {
        return 1;
    } else if ((byte & 0xe0) == 0xc0) {
        return 2;
    } else if ((byte & 0xf0) == 0xe0) {
        return 3;
    } else if ((byte & 0xf8) == 0xf0) {
        return 4;
    }
	return 0;
}

size_t utf32_codepoint_size(const uint32_t byte){
	if (byte <= 0x007F)
		return 1;
	else if (byte <= 0x07FF)
		return 2;
	else if (byte <= 0xFFFF)
		return 3;
	else if (byte <= 0x1FFFFF)
		return 4;
	return 0;
}

size_t strlen_utf32(UTF32* text){
	size_t count_chars = 0;
	size_t i = 0;
	while(text[i]){
		count_chars++;
		i += utf32_codepoint_size(text[i]);
	}
	return count_chars;
}


size_t utf8_strlen(const uint8_t* text){
	size_t i = 0;
	size_t count_chars = 0;
	
	while(text[i]){
		count_chars += 1;
		i += utf8_codepoint_size(text[i]);
	}
	return count_chars;
}

UTF32* utf8_to_unicode_32(uint8_t* text){
	size_t count_chars = utf8_strlen(text); 
	UTF32* string_in_unicode_32 = malloc(sizeof(UTF32) * (count_chars + 1)); /*+1 Pour le caractère terminal*/
	if (!string_in_unicode_32)
		return NULL;
	
	size_t i = 0;
	for(size_t n = 0; n < count_chars; ++n){
		size_t char_size = utf8_codepoint_size(text[i]);
		
		switch(char_size){
			case 1:
			string_in_unicode_32[n] = ((uint32_t) text[i]);
			break;
		case 2:
			string_in_unicode_32[n] =
				((uint32_t) (text[i] & 0x1f) << 6) |
				((uint32_t) (text[i + 1] & 0x3f) << 0);
			break;
		case 3:
			string_in_unicode_32[n] =
				((uint32_t) (text[i] & 0x0f) << 12) |
				((uint32_t) (text[i + 1] & 0x3f) << 6) |
				((uint32_t) (text[i + 2] & 0x3f) << 0);
			break;
		case 4:
			string_in_unicode_32[n] =
				((uint32_t) (text[i] & 0x07) << 18) | 
				((uint32_t) (text[i + 1] & 0x3f) << 12) |
				((uint32_t) (text[i + 2] & 0x3f) << 6) |
				((uint32_t) (text[i + 3] & 0x3f) << 0);
			break;	
		default:
			fprintf(stderr, "ERROR, INVALID BYTE IN GIVEN UTF8 STRING.\n"); 
			return 0;
		}

		i += char_size;
		}
		string_in_unicode_32[count_chars] = '\0';
		return string_in_unicode_32;
}

UTF8* unicode_32_to_utf8(UTF32* text){
	size_t count_chars = strlen_utf32(text);
	UTF8* string_in_utf8 = malloc(sizeof(uint8_t)*(count_chars*4));
	if (!string_in_utf8) return NULL;
	
	size_t i = 0;
	for(size_t n = 0; n < 1000;){
		size_t char_size = utf32_codepoint_size(text[i]);
		switch(char_size){
			case 1:
				string_in_utf8[n] = text[i];
				break;
			case 2:
				string_in_utf8[n] = 0xC0| text[i] >> 6;
				string_in_utf8[n+1] = 0x80 | (text[i] & 0x3F);
				break;
			case 3:
				string_in_utf8[n] = 0xE0 | (text[i] >> 12);
				string_in_utf8[n+1] = 0x80 | ((text[i] >> 6) & 0x3F);
				string_in_utf8[n+2] = 0x80 | (text[i] & 0x3F);
				break;
			case 4:
				string_in_utf8[n] = 0xF0 | (text[i] >> 18);
				string_in_utf8[n+1] = 0x80 | ((text[i] >> 12)  & 0x3F000);
				string_in_utf8[n+2] = 0x80 | ((text[i] >> 6)  & 0xFC0);
				string_in_utf8[n+3] = 0x80 | (text[i] & 0x3F);
				break;
			default:
				fprintf(stderr, "ERROR, INVALID BYTE IN GIVEN UTF32 STRING.\n");
				return NULL;
			}
		i += 1;
		n+=char_size;
	}
	string_in_utf8[count_chars] = '\0';
	return string_in_utf8;
}
