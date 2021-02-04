#include <stddef.h>
#include <stdlib.h>

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

struct node *RotateLR(struct node *p)
{
	if (!p || !p->l) return p;
	p->l = RotateL(p->l);
	return RotateR(p);
}

struct node *RotateRL(struct node *p)
{
	if (!p || !p->r) return p;
	p->r = RotateR(p->r);
	return RotateL(p);
}

struct node **RelatedNodesOf(const struct node *root, const void *key,
				int (*keycmp)(const void *, const void *))
{
	struct node **v = NULL, **tmp;
	size_t items = 1;
	int cmp;

	while (root && (cmp = (*keycmp)(root->k, key))) {
		if (!(tmp = realloc(v, ++items * sizeof(*v)))) {
			free(v);
			return NULL;
		}
		v = tmp;
		v[items - 2] = (struct node *)root;
		root = cmp < 0 ? root->l : root->r;
	}
	v[items - 1] = NULL;
	return v;
}

size_t LengthOf(const struct node **v)
{
	size_t i;

	for (i = 0; v[i] && v[i + 1]; i++);
	return i;
}

struct node *NodeOf(const struct node *root, const void *key,
				int (*keycmp)(const void *, const void *))
{
	int cmp;

	while (root && (cmp = (*keycmp)(root->k, key)))
		root = cmp < 0 ? root->l : root->r;
	return (struct node *)(root ? root : NULL);
}

void *Search(const struct node *root, const void *key,
				int (*keycmp)(const void *, const void *))
{
	struct node *tmp = NodeOf(root, key, keycmp);

	return tmp ? tmp->r : NULL;
}
