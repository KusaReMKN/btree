#include <stddef.h>

struct node {
	struct node *l;
	struct node *r;
	void *k;
	void *v;
	size_t h;
};
