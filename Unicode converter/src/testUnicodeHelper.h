#ifndef TEST_UNICODE_HELPER_H
#define TEST_UNICODE_HELPER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


uint32_t get_size_utf_32(uint32_t* text);
int size_of_file(FILE* fic);
void text_writer(uint32_t* text, size_t, char* filename);
uint8_t* text_reader(char* src);

#endif
