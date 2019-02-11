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

#include "config.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "cmdlineparse.hh"
#include "output-pdfmark.hh"

int main (int argc, char *argv[])
{
  cmdlineparse::parser cmd;
  std::unique_ptr<output_pdfmark> opdfmark {create_output_pdfmark ()};
  std::string output_filename;

  cmd.add_default_help ();
  cmd.add_handler ('V', "version",
                   cmdlineparse::arg_mode::no_argument,
                   [&cmd, &opdfmark](const std::string &)->bool
                   {
                     std::cout << cmd.get_version_string ()
                               << std::endl
                               << opdfmark->version ();
                     return false;
                   },
                   "    Print version and exit");
  cmd.add_string ('o', "output", &output_filename, "",
                  "    Output filename\n"
                  "    (Default: standard output)",
                  "OUTPUT.ps");
  opdfmark->add_options (&cmd);

  cmd.set_usage_unamed_opts ("INPUT.pdf");

  if (!cmd.parse (argc, argv))
    return 0;

  if (cmd.get_unamed_args ().empty ())
    {
      std::cerr << cmd.get_version_string () << std::endl
                << cmd.build_usage () << std::endl;
      return 1;
    }

  std::ostream *pout;
  std::ofstream ofs;
  if (output_filename.empty () || output_filename == "-")
    {
      pout = &std::cout;
    }
  else
    {
      ofs.open (output_filename);
      pout = &ofs;
    }

  *pout << "% " << PACKAGE_STRING << std::endl
        << "% " << PACKAGE_URL << std::endl << std::endl;

  if (!opdfmark->open (cmd.get_unamed_args ().at (0)))
    return 1;

  opdfmark->parse_options ();

  *pout << opdfmark->pagemode ();
  *pout << opdfmark->destname ();
  return 0;
}
