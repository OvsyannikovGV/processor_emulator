#ifndef PROC_STECK_H
#define PROC_STECK_H

struct steck {
	void * ptr;
	size_t last_elem;
};

int Steck_ctor(struct steck * ram, size_t size) {
	ram->ptr = calloc(size, 1);
	ram->last_elem = 0;
	return (ram->ptr) ? 0 : 1;
}

int Steck_push(struct steck * ram, double x) {
	*(double *)(ram->ptr + ram->last_elem) = x;
	ram->last_elem += sizeof(double);
	return 0;
}

double Steck_pop(struct steck * ram) {
	if (ram->last_elem >= sizeof(double))
		ram->last_elem -= sizeof(double);
	return *(double *)(ram->ptr + ram->last_elem + sizeof(double));
}

int Steck_dtor(struct steck * ram) {
	free(ram->ptr);
	return 0;
}

#endif //PROC_STECK_H
