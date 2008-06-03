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

//! Implementation of the Member class
/*!
 * \file Member.cpp
 *
 * Contains the implementation of the metamodel::Member class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/28/08
 */

#include "Member.h"

#ifndef ELEMENT_H_
#include "Element.h"
#endif

using storage::ActiveRecord;
using storage::BelongsTo;
using storage::HasMany;
using std::string;

namespace metamodel
{
    Member::Member(const string& className)
    : ActiveRecord<Member>(className)
    , BelongsTo<Element>()
    {
    }

    Member::Member(AnyPropertyMap& data)
    : ActiveRecord<Member>(data)
    , BelongsTo<Element>()
    {
    }

    Member::~Member()
    {
    }

    string& Member::getTableName()
    {
        static string tableName("members");
        return tableName;
    }

    string& Member::getParentColumnName()
    {
        static string columnName("element_id");
        return columnName;
    }

    void Member::createSchemaStructure()
    {
        addProperty<int>("someint");
        addProperty<int>("anotherint");
    }
}
