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

//! Contains the interface and implementation of the storage::HasMany template class.
/*!
 * \file HasMany.h
 *
 * Contains the interface and implementation of the storage::HasMany template class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef HASMANY_H_
#define HASMANY_H_

#include <string>
#include <map>
#include <vector>

#ifndef ANYPROPERTYMAP_H_
#include "AnyPropertyMap.h"
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
    //! Represents a "has many" relationship between ActiveRecord classes
    /*!
     * \class HasMany
     *
     * Used by ActiveRecord subclasses to create a simple relationship between an
     * instance and its related children. This template class is closely related to
     * the BelongsTo template class.
     */
    template <class C>
    class HasMany : public virtual Persistable
    {
    public:
        //! Default constructor.
        /*!
         *  HasMany constructor.
         */
        HasMany();

        //! Copy constructor.
        /*!
         * Copy constructor. The children instances are NOT copied.
         *
         * \param rhs The instance to copy values from.
         */
        HasMany(const HasMany&);

        //! Virtual destructor.
        /*!
         *  Virtual destructor.
         */
        virtual ~HasMany();
        
        //! Assignment operator.
        /*!
         * Assignment operator. Nothing is copied.
         *
         * \param rhs The instance to copy values from.
         * 
         * \return A reference to the current instance.
         */
        HasMany& operator=(const HasMany&);

        //! Tells whether the current instance has related elements.
        /*!
         * Returns a boolean value stating whether the current instance 
         * has children elements in it.
         *
         * \return A boolean value stating whether there are children (true) or not (false)
         */
        const bool hasChildren();

        //! Adds the object passed as parameter as child of the current instance.
        /*!
         * Adds the pointer passed as parameter to the collection of child instances.
         *
         * \param child The pointer to add to the children collection.
         */
        void addChild(C*);
        
        //! Adds the object passed as parameter as child of the current instance.
        /*!
         * Adds the pointer passed as parameter to the collection of child instances.
         * Using this operator is identical to a call to the "addChild()" method.
         *
         * \param child The pointer to add to the children collection.
         */
        HasMany& operator<<(C*);

        //! Gets the number of children of the current instance.
        /*!
         * Returns the number of children associated to the current instance.
         *
         * \return The number of children.
         */
        const int getChildrenCount();
        
        //! Returns the child whose name is passed as parameter.
        /*!
         * Returns the child whose name is passed as parameter.
         *
         * \param name The name of the child being sought.
         *
         * \return A pointer to the instance, or NULL if none was found.
         */
        C* getChild(const std::string&);

        //! Removes the child whose name is passed as parameter.
        /*!
         * Removes the child whose name is passed as parameter.
         *
         * \param name The name of the child to be deleted.
         */
        void removeChild(const std::string&);
        
        //! Removes all the children.
        /*!
         * Removes all the child elements associated to the current instance.
         */
        void removeAllChildren();
        
        //! Saves all the child elements associated to the current instance.
        /*!
         * Saves all the child elements associated to the current instance.
         */
        virtual void saveChildren();
        
        //! States whether the children are in memory.
        /*!
         * States whether the children are in memory.
         * 
         * \return A boolean; true if the children are in memory, false otherwise.
         */
        const bool hasLoadedChildren() const;
    
    private:
        //! Performs "lazy-loading" of children instances.
        /*!
         * Performs "lazy-loading" of children instances. This method is used 
         * by all the other methods that require the collection of children
         * instances to be available in memory.
         */
        void lazyLoadChildren();
        
    private:
        //! Shortcut to make the code more readable.
        typedef std::map<std::string, C*> InternalMap;

    private:
        //! The children objects related to the current instance.
        InternalMap _children;
        
        //! Flag used by the "lazyLoadChildren()" method.
        bool _childrenLoaded;
    };

    template <class C>
    HasMany<C>::HasMany()
    : _children()
    , _childrenLoaded(false)
    {
    }

    template <class C>
    HasMany<C>::HasMany(const HasMany& rhs)
    : _children()
    , _childrenLoaded(false)
    {
    }

    template <class C>
    HasMany<C>& HasMany<C>::operator=(const HasMany& rhs)
    {
        return *this;
    }
    
    template <class C>
    HasMany<C>::~HasMany()
    {
    }

    template <class C>
    const bool HasMany<C>::hasChildren()
    {
        lazyLoadChildren();
        return !_children.empty();
    }

    template <class C>
    void HasMany<C>::addChild(C* child)
    {
        if (child)
        {
            _children[child->getName()] = child;
            child->setParent(this);
            setDirty();
        }
    }
    
    template <class C>
    HasMany<C>& HasMany<C>::operator<<(C* child)
    {
        addChild(child);
        return *this;
    }

    template <class C>
    const int HasMany<C>::getChildrenCount()
    {
        lazyLoadChildren();
        return _children.size();
    }

    template <class C>
    C* HasMany<C>::getChild(const std::string& name)
    {
        lazyLoadChildren();
        return _children[name];
    }

    template <class C>
    void HasMany<C>::removeChild(const std::string& name)
    {
        lazyLoadChildren();
        C* element = _children[name];
        if (element)
        {
            element->destroy();
            delete element;
            _children.erase(name);
            setDirty();
        }
    }

    template <class C>
    void HasMany<C>::removeAllChildren()
    {
        // For the explanation of the "typename" keyword below, see
        // http://gcc.gnu.org/ml/gcc-help/2008-01/msg00137.html and
        // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18

        lazyLoadChildren();
        typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            C* element = (*iter).second;
            element->destroy();
            delete element;
        }
        _children.clear();
    }

    template <class C>
    void HasMany<C>::saveChildren()
    {
        typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            iter->second->save();
        }
        _childrenLoaded = true;
    }

    template <class C>
    const bool HasMany<C>::hasLoadedChildren() const
    {
        return _childrenLoaded;
    }

    template <class C>
    void HasMany<C>::lazyLoadChildren()
    {
        // It only makes sense to load children of objects
        // existing in the database...
        if (!isNew() && !_childrenLoaded)
        {
            // Do not load again
            _childrenLoaded = true;

            AnyPropertyMap conditions;
            conditions.setInteger(C::getParentColumnName(), getId());
            std::vector<C>* elements = C::findByCondition(conditions);

            typename std::vector<C>::iterator iter;
            for (iter = elements->begin(); iter != elements->end(); ++iter)
            {
                // Let's create a temporary object to insert into the internal map
                C* element = new C(*iter);
                _children[element->getName()] = element;
                delete element;
            }

            delete elements;
        }
    }
}

#endif /* HASMANY_H_ */
