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

//! Contains the interface of the storage::Persistable class.
/*!
 * \file Persistable.h
 *
 * Contains the interface of the storage::Persistable class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/26/08
 */

#ifndef PERSISTABLE_H_
#define PERSISTABLE_H_

#ifndef SQLITEWRAPPER_H_
#include "SQLiteWrapper.h"
#endif

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! Abstract base class for the ActiveRecord family of classes.
    /*!
     * \class Persistable
     *
     * Abstract base class for the ActiveRecord family of classes
     * implemented in this namespace. This class provides a common
     * interface allowing "sister-class delegation" as explained here:
     * http://www.parashift.com/c++-faq-lite/multiple-inheritance.html#faq-25.10
     */
    class Persistable
    {
    public:

        //! \name Methods implemented in the ActiveRecord class.
        //@{
        
        //! Gets the ID of the current instance.
        /*!
         * Returns the ID of the current instance.
         * Implemented in the ActiveRecord class.
         * 
         * \return An ID (long long) value.
         */
        virtual const ID getId() const = 0;

        //! Changes the "_isDirty" flag of the current instance.
        /*!
         * Used to change the "_isDirty" flag in the 
         * ActiveRecord base class; subclasses must call this method in
         * every "setter" method.
         * Implemented in the ActiveRecord class.
         */
        virtual void setDirty() = 0;

        //! States whether the current instance exists only in memory.
        /*!
         * Returns a value indicating whether the current instance
         * exists in the database or not.
         * Implemented in the ActiveRecord class.
         * 
         * \return A boolean value stating whether the current instance 
         * exists in the database (false) or not (true).
         */
        virtual const bool isNew() const = 0;

        //! Saves (inserts or updates) the current instance to disk.
        /*!
         * This method is the core of the ActiveRecord family of
         * classes. Clients use it to write the current state of
         * the instance into the database.
         * Implemented in the ActiveRecord class.
         */
        virtual void save() = 0;

        //! Deletes the current instance from disk.
        /*!
         * Deletes the current instance from disk. It does not deletes
         * the object from memory though.
         * Implemented in the ActiveRecord class.
         */
        virtual void destroy() = 0;
        
        //@}

        //! \name Methods implemented in the BelongsTo class.
        //@{
        
        //! States whether the current instance has a parent or not.
        /*!
         * States whether the current instance has a parent or not.
         * Implemented in the BelongsTo class.
         * 
         * \return A boolean value.
         */
        virtual const bool hasParent() const = 0;

        //! Gets the parent of the current instance.
        /*!
         * Gets the parent of the current instance.
         * Implemented in the BelongsTo class.
         * 
         * \return A pointer to the parent of the current instance.
         */
        virtual Persistable* getParent() const = 0;
        
        //! Returns the ID of the parent of the current instance.
        /*!
         * Returns the ID of the parent of the current instance.
         * Implemented in the BelongsTo class.
         * 
         * \return A const storage::ID value.
         */
        virtual const storage::ID getParentId() const = 0;

        //@}

        //! \name Methods implemented in the HasMany class.
        //@{

        //! Saves all the child elements associated to the current instance.
        /*!
         * Saves all the child elements associated to the current instance.
         * Implemented in the HasMany class.
         */
        virtual void saveChildren() = 0;

        //@}
    };
}

#endif /* PERSISTABLE_H_ */
