//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Created on: Aug 24, 2017
//
#pragma once

#include <list>
#include <string>
#include "windows.hpp"

namespace hdf5 {

//!
//! \brief path to a node object
//!
//! Every object within an HDF5 file can be addressed via a path. Such a path is a
//! list of link names separated by a slash /.
//! While HDF5s C-API uses a simple string to represent a path, the C++ wrapper
//! provides a class for this purpose.
//!
class DLL_EXPORT Path
{
  public:
    using value_type = std::string;
    using iterator = std::list<value_type>::iterator;
    using const_iterator = std::list<value_type>::const_iterator;
    using reverse_iterator = std::list<value_type>::reverse_iterator;
    using const_reverse_iterator= std::list<value_type>::const_reverse_iterator;

    //!
    //! \brief default constructor
    //!
    //! After default construction is list of path elements is empty and the
    //! absolute path flag is set to false.
    //!
    Path();

    //!
    //! \brief constructor
    //!
    //! Construct a path from a string. We use an explicit constructor here
    //! to avoid accidental conversions.
    //!
    explicit Path(const std::string &str);

    //!
    //! \brief copy constructor
    //!
    Path(const Path &p) = default;

    explicit operator std::string() const
    {
      return to_string();
    }

    //!
    //! \brief return number of path elements
    //!
    size_t size() const;

    //!
    //! \brief const iterator to first path element
    //!
    const_iterator begin() const;

    //!
    //! \brief const iterator to last + 1 element
    //!
    const_iterator end() const;

    //!
    //! \brief iterator to the first element
    //!
    iterator begin();

    //!
    //! \brief iterator to the last+1 element
    //!
    iterator end();

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    void push_front(const value_type &link_name);
    value_type pop_front();

    void push_back(const value_type &link_name);
    value_type pop_back();

    bool is_absolute_path() const noexcept;
    void is_absolute_path(bool value) noexcept;

    value_type back() const;
    value_type front() const;

    //!
    //! \brief true if the path refers to the root group
    //!
    //! A path is considered to reference the root group if the list
    //! of elements is empty but the absolute path flag is set.
    //!
    bool is_root() const;

    //!
    //! \brief get object name from a path
    //!
    //! The object name is the last element of a path. In the case
    //! of the root group it is the same.
    //!
    static std::string object_name(const Path &path);

    //!
    //! \brief get parent path
    //!
    //! This is basically the path with the last component stripped of.
    //!
    static Path parent_path(const Path &path);

  private:
    bool absolute_;
    std::list<std::string> link_names_;

    void from_string(const std::string &str);
    std::string to_string() const;

};

DLL_EXPORT Path operator+(const Path &lhs,const Path &rhs);

DLL_EXPORT Path operator+(const std::string &link_name,const Path &path);
DLL_EXPORT Path operator+(const Path &path,const std::string &link_name);

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Path &path);

} // namespace hdf5
