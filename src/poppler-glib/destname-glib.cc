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
#include <string>
#include <sstream>
#include <utility>
#include <poppler.h>

#include "poppler-glib.hh"

gboolean poppler_glib::walk_entry (gpointer key,
                                   gpointer value,
                                   gpointer user_data)
{
  GBytes *name = static_cast<GBytes*> (key);
  PopplerDest *dest = static_cast<PopplerDest*> (value);
  poppler_glib *pg = static_cast<poppler_glib*> (user_data);

  return pg->walk (name, dest);
}

bool poppler_glib::walk (GBytes *name, PopplerDest *dest)
{
  std::string n (static_cast<const char*> (g_bytes_get_data (name, nullptr)),
                 static_cast<std::string::size_type> (g_bytes_get_size (name)));
  std::stringstream ss;
  if (dest)
    {
      switch (dest->type)
        {
        case POPPLER_DEST_XYZ:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/XYZ " << dest->left
            << " " << dest->top
            << " " << dest->zoom
            << "] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FIT:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/Fit] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FITH:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/FitH " << dest->top
            << "] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FITV:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/FitV " << dest->left
            << "] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FITR:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/FitR " << dest->left
            << " " << dest->bottom
            << " " << dest->right
            << " " << dest->top
            << "] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FITB:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/FitB] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FITBH:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/FitBH " << dest->top
            << "] /DEST pdfmark" << std::endl;
          break;
        case POPPLER_DEST_FITBV:
          ss
            << "[ /Dest " << encode_name (n)
            << " /Page " << dest->page_num
            << " /View [/FitBV " << dest->left
            << "] /DEST pdfmark" << std::endl;
          break;
        default:
          ss << "%  dest type is unknown." << std::endl;
        }
    }
  else
    {
      ss << "%  dest is null." << std::endl;
    }

  dests += ss.str ();

  // return value is used for GTraverseFunc ()'s return value.
  // false means to continue the travarsal (true means to stop)
  return false;
}

std::string poppler_glib::destname (void)
{
  std::unique_ptr<GTree, decltype (&g_tree_destroy)>
    tree {poppler_document_build_dests_tree (document), g_tree_destroy};
  dests.clear ();

  g_tree_foreach (tree.get (), walk_entry, this);

  std::string tmp {std::move(dests)};
  dests.clear ();
  return tmp;
}
