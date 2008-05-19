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

#ifndef ACTIVERECORD_H_
#include "ActiveRecord.h"
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
    template <class C, class P>
    class HasMany
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
        void saveChildren();
        
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
        
        //! Returns a "casted-down" pointer of the current instance.
        /*!
         * Returns a "casted-down" pointer of the current instance, 
         * and caches it for future use.
         *
         * \return A "casted-down" pointer of the current instance.
         */
        P* getSelf();

    private:
        //! Shortcut to make the code more readable.
        typedef std::map<std::string, C*> InternalMap;

    private:
        //! The children objects related to the current instance.
        InternalMap _children;
        
        //! Flag used by the "lazyLoadChildren()" method.
        bool _childrenLoaded;
        
        //! Variable used to access members through dynamic_cast<>
        P* _self;
    };

    template <class C, class P>
    HasMany<C, P>::HasMany()
    : _children()
    , _childrenLoaded(false)
    , _self(NULL)
    {
    }

    template <class C, class P>
    HasMany<C, P>::HasMany(const HasMany& rhs)
    : _children()
    , _childrenLoaded(false)
    , _self(NULL)
    {
    }

    template <class C, class P>
    HasMany<C, P>& HasMany<C, P>::operator=(const HasMany& rhs)
    {
        return *this;
    }
    
    template <class C, class P>
    HasMany<C, P>::~HasMany()
    {
    }

    template <class C, class P>
    const bool HasMany<C, P>::hasChildren()
    {
        lazyLoadChildren();
        return !_children.empty();
    }

    template <class C, class P>
    void HasMany<C, P>::addChild(C* child)
    {
        if (child)
        {
            _children[child->getName()] = child;
            
            // The logic behind the "dynamic_cast" below is brilliantly
            // explained here:
            // http://carcino.gen.nz/tech/cpp/multiple_inheritance_this.php
            // Also look at 
            // http://www.acm.org/crossroads/xrds3-1/ovp3-1.html
            // for a good explanation of the different C++ cast operators.

            // Basically, when using multiple inheritance, you must use 
            // the dynamic_cast operator to get the correct "this" pointer
            // value needed. And this also explains the need of a second
            // template class parameter, with the type of the parent.
            child->setParent(getSelf());
            getSelf()->setDirty();
        }
    }

    template <class C, class P>
    const int HasMany<C, P>::getChildrenCount()
    {
        lazyLoadChildren();
        return _children.size();
    }

    template <class C, class P>
    C* HasMany<C, P>::getChild(const std::string& name)
    {
        lazyLoadChildren();
        return _children[name];
    }

    template <class C, class P>
    void HasMany<C, P>::removeChild(const std::string& name)
    {
        lazyLoadChildren();
        C* element = _children[name];
        if (element)
        {
            element->destroy();
            delete element;
            _children.erase(name);
            getSelf()->setDirty();
        }
    }

    template <class C, class P>
    void HasMany<C, P>::removeAllChildren()
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

    template <class C, class P>
    void HasMany<C, P>::saveChildren()
    {
        typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            iter->second->save();
        }
        _childrenLoaded = true;
    }

    template <class C, class P>
    const bool HasMany<C, P>::hasLoadedChildren() const
    {
        return _childrenLoaded;
    }

    template <class C, class P>
    void HasMany<C, P>::lazyLoadChildren()
    {
        // It only makes sense to load children of objects
        // existing in the database...
        if (!getSelf()->isNew() && !_childrenLoaded)
        {
            // Do not load again
            _childrenLoaded = true;

            AnyPropertyMap conditions;
            conditions.setInteger(P::getTableName() + "_id", getSelf()->getId());
            std::vector<C>* elements = ActiveRecord<C, P>::findByCondition(conditions);

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
    
    template <class C, class P>
    P* HasMany<C, P>::getSelf()
    {
        if (!_self)
        {
            _self = dynamic_cast<P*>(this);
        }
        return _self;
    }
}

#endif /* HASMANY_H_ */
