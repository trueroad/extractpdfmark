<!-- -*- coding: utf-8 -*- -->
# Extract PDFmark

PDF からページモードやリンクの宛先名を抽出し PDFmark として保存します

https://github.com/trueroad/extractpdfmark  
http://www.ctan.org/pkg/extractpdfmark

TeX のようなシステムを使って PDF のドキュメントを作る場合、
図としてたくさんの小さな PDF を用意して、
メインの PDF に貼り付けるようなことが行われます。
このとき、図の PDF では同じフォントを使っていることが多いと思います。

図の PDF にフォントのサブセットが埋め込まれていた場合、
TeX システムはそのフォントをそのままメインの PDF に埋め込みます。
結果として、
メイン PDF には重複した同じフォントの異なるサブセットが埋め込まれます。
サブセットが異なるため重複したフォントを削除することはできません。
よってメイン PDF のファイルサイズは、かなり大きくなってしまいます。

一方、図の PDF にフォントをフルセットで埋め込んだ場合、
TeX システムはフルセットのフォントをメインの PDF へ埋め込みます。
メイン PDF にはたくさんの重複したフォントが埋め込まれますが、
すべて同じフルセットのフォントです。
そのため、Ghostscript を使えば重複を削除することができ、
これによってメイン PDF のサイズを低減することができます。
（注意： Ghostscript 9.17 から 9.21 は重複フォント削除のために
`-dPDFDontUseFontObjectNum` コマンドラインオプションが必要です。
Ghostscript 9.22 以降は重複フォント削除ができなくなくなったため、
フルセット埋め込みの方法を採ることができません。
詳細は https://ghostscript.com/pipermail/gs-devel/2017-September/date.html
や http://lists.gnu.org/archive/html/lilypond-devel/2017-09/index.html
をご覧ください。
この場合は、次に示すフォントを一切埋め込まない方法を採る必要があります。）

さらに、図の PDF に一切フォントを埋め込まなかった場合、
TeX システムはフォントが欠けたメイン PDF を出力します。
この場合、Ghostscript は必要なフォントを埋め込むことができるので、
必要なディスク容量を劇的に減らすことができるようになります。
（注意： Ghostscript 9.26 以降で CID フォントを埋め込みたい場合は、
https://bugs.ghostscript.com/show_bug.cgi?id=700367
と https://bugs.ghostscript.com/show_bug.cgi?id=700436
をご覧ください。）

いずれの方法でも、
Ghostscript へ TeX システムの出力したメイン PDF を入力し、
最終的な PDF を出力することになります。
しかし、残念ながら、この処理で Ghostscript は PDF のページモードや
リンクの宛先名を残してくれません。
そのため、最終的な PDF は意図したとおりに開かれなかったり、
リモートからのリンクが機能しなくなったりしてしまいます。

http://bugs.ghostscript.com/show_bug.cgi?id=696943  
http://bugs.ghostscript.com/show_bug.cgi?id=695760

Extract PDFmark は PDF からページモードやリンクの宛先名を抽出し、
PDFmark として保存することができます。
このツールを使うと、ページモードやリンク先名を残したまま、
サイズの小さい PDF を得ることができます。

## 使い方

    $ extractpdfmark TeX出力.pdf > 抽出したPDFmark.ps
    $ gs -q -dBATCH -dNOPAUSE -sDEVICE=pdfwrite \
         -dPDFDontUseFontObjectNum -dPrinted=false \
         -sOutputFile=最終.pdf TeX出力.pdf 抽出したPDFmark.ps

（注意： Ghostscript 9.26 以降は `-dPrinted=false`
コマンドラインオプションが必要です。詳細は
https://bugs.ghostscript.com/show_bug.cgi?id=699830
をご覧ください。）

## バイナリパッケージからのインストール

いくつかのディストリビューションには `extractpdfmark` パッケージがあります。

* Debian:
[9 stretch](https://packages.debian.org/stretch/extractpdfmark).
* Ubuntu:
17.04 Zesty Zapus,
17.10 Artful Aardvark,
[18.04 LTS Bionic Beaver](https://packages.ubuntu.com/bionic/extractpdfmark),
[18.10 Cosmic Cuttlefish](https://packages.ubuntu.com/cosmic/extractpdfmark).
* Fedora:
[29](https://apps.fedoraproject.org/packages/extractpdfmark).
* Cygwin:
[2017-05](https://sourceware.org/ml/cygwin-announce/2017-05/msg00030.html).

## [ソース tarball](https://github.com/trueroad/extractpdfmark/releases/download/v1.0.3/extractpdfmark-1.0.3.tar.gz) からのインストール

### 必要なもの

[poppler](https://poppler.freedesktop.org/) 0.13.3 以降
に以下のオプションをつけてビルドしたもの。
（推奨 poppler 0.48.0 以降）

* --enable-xpdf-headers (poppler 0.59.0 まで)
* -DENABLE_XPDF_HEADERS=ON （poppler 0.60.0 から 0.72.0）
* -DENABLE_UNSTABLE_API_ABI_HEADERS=ON (poppler 0.73.0 以降)

パッケージを使って準備したい場合には、以下が便利でしょう。

* Debian / Ubuntu
  + libpoppler-private-dev
  + libpoppler-dev
* Fedora
  + poppler-devel
* Cygwin
  + libpoppler-devel

### ビルド・インストール方法

    $ ./configure
    $ make
    $ make install

`Ghostscript` 9.14 以降と `diff` 等があれば、
以下のようにインストール前にテストすることができます。

    $ ./configure
    $ make
    $ make check
    $ make install

## [Git リポジトリ](https://github.com/trueroad/extractpdfmark)からのインストール

ソース tarball のビルド要件と追加の要件が必要です。

### 追加で必要なもの

Autoconf 2.69 以降  
Automake  
autopoint 0.19.6 以降（gettext 0.19.6 以降）

### 追加で推奨するもの

pdfTeX （テスト PDF の生成用）  
Ghostscript 9.14 以降（`make check` 用）

### ビルド・インストール方法

    $ git clone https://github.com/trueroad/extractpdfmark.git
    $ cd extractpdfmark
    $ ./autogen.sh
    $ mkdir build
    $ cd build
    $ ../configure
    $ make
    $ make check
    $ make install

## News

[News](./NEWS)

## ライセンス

Copyright (C) 2016-2019 Masamichi Hosoda

Extract PDFmark is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Extract PDFmark is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.
