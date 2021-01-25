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
