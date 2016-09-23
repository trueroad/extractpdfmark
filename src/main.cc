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

#include "cmdlineparse.hh"
#include "output-pdfmark.hh"

int main (int argc, char *argv[])
{
  cmdlineparse::parser cmd;

  cmd.add_default ();
  cmd.set_usage_unamed_opts ("PDF filename");

  if (!cmd.parse (argc, argv))
    return 0;

  if (cmd.get_unamed_args ().empty ())
    {
      std::cerr << cmd.get_version_string () << std::endl
                << cmd.build_usage () << std::endl;
      return 1;
    }

  std::cout << "% " << PACKAGE_STRING << std::endl
            << "% " << PACKAGE_URL << std::endl << std::endl;

  return output_pdfmark (cmd.get_unamed_args ().at (0), std::cout);
}
