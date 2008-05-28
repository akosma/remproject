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

//! Implementation of the Project class
/*!  
 * \file Project.cpp
 * 
 * Contains the implementation of the metamodel::Project class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "Project.h"

#ifndef ELEMENT_H_
#include "Element.h"
#endif

#ifndef DIAGRAM_H_
#include "Diagram.h"
#endif

using storage::ActiveRecord;
using storage::BelongsTo;
using storage::HasMany;

namespace metamodel
{
    Project::Project()
    : ActiveRecord<Project>(std::string("project"))
    , HasMany<Diagram>()
    {
    }

    Project::Project(AnyPropertyMap& data)
    : ActiveRecord<Project>(data)
    , HasMany<Diagram>()
    {
    }

    Project::~Project()
    {
    }

    std::string& Project::getTableName()
    {
        static std::string tableName("projects");
        return tableName;
    }

    std::string& Project::getParentColumnName()
    {
        static std::string columnName("no_parent");
        return columnName;
    }

    void Project::createSchemaStructure()
    {
        addProperty<std::string>("author");
        addProperty<double>("version");
    }
}
