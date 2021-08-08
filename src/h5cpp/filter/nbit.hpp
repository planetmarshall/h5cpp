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
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 20, 2020
//
#pragma once

#include <h5cpp/filter/filter.hpp>

namespace hdf5 {
namespace filter {

//!
//! \brief NBit checksum filter
//!
//! If applied to a dataset creation property list this filter will setup
//! the nbit checksum filter.
//!
class DLL_EXPORT NBit : public Filter
{
  public:
    //!
    //! \brief default constructor
    //!
    NBit();

    ~NBit();

    //!
    //! \brief apply filter
    //!
    //! Applies the filter to a dataset creation property list.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param dcpl reference to the dataset creation property list
    //!
    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag = Availability::MANDATORY) const override;
};

} // namespace filter
} // namespace hdf5
