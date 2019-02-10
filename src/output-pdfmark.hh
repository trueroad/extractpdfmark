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

#ifndef INCLUDE_GUARD_OUTPUT_PDFMARK_HH
#define INCLUDE_GUARD_OUTPUT_PDFMARK_HH

#include <memory>
#include <string>

namespace cmdlineparse
{
  class parser;
}

class output_pdfmark
{
public:
  virtual bool open (const std::string &pdf_filename) = 0;
  virtual std::string pagemode (void) = 0;
  virtual std::string destname (void) = 0;
  virtual std::string version (void) = 0;

  void add_options (cmdlineparse::parser *cmd);
  void parse_options (void);

  std::string encode_literal (const std::string &name) const;
  std::string encode_hexadecimal (const std::string &name) const;
  std::string encode_nameobject (const std::string &name) const;
  std::string encode_name (const std::string &name) const;

  output_pdfmark () = default;
  virtual ~output_pdfmark () = default;

private:
  output_pdfmark (output_pdfmark const&) = delete;
  output_pdfmark (output_pdfmark&&) = delete;
  output_pdfmark& operator = (output_pdfmark const&) = delete;
  output_pdfmark& operator = (output_pdfmark&&) = delete;

  std::string style;
  bool escape = false;
  bool hexadecimal = false;
  bool nameobject = false;
};

std::unique_ptr<output_pdfmark> create_output_pdfmark (void);

#endif // INCLUDE_GUARD_OUTPUT_PDFMARK_HH
