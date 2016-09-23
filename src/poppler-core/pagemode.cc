// This file is part of Extract PDFmark.
//
// Copyright (C) 2016 Masamichi Hosoda
//
// Extract PDFmark is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Extract PDFmark is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include <iostream>
#include <PDFDoc.h>

#include "pagemode.hh"

void put_pagemode (PDFDoc *doc, std::ostream &output)
{
  Catalog *catalog = doc->getCatalog ();
  if (catalog && catalog->isOk ())
    {
      switch (catalog->getPageMode ())
        {
        case Catalog::pageModeNone:
          output
            << "[ /PageMode /UseNone /DOCVIEW pdfmark" << std::endl;
          break;
        case Catalog::pageModeOutlines:
          output
            << "[ /PageMode /UseOutlines /DOCVIEW pdfmark" << std::endl;
          break;
        case Catalog::pageModeThumbs:
          output
            << "[ /PageMode /UseThumbs /DOCVIEW pdfmark" << std::endl;
          break;
        case Catalog::pageModeFullScreen:
          output
            << "[ /PageMode /FullScreen /DOCVIEW pdfmark" << std::endl;
          break;
        default:
          output << "% PageMode unknown" << std::endl;
          break;
        }
    }
  else
    output << "% PageMode unset" << std::endl;
}
