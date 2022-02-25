#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unicode.h"
#include <wchar.h>
#include "testUnicodeHelper.h"

int main(int argc, char* argv[])
{
	FILE* fic1;
	fic1 = fopen("fichier.txt", "wb");
	FILE* fic2;
	if (argc == 3){
		if (argv[1][0] == '+'){
			fic2 = fopen(argv[2], "rb");
			if (!fic2) return 1;
			UTF32* text = malloc(sizeof(UTF32)* size_of_file(fic2));
			fread(text, 1, size_of_file(fic2), fic2);
			UTF8* dest = unicode_32_to_utf8(text);
			for(UTF32 i = 0; i < utf8_strlen(dest); ++i){
				fprintf(fic1, "%c",dest[i]);
			}	
			printf("Vérifiez le contenu de 'fichier.txt'\n");
			free(dest);
			free(text);	
		}
		else if (argv[1][0] == '-'){
			fic2 = fopen(argv[2], "rb");
			if (!fic2) return 1;
			UTF8* text = malloc(sizeof(UTF8)* size_of_file(fic2));
			fread(text, 1, size_of_file(fic2)*4, fic2);
			UTF32* dest = utf8_to_unicode_32(text);
			for(UTF32 i = 0; i < strlen_utf32(dest); ++i){
				fprintf(fic1, "%4c", dest[i]);
			}
			printf("Vérifiez le contenu de 'fichier.txt'\n");
			free(text);
			free(dest);
		}
		else{
			fprintf(stderr, "ERROR!, Entrez - ou +\n");
		}
	}else{
		fprintf(stderr, "ERROR!\n");
		//printf("%d %s %s %s", argc, argv[0], argv[1], argv[2]);
	}
	return 0;
}
