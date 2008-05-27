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

//! Contains the interface of the storage::None class.
/*!
 * \file None.h
 *
 * Contains the interface of the storage::None class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/26/08
 */

#ifndef NONE_H_
#define NONE_H_

#include <string>

#ifndef PERSISTABLE_H_
#include "Persistable.h"
#endif

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! Dummy class used in template instantiation.
    /*!
     * \class None
     *
     * Dummy class used by ActiveRecord subclasses who do not wish
     * to be related to a "parent" class or to have related children. 
     * It implements stubs for many methods required during template 
     * instantiation at compile-time.
     */
    class None : public Persistable
    {
    public:
        //! Constructor
        /*!
         * Constructor
         */
        None();

        //! Virtual destructor
        /*!
         * Virtual destructor
         */
        virtual ~None();

        //! Placeholder method required at template instantiation time.
        /*!
         * Placeholder method required at template instantiation time
         */
        virtual const ID getId() const;

        //! Placeholder method required at template instantiation time.
        /*!
         * Placeholder method required at template instantiation time
         */
        virtual void setDirty();

        //! Placeholder method required at template instantiation time.
        /*!
         * Placeholder method required at template instantiation time
         */
        virtual const bool hasParent() const;

        //! Placeholder method required at template instantiation time.
        /*!
         * Placeholder method required at template instantiation time
         */
        virtual void save();

        //! Placeholder method required at template instantiation time.
        /*!
         * Placeholder method required at template instantiation time
         */
        virtual void saveChildren();

    private:
        //! Used to return a valid string reference only
        std::string _parentColumn;
    };
}

#endif /* NONE_H_ */
