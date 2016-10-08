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

#include <sstream>
#include <iomanip>

#include "output-pdfmark.hh"
#include "utf16.hh"
#include "utf8.hh"

std::string output_pdfmark::encode (const std::string &name)
{
  bool bflag = escape || is_utf16 (name) || !is_utf8 (name);
  std::stringstream encoded;

  for (auto c: name)
    {
      if (bflag || static_cast<unsigned char>(c) < 0x20 ||
          c == '(' || c == ')' || c == '\\' || c == 0x7f)
        {
          encoded
            << '\\'
            << std::oct << std::setw (3) << std::setfill ('0')
            << static_cast<int>(static_cast<unsigned char>(c));
        }
      else
        {
          encoded << c;
        }
    }
  return encoded.str ();
}

std::string output_pdfmark::encode_name (const std::string &name)
{
  return "(" + encode (name) + ")";
}
