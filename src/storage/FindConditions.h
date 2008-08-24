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

//! Contains the interface of the storage::FindConditions class.
/*!
 * \file ActiveRecord.h
 *
 * Contains the interface of the storage::FindConditions class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/06/08
 */

#ifndef FINDCONDITIONS_H_
#define FINDCONDITIONS_H_

#ifndef ANYPROPERTYMAP_H_
#include "AnyPropertyMap.h"
#endif

using storage::AnyPropertyMap;

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage 
{
    //! Specifies a set of conditions to be used for retrieving data from a SQLite file.
    /*!
     * Specifies a set of conditions to be used for retrieving data from a SQLite file.
     */
    class FindConditions : public AnyPropertyMap
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        FindConditions();
        
        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~FindConditions();

        //! Generates a WHERE SQL statement.
        /*!
         * Generates a WHERE SQL statement.
         * 
         * \return A string.
         */
        const string getStringForWhere() const;        
    };
}

#endif /* FINDCONDITIONS_H_ */
