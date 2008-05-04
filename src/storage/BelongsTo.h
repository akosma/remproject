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
 * \file BelongsTo.h
 *
 * Contains the interface and implementation of the storage::BelongsTo template class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/28/08
 */

#ifndef BELONGSTO_H_
#define BELONGSTO_H_

#include <sstream>

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    /*!
     * \class BelongsTo
     *
     *  
     */
    template <class P>
    class BelongsTo
    {
    public:

        /*!
         *  BelongsTo constructor.
         */
        BelongsTo();

        /*!
         *  BelongsTo virtual destructor.
         */
        virtual ~BelongsTo();
        BelongsTo(const BelongsTo<P>&);
        BelongsTo<P>& operator=(const BelongsTo<P>&);
        
        const bool hasParent() const;
        void setParent(P*);
        P* getParent() const;
        const storage::ID getParentId() const;
        const std::string& getParentColumn() const;
        
    private:
        P* _parent;
        std::string _parentColumn;
    };

    /*!
     * 
     */
    template <class P>
    BelongsTo<P>::BelongsTo()
    : _parent(0)
    , _parentColumn("")
    {
        std::stringstream name;
        name << P::getTableName();
        name << "_id";
        _parentColumn = name.str();
    }
    
    template <class P>
    BelongsTo<P>::~BelongsTo()
    {
    }
    
    template <class P>
    BelongsTo<P>::BelongsTo(const BelongsTo<P>& rhs)
    : _parent(0)
    , _parentColumn("")
    {
    }
    
    template <class P>
    BelongsTo<P>& BelongsTo<P>::operator=(const BelongsTo<P>& rhs)
    {
        return *this;
    }
    
    template <class P>
    const bool BelongsTo<P>::hasParent() const
    {
        return _parent != NULL;
    }
    
    template <class P>
    void BelongsTo<P>::setParent(P* parent)
    {
        _parent = parent;
    }
    
    template <class P>
    P* BelongsTo<P>::getParent() const
    {
        return _parent;
    }
    
    template <class P>
    const storage::ID BelongsTo<P>::getParentId() const
    {
        if (_parent)
        {
            return _parent->getId();
        }
        else
        {
            return storage::DEFAULT_ID;
        }
    }
    
    template <class P>
    const std::string& BelongsTo<P>::getParentColumn() const
    {
        return _parentColumn;
    }
}

#endif /* BELONGSTO_H_ */
