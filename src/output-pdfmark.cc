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

#include <iostream>
#include <string>

#include "cmdlineparse.hh"
#include "output-pdfmark.hh"

void output_pdfmark::add_options (cmdlineparse::parser *cmd)
{
  cmd->add_string (0, "style", &style, "literal",
                   "    Name style\n"
                   "      literal: literal strings\n"
                   "      hex:     hexadecimal strings\n"
                   "      name:    name object",
                   "STYLE");
  cmd->add_flag (0, "escape", &escape,
                 "    Escape all characters");
}

void output_pdfmark::parse_options (void)
{
  if (style == "literal")
    {
      hexadecimal = false;
      nameobject = false;
    }
  else if (style == "hex")
    {
      hexadecimal = true;
      nameobject = false;
    }
  else if (style == "name")
    {
      hexadecimal = false;
      nameobject = true;
    }
  else
    std::cerr << "unknown --style argument: " << style << std::endl;
}
