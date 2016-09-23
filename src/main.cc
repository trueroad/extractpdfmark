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

#include "output-pdfmark.hh"

int main (int argc, char *argv[])
{
  std::cout << "% " << PACKAGE_NAME << " version "
            << PACKAGE_VERSION << std::endl
            << "% " << PACKAGE_URL << std::endl << std::endl;

  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " [PDF filename]" << std::endl;
      return 1;
    }

  return output_pdfmark (argv[1], std::cout);
}
