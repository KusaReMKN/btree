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

struct node **RelNodesOf(const struct node *root, const void *key,
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

size_t LengthOf(struct node ***v)
{
	size_t i;

	for (i = 0; v[i]; i++);
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

	return tmp ? tmp->v : NULL;
}

struct node *NewNode(void)
{
	struct node *p;

	if (!(p = malloc(sizeof(*p)))) return NULL;
	p->l = p->r = NULL;
	p->k = p->v = NULL;
	p->h = 1;
	return p;
}

int BiasOf(const struct node *p)
{
	return p ? (int)HeightOf(p->l) - (int)HeightOf(p->r) : 0;
}

struct node *Balance(struct node *p)
{
	int b;

	if (abs(b = BiasOf(p)) < 2) return p;
	if (b < 0) p = BiasOf(p->r) < 0 ? RotateL(p) : RotateRL(p);
	else p = BiasOf(p->l) > 0 ? RotateR(p) : RotateLR(p);
	return p;
}

struct node ***RefToRelNodesOf(const struct node *root, const void *key,
				int (*keycmp)(const void *, const void *))
{
	struct node ***v = NULL, ***tmp;
	size_t len = 1;
	int cmp;

	if (!(v = malloc(sizeof(*v)))) return NULL;
	while (root && (cmp = (*keycmp)(root->k, key))) {
		if (!(tmp = realloc(v, ++len * sizeof(*v)))) {
			free(v);
			return NULL;
		}
		v = tmp;
		if (cmp < 0) {
			v[len - 2] = (struct node **)&root->l;
			root = root->l;
		} else {
			v[len - 2] = (struct node **)&root->r;
			root = root->r;
		}
	}
	v[len - 1] = NULL;
	return v;
}

struct node *Insert(struct node *root, const void *key, const void *val,
				int (*keycmp)(const void *, const void *),
				void *(*keycpy)(void *, const void *),
				void *(*valcpy)(void *, const void *))
{
	struct node ***v = RefToRelNodesOf(root, key, keycmp);
	struct node **pdest;
	struct node *dest;
	size_t l = 0;

	if (!v) return NULL;
	if (!root) {
		if (!(root = dest = NewNode())) {
			free(v);
			return NULL;
		}
	} else {
		pdest = (l = LengthOf(v)) == 0 ? &root : v[l - 1];
		if (!(dest = *pdest)) {
			if (!(dest = NewNode())) {
				free(v);
				return NULL;
			}
			*pdest = dest;
		}
	}
	dest->k = (*keycpy)(dest->k, key);
	dest->v = (*valcpy)(dest->v, val);
	for (; l > 0; l--) {
		(*v[l-1])->h = CalcHeight(*v[l-1]);
		*v[l-1] = Balance(*v[l-1]);
	}
	free(v);
	return Balance(root);
}

int IsLeaf(struct node *p)
{
	return !p || !p->l && !p->r;
}

struct node *AChildOf(const struct node *p)
{
	if (!p || !(!p->l ^ !p->r)) return NULL;
	return p->l ? p->l : p->r;
}

struct node ***RefToRelNodesOfNextToLastOf(struct node ***v)
{
	struct node ***tmp;
	struct node *p;
	size_t l;

	if (!v || (l = LengthOf(v)) == 0) return v;
	p = *v[l - 1];
	l += 2;
	if (!(tmp = realloc(v, l * sizeof(*v)))) {
		free(v);
		return NULL;
	}
	v = tmp;
	v[l - 2] = &p->r;
	p = p->r;

	while (p && p->l) {
		if (!(tmp = realloc(v, ++l * sizeof(*v)))) {
			free(v);
			return NULL;
		}
		v = tmp;
		v[l - 2] = &p->l;
		p = p->l;
	}
	v[l-1] = NULL;
	return v;
}

struct node *Remove(struct node *root, const void *key,
				int (*keycmp)(const void *, const void *),
				void (*keyfree)(void *),
				void (*valfree)(void *))
{
	struct node ***v = RefToRelNodesOf(root, key, keycmp), ***vtmp;
	struct node **pdest, **pnext;
	struct node *dest, *tmp, *next;
	size_t l, ldest;

	if (!v) return NULL;
	if ((l = LengthOf(v)) == 0) {
		if (!(vtmp = realloc(v, ++l * sizeof(*v)))) {
			free(v);
			return NULL;
		}
		v = vtmp;
		v[0] = &root;
		v[1] = NULL;
	}
	pdest = v[l-1];
	if (!(dest = *pdest)) return root;

	if (IsLeaf(dest)) {
		*pdest = NULL;
		v[--l] = NULL;
	} else if ((tmp = AChildOf(dest))) {
		*pdest = tmp;
		v[--l] = NULL;
	} else {
		ldest = l;
		if (!(v = RefToRelNodesOfNextToLastOf(v))) return NULL;
		l = LengthOf(v);
		pnext = v[--l];
		next = *pnext;
		*pnext = AChildOf(next);
		*pdest = next;
		next->r = dest->r;
		next->l = dest->l;
		v[ldest] = &next->r;
	}

	(*keyfree)(dest->k);
	(*valfree)(dest->v);
	free(dest);

	for (; l > 0; l--) {
		(*v[l-1])->h = CalcHeight(*v[l-1]);
		*v[l-1] = Balance(*v[l-1]);
	}
	free(v);
	return Balance(root);
}
