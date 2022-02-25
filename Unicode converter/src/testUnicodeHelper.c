#include <stdio.h>
#include <stdlib.h>
#include "testUnicodeHelper.h"
#include <stdint.h>

int size_of_file(FILE* fic){
	if (fic == NULL){
		fprintf(stderr, "File Error.\n");
		return -1;
	}
	fseek(fic, 0, SEEK_END);
	int size = ftell(fic);
	fseek(fic, 0, SEEK_SET);
	return size;
}

uint32_t get_size_utf_32(uint32_t* text){
	uint32_t size = 0;
	while(text[size++]);
	return size;
}

uint8_t* text_reader(char* src){
	FILE *fic;
	fic = fopen(src, "rb");
	if (!fic){
		fprintf(stderr, "Erreur lors de l'ouverture des fichiers\n");
		return NULL;
	}
	uint8_t* texte = malloc(sizeof(char)*size_of_file(fic));
	fread(texte, 1, size_of_file(fic), fic);
	return texte;
}

void text_writer(uint32_t* text_u32, size_t size, char* filename){
	FILE* fic = fopen(filename, "wb");
	if (!fic){
		fprintf(stderr, "Erreur while openning the file.\n");
		return;
	}
	char* text = malloc(sizeof(char) * get_size_utf_32(text_u32));
	for(uint32_t i = 0; i < get_size_utf_32(text_u32); ++i){
		text[i] = (char)text_u32[i];
	}
	// Check for the \0
	fwrite(text, 1, size, fic);
	
}
