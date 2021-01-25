# 関数一覧

## RotateR, RotateL

```c
struct node *RotateR(struct node *u);
struct node *RotateL(struct node *u);
```

渡されたノード `u` を根とする木を(右|左)回転する．
回転不可能な場合，変更されていない木の根ノード `u` が返る．
回転可能な場合，回転後の木の根ノードが返る．
