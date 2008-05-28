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

//! Implementation of the Diagram class
/*!
 * \file Diagram.cpp
 *
 * Contains the implementation of the metamodel::Diagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Diagram.h"

#ifndef PROJECT_H_
#include "Project.h"
#endif

#ifndef ELEMENT_H_
#include "Element.h"
#endif

using storage::ActiveRecord;
using storage::BelongsTo;
using storage::HasMany;

namespace metamodel
{
    Diagram::Diagram(const std::string& className)
    : ActiveRecord<Diagram>(className)
    , BelongsTo<Project>()
    , HasMany<Element>()
    {
    }

    Diagram::Diagram(const std::string& className, const storage::ID id, AnyPropertyMap& data)
    : ActiveRecord<Diagram>(className, id, data)
    , BelongsTo<Project>()
    , HasMany<Element>()
    {
    }

    Diagram::~Diagram()
    {
    }

    std::string& Diagram::getTableName()
    {
        static std::string tableName("diagrams");
        return tableName;
    }

    std::string& Diagram::getParentColumnName()
    {
        static std::string columnName("project_id");
        return columnName;
    }

    void Diagram::createSchemaStructure()
    {
        addProperty<bool>("valid");
    }
}
