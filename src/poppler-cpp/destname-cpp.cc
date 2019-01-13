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

#include <sstream>
#include <string>
#include <poppler-destination.h>

std::string poppler_cpp::walk (const std::string &name,
                               const poppler::destination &dest)
{
  std::stringstream ss;

  switch (dest.type ())
    {
    case poppler::destination::type_enum::xyz:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/XYZ " << dest.left ()
        << " " << dest.top ()
        << " " << dest.zoom ()
        << "] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/Fit] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit_h:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/FitH " << dest.top ()
        << "] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit_v:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/FitV " << dest.left ()
        << "] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit_r:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/FitR " << dest.left ()
        << " " << dest.bottom ()
        << " " << dest.right ()
        << " " << dest.top ()
        << "] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit_b:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/FitB] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit_b_h:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest. page_number ()
        << " /View [/FitBH " << dest.top ()
        << "] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::fit_b_v:
      ss
        << "[ /Dest " << encode_name (name)
        << " /Page " << dest.page_number ()
        << " /View [/FitBV " << dest.left ()
        << "] /DEST pdfmark" << std::endl;
      break;
    case poppler::destination::type_enum::unknown:
      ss << "%  dest type is unknown." << std::endl;
      break;
    default:
      ss << "%  dest type error." << std::endl;
      break;
    }

  return ss.str ();
}

std::string poppler_cpp::destname (void)
{
  auto map {doc->create_destination_map ()};
  std::string retval;

  for (const auto& pair: map)
    retval += walk (pair.first, pair.second);

  return retval;
}
