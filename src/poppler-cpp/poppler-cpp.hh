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

#ifndef INCLUDE_GUARD_POPPLER_CPP_HH
#define INCLUDE_GUARD_POPPLER_CPP_HH

#include <memory>
#include <string>
#include <poppler-destination.h>
#include <poppler-document.h>

#include "output-pdfmark.hh"

class poppler_cpp : public output_pdfmark
{
public:
  bool open (const std::string &pdf_filename);
  std::string pagemode (void);
  std::string destname (void);
  std::string version (void);

private:
  std::string walk (const std::string &name,
                    const poppler::destination &dest);

  std::unique_ptr<poppler::document> doc;
};

#endif // INCLUDE_GUARD_POPPLER_CPP_HH
