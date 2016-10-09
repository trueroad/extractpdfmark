# Extract PDFmark

If you create a PDF document by something like TeX systems,
many small PDFs as figures get included into the main PDF.
It is common for each small PDF to use the same fonts.

If the small PDFs are embedded subsetted fonts,
the TeX system includes them as-is for the main PDF.
As a result,
the main PDF is embedded different subsets of the same duplicate font.
It is not possible to remove the duplicates since they are different subsets.
It enormously increases the main PDF file size.

On the other hand,
if the small PDFs are embedded full set fonts,
the TeX system also includes all of them for the main PDF.
The main PDF is embedded many duplicate fonts,
but they are all same full set fonts.
Therefore, Ghostscript can remove the duplicates.
It can reduce the main PDF files size.

Moreover,
if the small PDFs are not embedded any fonts,
the TeX system outputs the main PDF which lacks some fonts.
In this case, Ghostscript can embed the necessary fonts.
It can significantly reduce the required disk size.

Either way,
Ghostscript inputs the main PDF which is outputted by the TeX system,
and outputs the final PDF.
Unfortunately, during this process,
Ghostscript does not preserve PDF page-mode and named-destinations etc.
As a result,
when you open the final PDF,
it cannot realize the intended how the document shall be displayed.
Remote PDF links also do not work.

http://bugs.ghostscript.com/show_bug.cgi?id=696943

http://bugs.ghostscript.com/show_bug.cgi?id=695760

Extract PDFmark can extract page mode and named destinations
as PDFmark from PDF.
You can get the small PDF that has preserved them by using this tool.

## Required

poppler 0.13.3+

Autotools (autoheader, aclocal, automake, autoconf)

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

Extract PDFmark is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.
