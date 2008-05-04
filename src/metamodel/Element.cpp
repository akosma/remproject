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
#include "../metamodel/Project.h"
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
     * Element Constructor.
     * 
     * \param className The name of the subclass of the current instance.
     */
    Element::Element(const std::string& className)
    : ActiveRecord<Element, BelongsTo<Diagram>, HasMany<NoChildren, Element> >(className)
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
    Element::Element(const std::string& className, const storage::ID id, AnyPropertyMap& data)
    : ActiveRecord<Element, BelongsTo<Diagram>, HasMany<NoChildren, Element> >(className, id, data)
    {
    }
    
    /*!
     * Element Virtual destructor.
     */
    Element::~Element()
    {
    }

    /*!
     * Creates dynamically the complete structure of fields 
     * needed by all the instances of this class.
     */
    void Element::createSchemaStructure()
    {
        addIntegerProperty("x");
        addIntegerProperty("y");
        addIntegerProperty("width");
        addIntegerProperty("height");
    }

    /*!
     * Returns the name of the SQLite table to be used to store
     * instances of this class. This static method is required by
     * the "informal protocol" of the storage::ActiveRecord subsystem.
     *
     * \return A string with the name of the database table.
     */
    std::string& Element::getTableName()
    {
        static std::string tableName("elements");
        return tableName;
    }
}
