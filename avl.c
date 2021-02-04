#include <stddef.h>

struct node {
	struct node *l;
	struct node *r;
	void *k;
	void *v;
	size_t h;
};

size_t HeightOf(const struct node *p)
{
	return p ? p->h : 0;
}
