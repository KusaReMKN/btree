# 関数一覧

## NewMap &#x2014; 新しい連想配列

### 書式

```c
mknmap NewMap(int (*keycmp)(const void *, const void *),
				void *(*keycpy)(void *, const void *),
				void *(*valcpy)(void *, const void *),
				void (*keyfree)(void *),
				void (*valfree)(void *));
```

### 説明

新しい連想配列を生成します．
生成した連想配列は `DeleteMap()` で削除する必要があります．
各引数は関数へのポインタです．

<dl>
    <dt><code>int (*keycmp)(const void *, const void *)</code></dt>
    <dd><p>
        連想配列のキーを比較する関数です．<code>bsearch(3)</code> の引数にある比較関数と同様の要件です．
        </p></dd>
    <dt><code>void *(*keycpy)(void *, const void *)</code></dt>
    <dd><p>
        連想配列のキーをコピーする関数です．
        第一引数が <code>NULL</code> の場合は新しい領域を確保し，第二引数の内容を確保された領域にコピーし，その領域へのポインタを返却してください．
        第一引数が <code>NULL</code> 以外の場合は第一引数をそのまま返却してください．
        この関数が <code>NULL</code> を返却すると，mknmap の内部でエラーが発生します．
        </p></dd>
    <dd><p>
        たとえば，以下のコードはキーとして文字列を利用している場合にうまく仕事をします．
        </p>
        <pre><code class="lang-c">void *my_keycpy(void *prev, const void *newkey)
{
	void *tmp;
	if (prev != NULL) return prev;
	tmp = malloc(strlen((const char *)newkey) + 1);
	if (tmp == NULL) return NULL;
	strcpy(tmp, newkey);
	return tmp;
}</code></pre>
    </dd>
    <dt><code>void *(*valcpy)(void *, const void *)</code></dt>
    <dd><p>
        連想配列の値をコピーする関数です．
        <code>keycpy()</code> と同じですが，領域の (再) 確保とコピーを常に行う必要があります．
        これは，連想配列の要素について，キーは不変であるのに対して値は可変であることによります．
        </p></dd>
    <dd><p>
        たとえば，以下のコードは値として文字列を利用している場合にうまく仕事をします．
        </p>
        <pre><code class="lang-c">void *my_valcpy(void *prev, const void *newval)
{
	void *tmp = realloc(prev, (strlen((const char *)newkey) + 1);
	if (tmp == NULL) return NULL;
	strcpy(tmp, newkey);
	return tmp;
}</code></pre>
    </dd>
    <dt><code>void (*keyfree)(void *)</code></dt>
    <dd><p>
        不必要になったキーの領域を解放する関数です．
        領域が <code>malloc(3)</code> によって確保されている場合は <code>free(3)</code> をそのまま指定できます．
        </p></dd>
    <dt><code>void (*valfree)(void *)</code></dt>
    <dd><p>
        <code>keyfree()</code> と同じですが，値を解放します．
        </p></dd>
</dl>


## GetItem &#x2014; 値の取得

### 書式

```c
void *GetItem(const mknmap map, const void *key);
```

### 説明

連想配列 `map` のキー `key` に対応する値へのポインタを返却します．
`map` に `key` に対応する値がない場合は `NULL` を返却します．

返却されるポインタの指す領域を操作する場合は，その操作が `NewMap()` の引数 `valcpy()` の操作と互換性がある必要があります (通常は `PutItem()` を利用してください)．

## PutItem &#x2014; 値の設定

### 書式

```c
int PutItem(mknmap map, const void *key, const void *val);
```

### 説明

連想配列 `map` にキー `key` と値 `val` の対を追加します．
`map` に `key` に対応する値が存在する場合は上書きされます．

通常は零を返します．
非零が返った場合は mknmap の内部で重篤なエラーが発生しています．

## RemoveItem &#x2014; 値の削除

### 書式

```c
int RemoveItem(mknmap map, const void *key);
```

### 説明

連想配列 `map` からキー `key` と値の対を取り除きます．
`map` に `key` に対応する値が存在しない場合はエラーになりません．

通常は零を返します．
非零が返った場合は mknmap の内部で重篤なエラーが発生しています．

## RemoveAll &#x2014; 値の全削除

### 書式

```c
void RemoveAll(mknmap map);
```

### 説明

連想配列 `map` の要素をすべて削除します．

## DeleteMap &#x2014; 連想配列の削除

### 書式

```c
void DeleteMap(mknmap map);
```

### 説明

`NewMap()` で生成された連想配列 `map` を削除します．
`map` の要素はすべて削除されます．

## FirstItem, LastItem &#x2014; 最初・最後の要素

### 書式

```c
mapitem FirstItem(const mknmap map);
mapitem LastItem(const mknmap map);
```

### 説明

連想配列 `map` から最初．最後の要素へのポインタを返却します．

返却されたポインタ `p` のメンバ `p->k` は要素のキー，`p->v` は要素の値へのポインタです．

## IsEmpty &#x2014; 連想配列は空か

### 書式 

```c
int IsEmpty(const mknmap map);
```

### 説明

連想配列 `map` が空の場合，真を返します．
