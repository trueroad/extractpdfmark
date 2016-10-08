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

#include "poppler-glib.hh"

#include <iostream>
#include <memory>
#include <string>
#include <poppler.h>

std::unique_ptr<output_pdfmark> create_output_pdfmark (void)
{
  return std::unique_ptr<output_pdfmark> (new poppler_glib ());
}

namespace
{
  std::string get_uri (const std::string &filename)
  {
    std::string abs_filename;

    if (g_path_is_absolute (filename.c_str ()))
      abs_filename = filename;
    else
      {
        std::unique_ptr<gchar, decltype (&g_free)> dir
        {g_get_current_dir (), g_free};
        std::unique_ptr<gchar, decltype (&g_free)> abs
        {g_build_filename (dir.get (), filename.c_str (), nullptr), g_free};
        abs_filename = abs.get ();
      }

    GError *error {nullptr};
    std::unique_ptr<gchar, decltype (&g_free)> uri
    {g_filename_to_uri (abs_filename.c_str (), nullptr, &error), g_free};
    if (!uri)
      {
        std::cerr << "g_filename_to_uri failed: " << abs_filename;
        if (error)
          {
            std::cerr << ": " << error->message << std::endl;
            g_error_free (error);
          }
        else
          {
            std::cerr << std::endl;
          }
        return "";
      }
    return uri.get ();
  }
}

bool poppler_glib::open (const std::string &pdf_filename)
{
  GError *error {nullptr};
  document = poppler_document_new_from_file (get_uri (pdf_filename).c_str (),
                                             nullptr, &error);
  if (!document)
    {
      std::cerr << "poppler_document_new_from_file failed: " << pdf_filename;
      if (error)
        {
          std::cerr << ": " << error->message << std::endl;
          g_error_free (error);
        }
      else
        {
          std::cerr << std::endl;
        }
      return false;
    }
  return true;
}
