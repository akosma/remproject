/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the implementation of the storage::FindConditions class.
/*!
 * \file ActiveRecord.h
 *
 * Contains the implementation of the storage::FindConditions class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/06/08
 */

#include "FindConditions.h"

#include <sstream>
#include <string>

using std::stringstream;
using std::string;
using storage::AnyPropertyMap;

namespace storage
{
    FindConditions::FindConditions()
    : AnyPropertyMap()
    {
    }
    
    FindConditions::~FindConditions()
    {
    }

    const string FindConditions::getStringForWhere() const
    {
        stringstream output;
        output << joinMap(&FindConditions::getNameValuePair, " AND ");
        return output.str();
    }
}
