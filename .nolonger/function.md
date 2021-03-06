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

## IsLeaf

```c
int IsLeaf(struct node *p);
```

ノード `p` が末端ノード (葉ノード) かどうか調べる

## AChildOf

```c
struct node *AChildOf(struct node *p);
```

ノード `p` がただ一つの子ノードを持つときにそのノードへのポインタを返す．

## ParentOfNextTo, ParentOfPrevTo

```c
struct node *ParentOfNextTo(struct node *p);
struct node *ParentOfPrevTo(struct node *p);
```

ノード `p` の(次|前)の要素の親ノードへのポインタを返す．
それは `p` 自身かもしれない．

## PrintTree

```c
void PrintTree(struct node *p, int depth);
```

二分木の構造を標準出力に書き出す．
初回呼び出しの時，第二引数には常に 0 を指定すること．
書き出されたリストは plantuml.com の mindmap 形式でプロットすることで図が得られる．
この関数はノードのキー，値の要素が文字列であることを前提としている．

## ParentOf

```c
struct node *ParentOf(struct node *root, const void *key,
				int (*keycmp)(const void *, const void *))
```

渡されたノード `root` を根とする木のうち，検索キー `key` に対応するノードの親を探す．
`key` に対応するノードが `root` であってはならない．
返り値はへ親ノードへのポインタ (見つからなければ NULL)．

## RefToNextTo, RefToPrevTo

```c
struct node **RefToNextTo(struct node *p);
struct node **RefToPrevTo(struct node *p);
```

ノード `p` の(前|次)のノードを指す参照へのポインタを返す．

## Remove

```c
struct node *Remove(struct node *root, const void *key,
				int (*keycmp)(const void *, const void *),
				void (*delkey)(void *), void (*delval)(void *));
```

渡されたノード `root` を根とする木から，検索キー `key` に対応するノードを取り除く．
返り値は削除後の木の根ノードを指すポインタ．
`key` に対応するノードがない場合は何も行われない．
`delkey` や `delval` は(キー|値)の領域を解放する関数．
例えば:

```c
void my_delkey(void *p)
{
	free(p);
}
```

## PrintNode

```c
void PrintNode(struct node *p);
```

渡されたノード `p` の情報を標準出力に書き出す．
