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
#include <memory>

#include "poppler-glib.hh"

std::unique_ptr<output_pdfmark> create_output_pdfmark (void)
{
  return std::unique_ptr<output_pdfmark> (new poppler_glib ());
}

bool poppler_glib::open (const std::string &pdf_filename)
{
  std::cerr << "poppler_glib::open () dummy" << std::endl;
  return false;
}

std::string poppler_glib::pagemode (void)
{
  return "";
}

std::string poppler_glib::destname (void)
{
  return "";
}
