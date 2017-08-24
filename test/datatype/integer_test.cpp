//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 23, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing integral type implementation
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <h5cpp/datatype/integer.hpp>

namespace type = hdf5::datatype;

using test_types = boost::mpl::list<char,unsigned char,signed char,
                                    short,unsigned short,
                                    int, unsigned int,
                                    long, unsigned long,
                                    long long, unsigned long long>;

BOOST_AUTO_TEST_SUITE(Integer_test)

BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,T,test_types)
{
  type::Integer t = type::Integer::create<T>();
  BOOST_CHECK(t.get_class()==type::Class::INTEGER);
  BOOST_CHECK_EQUAL(t.size(),sizeof(T));

}
BOOST_AUTO_TEST_SUITE_END()