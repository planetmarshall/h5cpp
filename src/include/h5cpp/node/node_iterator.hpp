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
// Created on: Sep 13, 2017
//
#pragma once

#include <functional>
#include "../iterator.hpp"
#include "node_view.hpp"
#include "node.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace node {

class DLL_EXPORT NodeIterator : public Iterator
{
  public:
    using value_type = Node;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::random_access_iterator_tag;

    NodeIterator() = delete;
    NodeIterator(const NodeIterator&) = default;
    NodeIterator(const NodeView &view,ssize_t index);

    explicit operator bool() const
    {
      return !(index()<0 || index()>=view_.get().size());
    }

    Node operator*() const;

    Node *operator->();

    NodeIterator &operator++();
    NodeIterator operator++(int);
    NodeIterator &operator--();
    NodeIterator operator--(int);

    NodeIterator &operator+=(ssize_t i);
    NodeIterator &operator-=(ssize_t i);

    bool operator==(const NodeIterator &a) const;

    bool operator!=(const NodeIterator &a) const;

  private:
    std::reference_wrapper<const NodeView> view_;
    Node current_node_;

};

} // namespace node
} // namespace hdf5
