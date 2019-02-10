// This file is part of Extract PDFmark.
//
// Copyright (C) 2016, 2019 Masamichi Hosoda
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

#include "poppler-core.hh"

#include <iostream>
#include <memory>
#include <PDFDoc.h>
#include <PDFDocFactory.h>

std::unique_ptr<output_pdfmark> create_output_pdfmark (void)
{
  return std::unique_ptr<output_pdfmark> (new poppler_core ());
}

bool poppler_core::open (const std::string &pdf_filename)
{
  std::unique_ptr<GooString> fileName
  {new GooString {pdf_filename.c_str (),
        static_cast<int> (pdf_filename.length ())}};
  doc = std::unique_ptr<PDFDoc>
    {PDFDocFactory ().createPDFDoc (*fileName, NULL, NULL)};

  if (!doc)
    {
      std::cerr << "open failed." << std::endl;
      return false;
    }
  if (!doc->isOk ())
    {
      std::cerr << "file is not OK." << std::endl;
      return false;
    }

  return true;
}

std::string poppler_core::version (void)
{
  std::string retval;

  retval = "Compiled with poppler-core";
#ifndef HAVE_POPPLER_CORE_IF
  retval += " private";
#endif
  retval += ".\n";

  return retval;
}
