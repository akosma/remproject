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

//! Implementation of the Element class
/*!
 * \file Element.cpp
 *
 * Contains the implementation of the metamodel::Element class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Element.h"

#ifndef PROJECT_H_
#include "Project.h"
#endif

#ifndef DIAGRAM_H_
#include "Diagram.h"
#endif

using storage::ActiveRecord;
using storage::BelongsTo;
using storage::HasMany;
using std::string;

namespace metamodel
{
    Element::Element(const string& className)
    : ActiveRecord<Element>(className)
    , BelongsTo<Diagram>()
    , HasMany<Member>()
    {
    }

    Element::Element(AnyPropertyMap& data)
    : ActiveRecord<Element>(data)
    , BelongsTo<Diagram>()
    , HasMany<Member>()
    {
    }

    Element::~Element()
    {
    }

    string& Element::getTableName()
    {
        static string tableName("elements");
        return tableName;
    }

    string& Element::getParentColumnName()
    {
        static string columnName("diagram_id");
        return columnName;
    }

    void Element::createSchemaStructure()
    {
        addProperty<int>("x");
        addProperty<int>("y");
        addProperty<int>("width");
        addProperty<int>("height");
        addProperty<string>("start");
        addProperty<string>("end");
        addProperty<string>("title");
        set<bool>("selected", false);
    }
}
