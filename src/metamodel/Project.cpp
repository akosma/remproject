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

using namespace storage;

/*!
 * \namespace metamodel
 * Holds the classes representing the different parts of an UML project.
 */
namespace metamodel
{
    /*!
     * Project Constructor. This constructor does not take parameters,
     * since each SQLite file has one and only one Project instance.
     */
    Project::Project()
    : ActiveRecord<Project, BelongsTo<NoParent>, HasMany<Diagram, Project> >(std::string("project"))
    {
    }

    /*!
     * Constructor required by ActiveRecord, to instantiate objects
     * that are retrieved from the SQLite file.
     * 
     * \param className The subclass name of the current instance.
     * \param id The ID of the current instance.
     * \param data The data of the current instance.
     */
    Project::Project(std::string& className, storage::ID id, AnyPropertyMap& data)
    : ActiveRecord<Project, BelongsTo<NoParent>, HasMany<Diagram, Project> >(className, id, data)
    {
    }
    
    /*!
     * Project Virtual destructor.
     */
    Project::~Project()
    {
    }

    /*!
     * Creates dynamically the complete structure of fields 
     * needed by all the instances of this class.
     */
    void Project::createSchemaStructure()
    {
        addStringProperty("author");
        addDoubleProperty("version");
    }
    
    /*!
     * Returns the name of the SQLite table to be used to store
     * instances of this class. This static method is required by
     * the "informal protocol" of the storage::ActiveRecord subsystem.
     *
     * \return A string with the name of the database table.
     */
    std::string& Project::getTableName()
    {
        static std::string tableName("projects");
        return tableName;
    }
}
