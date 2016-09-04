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
#include <PDFDocFactory.h>

#include "../output-pdfmark.hh"
#include "pagemode.hh"
#include "destname.hh"

int output_pdfmark (char *pdf_filename)
{
  GooString *fileName = new GooString (pdf_filename);
  PDFDoc *doc = PDFDocFactory().createPDFDoc(*fileName, NULL, NULL);
  delete fileName;

  if (!doc)
    {
      std::cerr << "open failed." << std::endl;
      return 1;
    }
  if (!doc->isOk ())
    {
      std::cerr << "file is not OK." << std::endl;
      delete doc;
      return 1;
    }

  put_pagemode (doc);
  put_destnametree (doc);

  delete doc;
  return 0;
}
