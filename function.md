# 関数一覧

## RotateR, RotateL

```c
struct node *RotateR(struct node *u);
struct node *RotateL(struct node *u);
```

渡されたノード `u` を根とする木を(右|左)回転する．
回転不可能な場合，変更されていない木の根ノード `u` が返る．
回転可能な場合，回転後の木の根ノードが返る．

## Search

```c
void *Search(const struct node *root, const void *key,
				int (*keycmp)(const void *, const void *));
```

渡されたノード `root` を根とする木のうち，検索キー `key` に対応する値を探す．
関数 `keycmp` は `qsort(3)` や `bsearch(3)` の比較関数と同様の要件．
返り値は値へのポインタ (見つからなければ NULL)．

## NewNode

```c
struct node *NewNode(void);
```

新しいノードを作成する．
新しいノードの要素は NULL に初期化されている．
返り値はノードへのポインタ (失敗時は NULL)．

## Insert

```c
struct node *Insert(struct node *root, const void *key, const void *value,
				int (*keycmp)(const void *, const void *),
				void *(*keycpy)(void *, const void *),
				void *(*valcpy)(void *, const void *));
```

根ノード `root` にノードを挿入 (すでに存在している場合は置換) する．
`root` は NULL 可能である．
返り値は挿入後の木の根ノード．
`keycpy` や `valcpy` は(キー|値)のコピーを行う関数
例えば:

```c
void *my_keycpy(void *prev, const void *newkey)
{
	char *p;

	free(prev);
	if ((p = malloc(strlen(newkey) + 1)) == NULL)
		return NULL;
	strcpy(p, newkey);
	return p;
}
```

## MaxOf, MinOf

```c
struct node *MaxOf(struct node *root);
struct node *MinOf(struct node *root);
```

ノード `root` を根とする木のうちで最(大|小)のノードへのポインタを返す．
