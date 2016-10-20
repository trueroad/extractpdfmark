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

#include "utf8.hh"

#ifdef USE_CODECVT
#include <cwchar>
#include <codecvt>
#endif

#include <string>

#ifdef USE_ICONV
#include "iconv_wrapper.hh"
#endif

#ifdef USE_CODECVT

bool is_utf8 (const std::string &str)
{
  std::codecvt_utf8<char32_t> cvt;
  auto mb {std::mbstate_t ()};
  return (cvt.length (mb, &str.front (), &str.front () + str.length (),
                      std::string::npos)
          == str.length ());
}

#else  // USE_CODECVT

#ifdef USE_ICONV

bool is_utf8 (const std::string &str)
{
  try
    {
      iconv_wrapper::iconv cvt8to16 {"UTF-8", "UTF-16"};
      std::string utf16 {cvt8to16.convert (str)};
      iconv_wrapper::iconv cvt16to8 {"UTF-16", "UTF-8"};
      std::string utf8 {cvt16to8.convert (utf16)};
      return (str == utf8);
    }
  catch (std::system_error &error)
    {
      return false;
    }
  return false;
}

#else  // USE_ICONV

bool is_utf8 (const std::string &str)
{
  return false;
}

#endif  // USE_ICONV
#endif  // USE_CODECVT
