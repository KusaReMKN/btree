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

struct node *HigherOf(const struct node *a, const struct node *b)
{
	size_t ah = HeightOf(a), bh = HeightOf(b);

	return (struct node *)(ah > bh ? a : b);
}

size_t CalcHeight(const struct node *p)
{
	return p ? HeightOf(HigherOf(p->l, p->r)) + 1 : 0;
}

struct node *RotateR(struct node *p)
{
	struct node *tmp = p ? p->l : NULL;

	if (!tmp) return p;
	p->l = tmp->r;
	tmp->r = p;
	p->h = CalcHeight(p);
	tmp->h = CalcHeight(tmp);
	return tmp;
}

struct node *RotateL(struct node *p)
{
	struct node *tmp = p ? p->r : NULL;

	if (!tmp) return p;
	p->r = tmp->l;
	tmp->l = p;
	p->h = CalcHeight(p);
	tmp->h = CalcHeight(tmp);
	return tmp;
}
