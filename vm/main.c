#include "main.h"
#include "list.h"

char *mem = NULL;
int mem_length = 0;

int main(int argc, char const *argv[]) {
	/* code */
	
	FILE *fp = fopen("../test/out.bin", "rb");
	if(!fp) {
		printf("Unable to load\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	mem = malloc(fsize);
	mem_length = fsize;
	if(fread(mem, 1, fsize, fp) != fsize) {
		printf("Unable to preperly read file\n");
		exit(1);
	}
	fclose(fp);

	dump_instructions();

	return 0;
}

void dump_instructions() {
	int i = 0;
	uint16_t label_length = (uint16_t)*(mem + i);
	i += sizeof(uint16_t);
	char label[label_length + 1];
	memcpy(label, mem + i, label_length);
	label[label_length] = '\0';
	i += label_length;
	while(1) {
		
	}
}