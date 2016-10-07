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

#ifndef INCLUDE_GUARD_OUTPUT_PDFMARK_HH
#define INCLUDE_GUARD_OUTPUT_PDFMARK_HH

#include <string>
#include <memory>

class output_pdfmark
{
public:
  virtual bool open (const std::string &pdf_filename) = 0;
  virtual std::string pagemode (void) = 0;
  virtual std::string destname (void) = 0;

  virtual ~output_pdfmark () = default;
};

std::unique_ptr<output_pdfmark> create_output_pdfmark (void);

#endif // INCLUDE_GUARD_OUTPUT_PDFMARK_HH
