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
  std::cerr << "walk" << std::endl;

  // return value is used for GTraverseFunc ()'s return value.
  // false means to continue the travarsal (true means to stop)
  return false;
}

std::string poppler_glib::destname (void)
{
  std::unique_ptr<GTree, decltype (&g_tree_destroy)>
    tree {poppler_document_build_dests_tree (document), g_tree_destroy};

  g_tree_foreach (tree.get (), walk_entry, this);

  return "";
}
