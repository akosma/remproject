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
 * \file Element.h
 *
 * Contains the interface of the metamodel::Element class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

#ifndef BELONGSTO_H_
#include "../storage/BelongsTo.h"
#endif

#ifndef HASMANY_H_
#include "../storage/HasMany.h"
#endif

using namespace storage;

/*!
 * \namespace metamodel
 * Holds the classes representing the different parts of an UML project.
 */
namespace metamodel
{
    /*
     * Forward declaration of the Diagram class, used as parameter for the 
     * template specializations in the Element class declaration.
     */
    class Diagram;

    /*!
     * \class Element
     *
     * Represents a single visual element rendered inside a Diagram.
     */
    class Element : public ActiveRecord<Element
                         , BelongsTo<Diagram> 
                         , HasMany<NoChildren, Element> >
    {
    public:

        /*!
         *  Element constructor.
         * 
         * \param className The name of the subclass of the current instance.
         */
        Element(std::string&);

        /*!
         * Constructor required by ActiveRecord, to instantiate objects
         * that are retrieved from the SQLite file.
         * 
         * \param className The subclass name of the current instance.
         * \param id The ID of the current instance.
         * \param data The data of the current instance.
         */
        Element(std::string&, storage::ID, AnyPropertyMap&);

        /*!
         *  Element virtual destructor.
         */
        virtual ~Element();

        /*!
         * Returns the name of the SQLite table to be used to store
         * instances of this class. This static method is required by
         * the "informal protocol" of the storage::ActiveRecord subsystem.
         *
         * \return A string with the name of the database table.
         */
        static std::string& getTableName();

    protected:
        /*!
         * Creates dynamically the complete structure of fields 
         * needed by all the instances of this class.
         */
        virtual void createSchemaStructure();
        
    };
}

#endif /* ELEMENT_H_ */
