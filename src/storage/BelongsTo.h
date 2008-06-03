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

//! Contains the interface and implementation of the storage::BelongsTo template class.
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

#ifndef SQLITEWRAPPER_H_
#include "SQLiteWrapper.h"
#endif

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
    //! Represents a child-parent relationship.
    /*!
     * \class BelongsTo
     *
     * Used by ActiveRecord subclasses to create a simple relationship between an
     * instance and its related parent. This template class is closely related to
     * the HasMany template class.
     */
    template <class P>
    class BelongsTo : public virtual Persistable
    {
    public:

        //! Constructor.
        /*!
         *  Constructor.
         */
        BelongsTo();

        //! Virtual destructor.
        /*!
         *  Virtual destructor.
         */
        virtual ~BelongsTo();
        
        //! Copy constructor.
        /*!
         * Copy constructor.
         * 
         * \param rhs The object to assign to the current instance.
         */
        BelongsTo(const BelongsTo<P>&);
        
        //! Assignment operator.
        /*!
         * Assignment operator.
         * 
         * \param rhs The object to assign to the current instance.
         * 
         * \return A reference to the current instance.
         */
        BelongsTo<P>& operator=(const BelongsTo<P>&);

        //! States whether the current instance has a parent or not.
        /*!
         * States whether the current instance has a parent or not.
         * 
         * \return A boolean value.
         */
        virtual const bool hasParent() const;
        
        //! Sets a parent to the current instance.
        /*!
         * Sets a parent to the current instance.
         * 
         * \param parent A pointer to the instance of which this object is child.
         */
        void setParent(Persistable*);
        
        //! Gets the parent of the current instance.
        /*!
         * Gets the parent of the current instance.
         * 
         * \return A pointer to the parent of the current instance.
         */
        virtual Persistable* getParent() const;
        
        //! Gets a cast-down pointer to the parent of the current instance.
        /*!
         * Gets a cast-down pointer to the parent of the current instance.
         * This is a convenience method, to avoid clients having to implement
         * a dynamic_cast<>() operation every time.
         * 
         * \return A pointer to the parent of the current instance.
         */
        P* getCastParent() const;
    
    private:
        
        //! Holds the pointer to the parent of the current instance.
        P* _parent;
    };

    template <class P>
    BelongsTo<P>::BelongsTo()
    : _parent(0)
    {
    }
    
    template <class P>
    BelongsTo<P>::~BelongsTo()
    {
    }
    
    template <class P>
    BelongsTo<P>::BelongsTo(const BelongsTo<P>& rhs)
    : _parent(0)
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
    void BelongsTo<P>::setParent(Persistable* parent)
    {
        // Here we enforce the interface that, for polymorphic
        // reasons, cannot be enforced in the method signature!
        _parent = dynamic_cast<P*>(parent);
    }
    
    template <class P>
    Persistable* BelongsTo<P>::getParent() const
    {
        return (Persistable*)(_parent);
    }
    
    template <class P>
    P* BelongsTo<P>::getCastParent() const
    {
        return _parent;
    }
}

#endif /* BELONGSTO_H_ */
