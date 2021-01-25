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
