# MKNMAP &#x2014; Associative Array for C

## MKNMAP is なに

MKNMAP はあらゆる型の値を添字として利用できる連想配列を実現します．

## どうやって使うの

文字列に文字列を対応させる例です:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mknmap.h"

/* 文字列を新しい領域にコピーする関数 */
void *copier(void *prev, const void *newer)
{
	void *tmp = realloc(prev, strlen(newer) + 1);
	if (tmp == NULL) return NULL;
	strcpy(tmp, newer);
	return tmp;
}

int main(void)
{
	mknmap mp;

	/* 連想配列を作成 */
	mp = NewMap((void *)strcmp, copier, copier, free, free);
	if (mp == NULL) exit(EXIT_FAILURE);

	/* 値をセット */
	PutItem(mp, "foo", "hoge");	/* mp["foo"] = "hoge" */
	PutItem(mp, "bar", "fuga");	/* mp["bar"] = "fuga" */
	PutItem(mp, "baz", "piyo");
	PutItem(mp, "qux", "poyo");

	/* 値の参照 */
	printf("bar : %s\n", (char *)GetItem(mp, "bar"));	/* fuga */
	printf("qux : %s\n", (char *)GetItem(mp, "qux"));	/* poyo */

	/* 値の上書き */
	PutItem(mp, "bar", "fugafuga");
	printf("bar : %s\n", (char *)GetItem(mp, "bar"));	/* fugafuga */

	/* 値の削除 */
	RemoveItem(mp, "qux");
	printf("qux : %s\n", (char *)GetItem(mp, "qux"));	/* (null) */

	/* 連想配列の解放 */
	DeleteMap(mp);

	return 0;
}
```

## 関数一覧

そのうち書きます．

## ライセンス

MIT License
