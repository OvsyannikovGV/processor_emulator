#ifndef PROC_COMMANDS_H
#define PROC_COMMANDS_H

#define cmd_push 1
#define cmd_pop 2
#define cmd_add 3
#define cmd_sub 4
#define cmd_mul 5
#define cmd_div 6
#define cmd_sin 7
#define cmd_cos 8
#define cmd_sqrt 9
#define cmd_push_register 10
#define cmd_pop_register 11
#define cmd_declare_ptr 12
#define cmd_jmp 13
#define cmd_je 14
#define cmd_jne 15
#define cmd_ja 16
#define cmd_jae 17
#define cmd_jb 18
#define cmd_jbe 19
#define cmd_in 20
#define cmd_out 21

struct command {
	unsigned char id;
	double value;
	unsigned char rgstr_id;
	unsigned char ptr_id;
	long int ptr;
};

struct stdcommand {
	unsigned char id;
	char value;
	char input_from_steck;
	char output_to_steck;
	char rgstr_id;
	char ptr_id;
	char name[5];
};


//  i == stdcmd[i].id
struct stdcommand stdcmd[23] = {{0, 0, 0, 0, 0, 0, "end\0"},//________end 0f program
								{cmd_push, 1, 0, 1, 0, 0, "push\0"},
								{cmd_pop, 0, 1, 0, 0, 0, "pop\0"},
								{cmd_add, 0, 2, 1, 0, 0, "add\0"},
								{cmd_sub, 0, 2, 1, 0, 0, "sub\0"},
								{cmd_mul, 0, 2, 1, 0, 0, "mul\0"},
								{cmd_div, 0, 2, 1, 0, 0, "div\0"},
								{cmd_sin, 0, 2, 1, 0, 0, "sin\0"},
								{cmd_cos, 0, 1, 1, 0, 0, "cos\0"},
								{cmd_sqrt, 0, 1, 1, 0, 0, "sqrt\0"},
								{cmd_push_register, 0, 1, 1, 1, 0, "push\0"},
								{cmd_pop_register, 0, 1, 0, 1, 0, "pop\0"},
								{cmd_declare_ptr, 0, 0, 0, 0, 0, ":x\0"},
								{cmd_jmp, 0, 2, 2, 0, 1, "jump\0"},
								{cmd_je, 0, 2, 2, 0, 1, "je\0"},
								{cmd_jne, 0, 2, 2, 0, 1, "jne\0"},
								{cmd_ja, 0, 2, 2, 0, 1, "ja\0"},
								{cmd_jae, 0, 2, 2, 0, 1, "jae\0"},
								{cmd_jb, 0, 2, 2, 0, 1, "jb\0"},
								{cmd_jbe, 0, 2, 2, 0, 1, "jbe\0"},
								{cmd_in, 0, 0, 1, 0, 0, "in\0"},
								{cmd_out, 0, 1, 1, 0, 0, "out\0"}};

#endif //PROC_COMMANDS_H
