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

#include "config.h"

#include "poppler-cpp.hh"

#include <iostream>
#include <sstream>
#include <string>
#include <poppler-document.h>

std::string poppler_cpp::pagemode (void)
{
  std::stringstream ss;

  if (!doc)
    {
      std::cerr << "% document is null" << std::endl;
      return "";
    }

  switch (doc->page_mode ())
    {
    case poppler::document::page_mode_enum::use_none:
      ss << "[ /PageMode /UseNone /DOCVIEW pdfmark" << std::endl;
      break;
    case poppler::document::page_mode_enum::use_outlines:
      ss << "[ /PageMode /UseOutlines /DOCVIEW pdfmark" << std::endl;
      break;
    case poppler::document::page_mode_enum::use_thumbs:
      ss << "[ /PageMode /UseThumbs /DOCVIEW pdfmark" << std::endl;
      break;
    case poppler::document::page_mode_enum::fullscreen:
      ss << "[ /PageMode /FullScreen /DOCVIEW pdfmark" << std::endl;
      break;
    case poppler::document::page_mode_enum::use_oc:
      ss << "% PageMode use_oc" << std::endl;
      break;
    case poppler::document::page_mode_enum::use_attach:
      ss << "% PageMode use_attach" << std::endl;
      break;
    default:
      ss << "% PageMode unknown" << std::endl;
      break;
    }

  return ss.str ();
}
