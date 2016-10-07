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

#ifndef INCLUDE_GUARD_POPPLER_CORE_HH
#define INCLUDE_GUARD_POPPLER_CORE_HH

#include <string>
#include <memory>

#include "../output-pdfmark.hh"

class poppler_core : public output_pdfmark
{
public:
  bool open (const std::string &pdf_filename);
  std::string pagemode (void);
  std::string destname (void);

  poppler_core () :
    doc {nullptr}
  {
  }

private:
  std::string build_destname (GooString *name);
  std::unique_ptr<PDFDoc> doc;
};

#endif // INCLUDE_GUARD_POPPLER_CORE_HH
