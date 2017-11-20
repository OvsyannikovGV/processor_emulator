#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define num_ptrs 32
#define steck_size 16777216
#define register_num 6

#include "commands.h"
#include "steck.h"

int getcmd(struct command * cmd, FILE * input) {
	fread(&cmd->id, sizeof(unsigned char), 1, input);
	if (stdcmd[cmd->id].value) {
		fread(&cmd->value, sizeof(double), 1, input);
	}
	if (stdcmd[cmd->id].ptr_id) {
		fread(&cmd->ptr_id, sizeof(unsigned char), 1, input);
	}
	if (stdcmd[cmd->id].rgstr_id) {
		fread(&cmd->rgstr_id, sizeof(unsigned char), 1, input);
	}
	return cmd->id;
}

int runcmd(struct command cmd, struct steck * ram, double * rgstrs, FILE * input, unsigned char num_ptr, long int * ptrs) {
	double a, b;
	switch(cmd.id) {
		case 0:
			return 0;
		case 1:
			Steck_push(ram, cmd.value);
			return 0;
		case 2:
			Steck_pop(ram);
			return 0;
		case 3:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			Steck_push(ram, a + b);
			return 0;
		case 4:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			Steck_push(ram, a - b);
			return 0;
		case 5:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			Steck_push(ram, a*b);
			return 0;
		case 6:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			Steck_push(ram, a/b);
			return 0;
		case 7:
			a = Steck_pop(ram);
			Steck_push(ram, sin(a));
			return 0;
		case 8:
			a = Steck_pop(ram);
			Steck_push(ram, cos(a));
			return 0;
		case 9:
			a = Steck_pop(ram);
			Steck_push(ram, sqrt(a));
			return 0;
		case 10:
			a = Steck_pop(ram);
			rgstrs[cmd.rgstr_id] = a;
			return 0;
		case 11:
			Steck_push(ram, rgstrs[cmd.rgstr_id]);
			return 0;
		case 13:
			fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			return 0;
		case 14:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			if (a == b)
				fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			Steck_push(ram, a);
			Steck_push(ram, b);
			return 0;
		case 15:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			if (a != b)
				fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			Steck_push(ram, a);
			Steck_push(ram, b);
			return 0;
		case 16:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			if (a > b)
				fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			Steck_push(ram, a);
			Steck_push(ram, b);
			return 0;
		case 17:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			if (a >= b)
				fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			Steck_push(ram, a);
			Steck_push(ram, b);
			return 0;
		case 18:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			if (a < b)
				fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			Steck_push(ram, a);
			Steck_push(ram, b);
			return 0;
		case 19:
			a = Steck_pop(ram);
			b = Steck_pop(ram);
			if (a <= b)
				fseek(input, ptrs[cmd.ptr_id] + num_ptr*sizeof(long int) + sizeof(unsigned char), SEEK_SET);
			Steck_push(ram, a);
			Steck_push(ram, b);
			return 0;
		case 20:
			scanf("%lg", &a);
			Steck_push(ram, a);
			return 0;
		case 21:
			a = Steck_pop(ram);
			printf("%lg\n", a);
			Steck_push(ram, a);
			return 0;
		default:
			return 1;
	}
}

int main() {
	struct steck ram;
	Steck_ctor(&ram, steck_size);
	double rgstrs[register_num];
	FILE * input = fopen("execute.bin", "rb");
	long int ptrs[num_ptrs] = {0}; //__________________________memory for pointers
	unsigned char num_ptr = 0;
	struct command cmd;

	fread(&num_ptr, sizeof(unsigned char), 1, input);

	fread(ptrs, sizeof(long int), num_ptr, input);

	while (getcmd(&cmd, input))
		runcmd(cmd, &ram, rgstrs, input, num_ptr, ptrs);
	Steck_dtor(&ram);
	fclose(input);
}