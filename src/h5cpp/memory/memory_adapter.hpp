//
// (c) Copyright 2019 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 1, 2019
//
#pragma once

#include <type_traits>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/datatype/trait.hpp>

namespace hdf5 {
namespace memory {


template<bool is_const_type>
struct VoidType {
    using type = void;
};

template<> struct VoidType<true>
{
    using type = const void;
};


//! \brief the basic memory adapter template
//!
//! Memory adapters are the corner stones of h5cpp's IO system. They provide
//! access to the memory occupied by an instance of a particular datatype.
//! Unlike the trait classes which have been there since the beginning
//! these templates allow to store state and thus could be used to provide
//! intermediate buffers required by some in-memory structures not compatible
//! with HDF5.
//!
//! \tparam T the type parameters
//!
template<typename T>
class MemoryAdapter
{
  private:
    T &_reference;
  public:
    using BaseType = T;
    using DataspaceType = typename dataspace::TypeTrait<BaseType>::DataspaceType;
    using DatatypeType = typename datatype::TypeTrait<BaseType>::TypeClass;

    explicit MemoryAdapter(T &instance):
      _reference(instance)
    {}

    MemoryAdapter(const MemoryAdapter<T> &) = delete;
    MemoryAdapter(MemoryAdapter<T> &&) = default;

    void* pointer()
    {
      return reinterpret_cast<void*>(&_reference);
    }

    const void* pointer() const
    {
      return reinterpret_cast<const void*>(&_reference);
    }


    DataspaceType dataspace() const
    {
      return dataspace::TypeTrait<BaseType>::create(_reference);
    }

    DatatypeType datatype() const
    {
      return datatype::TypeTrait<BaseType>::create(_reference);
    }


    static BaseType create(const datatype::Datatype& = datatype::Datatype(),
                    const dataspace::Dataspace & = dataspace::Dataspace())
    {
      return BaseType();
    }

    /**
     * @brief update the target data structure
     *
     * After every write operation on the buffer provided by the adapter,
     * which means after every read operation from the view point of HDF5,
     * the update method ensures that all data is copied to the original
     * data structure.
     */
    void update() {}

};

/**
 * @brief construct a memory adapter from a given instance of arbitrary type
 *
 * @param instance reference to the instance for which to construct the adapter
 * @return new instance of a memory adapter
 */
template<typename T>
MemoryAdapter<typename std::remove_const<T>::type> make_adapter(T &instance)
{
  using AdapterType = typename std::remove_const<T>::type;
  return MemoryAdapter<AdapterType>(const_cast<AdapterType&>(instance));
}





} // end of namespace memory
} // end of namespace hdf5