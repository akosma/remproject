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

//! Interface of the Project class
/*!  
 * \file Project.h
 * 
 * Contains the interface of the metamodel::Project class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

#ifndef BELONGSTO_H_
#include "../storage/BelongsTo.h"
#endif

#ifndef HASMANY_H_
#include "../storage/HasMany.h"
#endif

#ifndef NONE_H_
#include "../storage/None.h"
#endif

using storage::ActiveRecord;
using storage::BelongsTo;
using storage::HasMany;
using storage::None;

//! Model classes for UML projects
/*!
 * \namespace metamodel
 * Holds the classes representing the different parts of an UML project.
 */
namespace metamodel
{
     // Forward declaration of the Diagram class, used as parameter for the 
     // template specializations in the Project class declaration.
    class Diagram;

    //! Represents a set of Diagram instances
    /*!
     * \class Project
     *
     * Represents a single Project, containing many diagrams in it.
     */
    class Project : public ActiveRecord<Project>
                  , public BelongsTo<None>
                  , public HasMany<Diagram>
    {
    public:

        //! Default constructor
        /*!
         * Project constructor. This constructor does not take parameters,
         * since each SQLite file has one and only one Project instance.
         */
        Project();

        //! Constructor used for instances retrieved from a file
        /*!
         * Constructor required by ActiveRecord, to instantiate objects
         * that are retrieved from the SQLite file.
         * 
         * \param className The subclass name of the current instance.
         * \param id The ID of the current instance.
         * \param data The data of the current instance.
         */
        Project(const std::string&, const storage::ID, storage::AnyPropertyMap&);

        //! Virtual destructor
        /*!
         * Project virtual destructor.
         */
        virtual ~Project();

        //! Get the name of the table used to store instances of this class
        /*!
         * Returns the name of the SQLite table to be used to store
         * instances of this class. This static method is required by
         * the "informal protocol" of the storage::ActiveRecord subsystem.
         *
         * \return A string with the name of the database table.
         */
        static std::string& getTableName();

        //! Get the name of the column used to store the ID of the parent of this class
        /*!
         * Returns the name of the SQLite column to be used to store the ID 
         * of the parent instance of this class. This static method is required by
         * the "informal protocol" of the storage::ActiveRecord subsystem.
         *
         * \return A string with the name of the database table.
         */
        static std::string& getParentColumnName();

    protected:
        
        //! Create all the fields required for all the instances of this class.
        /*!
         * Creates dynamically the complete structure of fields 
         * needed by all the instances of this class.
         */
        virtual void createSchemaStructure();
    };
}

#endif /* PROJECT_H_ */
