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

#ifndef INCLUDE_GUARD_POPPLER_CORE_HH
#define INCLUDE_GUARD_POPPLER_CORE_HH

#include <map>
#include <memory>
#include <string>
#include <Link.h>

#include "output-pdfmark.hh"

class PDFDoc;

class poppler_core : public output_pdfmark
{
public:
  bool open (const std::string &pdf_filename);
  std::string pagemode (void);
  std::string destname (void);
  std::string version (void);

private:
  std::string build_destname (const std::string &name, LinkDest *link_dest);
  std::string build_destnames (void);
  void add_destname (const std::string &name, LinkDest *link_dest);
  void add_destname (GooString *name, LinkDest *link_dest);
  void add_destname (GooString *name);
  void add_destname (const char *name);

  std::unique_ptr<PDFDoc> doc;
  std::map<std::string, LinkDest> name_map;
};

#endif // INCLUDE_GUARD_POPPLER_CORE_HH
