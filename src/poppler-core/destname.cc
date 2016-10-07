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
#include <map>
#include <PDFDoc.h>
#include <Link.h>

#include "poppler-core.hh"

#ifndef HAVE_POPPLER_CORE_IF
#include "destname-private.hh"
#endif

inline std::string goo_to_string (GooString *goo)
{
  return std::string {goo->getCString (),
      static_cast<std::string::size_type>(goo->getLength ())};
}

inline void poppler_core::add_destname (GooString *name,
                                        LinkDest *link_dest)
{
  std::string str = goo_to_string (name);
  add_destname (str, link_dest);
}

inline void poppler_core::add_destname (GooString *name)
{
  std::string str = goo_to_string (name);
  auto link_dest = std::unique_ptr<LinkDest> (doc->findDest (name));
  add_destname (str, link_dest.get ());
}

inline void poppler_core::add_destname (const char *name)
{
  GooString goo {name};
  auto link_dest = std::unique_ptr<LinkDest> (doc->findDest (&goo));
  add_destname (name, link_dest.get ());
}

inline void poppler_core::add_destname (const std::string &name,
                                        LinkDest *link_dest)
{
  if (link_dest)
    {
      name_map.insert (std::make_pair (name, *link_dest));
    }
}

std::string poppler_core::build_destname (const std::string &name,
                                          LinkDest *link_dest)
{
  std::stringstream ss;

  if (link_dest)
    {
      int pagenum;
      if (link_dest->isPageRef ())
        {
          Ref page_ref = link_dest->getPageRef ();
          pagenum = doc->findPage (page_ref.num, page_ref.gen);
        }
      else
        {
          pagenum = link_dest->getPageNum ();
        }

      switch (link_dest->getKind ())
        {
        case destXYZ:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/XYZ " << link_dest->getLeft ()
            << " " << link_dest->getTop ()
            << " " << link_dest->getZoom ()
            << "] /DEST pdfmark" << std::endl;
          break;
        case destFit:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/Fit] /DEST pdfmark" << std::endl;
          break;
        case destFitH:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/FitH " << link_dest->getTop ()
            << "] /DEST pdfmark" << std::endl;
          break;
        case destFitV:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/FitV " << link_dest->getLeft ()
            << "] /DEST pdfmark" << std::endl;
          break;
        case destFitR:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/FitR " << link_dest->getLeft ()
            << " " << link_dest->getBottom ()
            << " " << link_dest->getRight ()
            << " " << link_dest->getTop ()
            << "] /DEST pdfmark" << std::endl;
          break;
        case destFitB:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/FitB] /DEST pdfmark" << std::endl;
          break;
        case destFitBH:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/FitBH " << link_dest->getTop ()
            << "] /DEST pdfmark" << std::endl;
          break;
        case destFitBV:
          ss
            << "[ /Dest (" << encode_name (name)
            << ") /Page " << pagenum
            << " /View [/FitBV " << link_dest->getLeft ()
            << "] /DEST pdfmark" << std::endl;
          break;
        default:
          ss << "%  link_dest kind is unknown." << std::endl;
          break;
        }
    }
  else
    {
      ss << "%  link_dest is null." << std::endl;
    }

  return ss.str ();
}

std::string poppler_core::build_destnames (void)
{
  std::string str;

  for (auto &elm: name_map)
    {
      str += build_destname (elm.first, &elm.second);
    }

  return str;
}

#ifdef HAVE_POPPLER_CORE_IF

// Use poppler-core interface
std::string poppler_core::destname (void)
{
  Catalog *catalog = doc->getCatalog ();
  name_map.clear ();

  if (catalog && catalog->isOk ())
    {
      int len = catalog->numDestNameTree ();
      for (int i=0; i<len; ++i)
        {
          add_destname (catalog->getDestNameTreeName (i),
                        catalog->getDestNameTreeDest (i));
        }

      len = catalog->numDests ();
      for (int i=0; i<len; ++i)
        {
          add_destname (catalog->getDestsName (i),
                        catalog->getDestsDest (i));
        }
    }
  else
    std::cerr << "Catalog is not OK" << std::endl;

  return build_destnames ();
}

#else  // HAVE_POPPLER_CORE_IF

// Use poppler-core private access
std::string poppler_core::destname (void)
{
  Catalog *catalog = doc->getCatalog ();
  name_map.clear ();

  if (catalog && catalog->isOk ())
    {
      NameTree *destnametree = get_destnametree (catalog);
      if (destnametree)
        {
          int len = destnametree->numEntries ();
          for (int i=0; i<len; ++i)
            {
              add_destname (destnametree->getName (i));
            }
        }

      Object *obj = catalog->getDests ();
      if (obj && obj->isDict ())
        {
          int len = obj->dictGetLength ();
          for (int i=0; i<len; ++i)
            {
              add_destname (obj->dictGetKey (i));
            }
        }
    }
  else
    std::cerr << "Catalog is not OK" << std::endl;

  return build_destnames ();
}

#endif  // HAVE_POPPLER_CORE_IF
