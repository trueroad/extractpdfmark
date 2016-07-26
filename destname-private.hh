// This file is part of Extract PDFmark.
//
// Copyright (C) 2016 Masamichi Hosoda
//
// Extract PDFmark is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Foobar is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.

#include <Catalog.h>

//
// *** FIX ME, UGLY ***
//
// poppler does not have destination name enumeration.
// So forced to use a private member function.
//
// http://bloglitb.blogspot.jp/2010/07/access-to-private-members-thats-easy.html
// https://gist.github.com/dabrahams/1528856
//

template <class Tag>
struct Accessor
{
  static typename Tag::type value;
};

template <class Tag>
typename Tag::type Accessor<Tag>::value;

template <class Tag, typename Tag::type p>
struct Initializer
{
  Initializer()
  {
    Accessor<Tag>::value = p;
  }
  static Initializer instance;
};

template <class Tag, typename Tag::type p>
Initializer<Tag, p> Initializer<Tag, p>::instance;

struct Catalog_getDestNameTree { typedef NameTree* (Catalog::* type)(); };

template struct Initializer<Catalog_getDestNameTree,
                            &Catalog::getDestNameTree>;

inline NameTree *get_destnametree (Catalog *catalog)
{
  return (catalog->*Accessor<Catalog_getDestNameTree>::value)();
}

//
// *** FIXME, UGLY ***
//
