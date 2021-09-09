# compprog-cffi-pypy-set
PyPyで高速なset,multiset, mapを使うためのライブラリです。競技プログラミング用）

## Requirement

### 環境
- Ubuntu 18.04

### 必須

- Python3

### なくてもよいがあるとうれしい
- Python3 pyperclip (自動でクリップボードにコードがコピペされて提出しやすい)
- gcc (手元で編集してコンパイルするのに必要)
- PyPy3 (7.3.0) (手元でテスト可能)
  - CFFI (手元で編集してコンパイルするのに必要)

## 使い方

### 準備

```
$ git clone https://github.com/likein12/compprog-cffi-pypy-set.git
$ cd compprog-cffi-pypy-set
```

### 提出ファイルを作る

```./draft/draft.py```を開いて編集。

```
$ ./sh/build_src_python.sh
```
上記を実行。

### 自分でコンパイルする方法

PyPy (7.3.0) + CFFIが必須

```
$ ./sh/temp_compile.sh
```

### 検証

工事中

