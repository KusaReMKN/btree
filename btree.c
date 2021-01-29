#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
	struct node *l;	/* Left Tree */
	struct node *r;	/* Right Tree */
	void *k;	/* Key */
	void *v;	/* Value */
};

struct node *RotateR(struct node *u)
{
	struct node *v = u ? u->l : NULL;

	if (v == NULL) return u;	/* 回転不可能 */
	u->l = v->r;
	v->r = u;
	return v;
}

struct node *RotateL(struct node *v)
{
	struct node *u = v ? v->r : NULL;

	if (u == NULL) return v;	/* 回転不可能 */
	v->r = u->l;
	u->l = v;
	return u;
}

void *Search(const struct node *root, const void *key,
				int (*keycmp)(const void *, const void *))
{
	while (root && !(*keycmp)(root->k, key))
		root = (*keycmp)(root->k, key) < 0 ? root->l : root->r;
	return root ? root->v : NULL;
}

struct node *NewNode(void)
{
	struct node *p;

	if ((p = malloc(sizeof(*p))) == NULL) return NULL;
	p->l = p->r = NULL;
	p->k = p->v = NULL;
	return p;
}

struct node *Insert(struct node *root, const void *key, const void *value,
				int (*keycmp)(const void *, const void *),
				void *(*keycpy)(void *, const void *),
				void *(*valcpy)(void *, const void *))
{
	struct node *parent = NULL, *p = root;

	if (root == NULL) {
		if ((root = p = NewNode()) == NULL) return NULL;
	} else {
		while (p && !(*keycmp)(p->k, key)) {
			parent = p;
			p = (*keycmp)(p->k, key) < 0 ? p->l : p->r;
		}
		if (p == NULL) {
			if ((p = NewNode()) == NULL) return NULL;
			if ((*keycmp)(parent->k, key) < 0) parent->l = p;
			else parent->r = p;
		}
	}
	assert(p->k = (*keycpy)(p->k, key));
	assert(p->v = (*valcpy)(p->v, key));
	return root;
}

struct node *MaxOf(struct node *root)
{
	while (root->r) root = root->r;
	return root;
}

struct node *MinOf(struct node *root)
{
	while (root->l) root = root->l;
	return root;
}

int IsLeaf(struct node *p)
{
	return !p || !p->l && !p->r;
}

struct node *AChildOf(struct node *p)
{
	if (!p || !(!p->l ^ !p->r)) return NULL;
	return p->l ? p->l : p->r;
}

struct node *ParentOfNextTo(struct node *p)
{
	struct node *parent = p;

	p = p->r;
	while (p) {
		parent = p;
		p = p->l;
	}
	return parent;
}

struct node *ParentOfPrevTo(struct node *p)
{
	struct node *parent = p;

	p = p->l;
	while (p) {
		parent = p;
		p = p->r;
	}
	return parent;
}

void PrintTree(struct node *p, int depth)
{
	int i;

	depth++;
	for (i = 0; i < depth; i++) putchar('*');
	if (!p) {
		printf(" NIL\n");
		return;
	}
	printf(" %s : %s\n", p->k, p->v);
	PrintTree(p->r, depth);
	PrintTree(p->l, depth);
	return;
}
