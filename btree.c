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
