# Extract PDFmark

If you use Ghostscript for the PDF file size reduction,
Ghostscript does not preserve page mode and named destinations etc.

Extract PDFmark can extract page mode and named destinations
as PDFmark from PDF.
You can get the small PDF that has preserved them by using this tool.

## Required

poppler

## Build

    $ ./autogen.sh
    $ ./configure
    $ make

## Usage

    $ extractpdfmark foo.pdf > foo.pdfmark.ps
    $ gs -q -dBATCH -dNOPAUSE -sDEVICE=pdfwrite \
         -sOutputFile=foo.new.pdf foo.pdf foo.pdfmark.ps

## Licence

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
