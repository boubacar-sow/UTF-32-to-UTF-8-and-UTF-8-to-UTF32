#ifndef _UNICODE_H
#define _UNICODE_H
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef uint32_t UTF32;

typedef uint8_t UTF8;

size_t utf8_strlen(const uint8_t* text);

size_t utf8_codepoint_size(const uint8_t byte);

UTF32* utf8_to_unicode_32(UTF8*);

UTF8* unicode_32_to_utf8(UTF32*);

size_t strlen_utf32(UTF32* text);

size_t utf32_codepoint_size(const uint32_t byte);


#endif
