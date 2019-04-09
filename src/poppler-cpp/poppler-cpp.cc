// This file is part of Extract PDFmark.
//
// Copyright (C) 2019 Masamichi Hosoda
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

#include "poppler-cpp.hh"

#include <iostream>
#include <memory>
#include <string>
#include <poppler-document.h>
#include <poppler-version.h>

std::unique_ptr<output_pdfmark> create_output_pdfmark (void)
{
  return std::unique_ptr<output_pdfmark> (new poppler_cpp ());
}

bool poppler_cpp::open (const std::string &pdf_filename)
{
  doc = std::unique_ptr<poppler::document>
    {poppler::document::load_from_file (pdf_filename)};

  if (!doc)
    {
      std::cerr << "poppler::document::load_from_file failed: "
                << pdf_filename;
      return false;
    }
  return true;
}

std::string poppler_cpp::version (void)
{
  std::string retval;

  retval = "Compiled with poppler-cpp ";
  retval += POPPLER_VERSION;
  retval += ".\nRunning with poppler-cpp ";
  retval += poppler::version_string ();
  retval += ".\n";

  return retval;
}
