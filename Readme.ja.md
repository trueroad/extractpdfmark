<!-- -*- coding: utf-8 -*- -->
# Extract PDFmark

Ghostscript を PDF ファイルサイズ低減のために使うとすると、
ページモードやリンク先名等が保存されません。

Extract PDFmark は PDF からページモードやリンク先名を抽出し、
PDFmark として保存することができます。
このツールを使うと、ページモードやリンク先名を残したまま、
サイズの小さい PDF を得ることができます。

## 必要なもの

poppler

## ビルド方法

    $ ./autogen.sh
    $ ./configure
    $ make

## 使い方

    $ extractpdfmark foo.pdf > foo.pdfmark.ps
    $ gs -q -dBATCH -dNOPAUSE -sDEVICE=pdfwrite \
         -sOutputFile=foo.new.pdf foo.pdf foo.pdfmark.ps

## ライセンス

Copyright (C) 2016 Masamichi Hosoda

Extract PDFmark is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.
