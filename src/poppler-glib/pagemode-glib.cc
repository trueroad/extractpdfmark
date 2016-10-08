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
#include <sstream>
#include <poppler.h>

#include "poppler-glib.hh"

std::string poppler_glib::pagemode (void)
{
  std::stringstream ss;

  if (!document)
    {
      std::cerr << "% document is null" << std::endl;
      return "";
    }

  switch (poppler_document_get_page_mode (document))
    {
    case POPPLER_PAGE_MODE_UNSET:
    case POPPLER_PAGE_MODE_NONE:
      ss << "[ /PageMode /UseNone /DOCVIEW pdfmark" << std::endl;
      break;
    case POPPLER_PAGE_MODE_USE_OUTLINES:
      ss << "[ /PageMode /UseOutlines /DOCVIEW pdfmark" << std::endl;
      break;
    case POPPLER_PAGE_MODE_USE_THUMBS:
      ss << "[ /PageMode /UseThumbs /DOCVIEW pdfmark" << std::endl;
      break;
    case POPPLER_PAGE_MODE_FULL_SCREEN:
      ss << "[ /PageMode /FullScreen /DOCVIEW pdfmark" << std::endl;
      break;
    case POPPLER_PAGE_MODE_USE_OC:
      ss << "% PageMode POPPLER_MODE_USE_OC" << std::endl;
      break;
    case POPPLER_PAGE_MODE_USE_ATTACHMENTS:
      ss << "% PageMode POPPLER_MODE_USE_ATTACHMENTS" << std::endl;
      break;
    default:
      ss << "% PageMode unknown" << std::endl;
      break;
    }

  return ss.str ();
}
