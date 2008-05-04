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

/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
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
    
        /*!
         *  HasMany constructor.
         */
        HasMany();

        /*!
         * Copy constructor.
         *
         * \param rhs The instance to copy values from.
         */
        HasMany(const HasMany&);

        /*!
         *  Virtual destructor.
         */
        virtual ~HasMany();
        
        /*!
         * Assignment operator.
         *
         * \param rhs The instance to copy values from.
         * 
         * \return A reference to the current instance.
         */
        HasMany& operator=(const HasMany&);

        /*!
         * Returns a boolean value stating whether the current instance 
         * has children elements in it.
         *
         * \return A boolean value stating whether there are children (true) or not (false)
         */
        const bool hasChildren() const;

        /*!
         * Adds the pointer passed as parameter to the collection of child instances.
         *
         * \param child The pointer to add to the children collection.
         */
        void addChild(C*);

        /*!
         * Returns the number of children associated to the current instance.
         *
         * \return The number of children.
         */
        const int getChildrenCount() const;
        
        /*!
         * Returns the child whose name is passed as parameter.
         *
         * \param name The name of the child being sought.
         *
         * \return A pointer to the instance, or NULL if none was found.
         */
        C* getChild(const std::string&);

        /*!
         * Removes the child whose name is passed as parameter.
         *
         * \param name The name of the child to be deleted.
         */
        void removeChild(const std::string&);
        
        /*!
         * Removes all the child elements associated to the current instance.
         */
        void removeAllChildren();
        
        /*!
         * Saves all the child elements associated to the current instance.
         */
        void saveChildren();

    private:
        //! Shortcut to make code more readable.
        typedef std::map<std::string, C*> InternalMap;

    private:
        //! The children objects related to the current instance.
        InternalMap _children;
    };

    /*!
     * HasMany constructor.
     */
    template <class C, class P>
    HasMany<C, P>::HasMany()
    : _children()
    {
    }

    /*!
     * Copy constructor.
     *
     * \param rhs The instance to copy values from.
     */
    template <class C, class P>
    HasMany<C, P>::HasMany(const HasMany& rhs)
    : _children()
    {
    }

    /*!
     * Assignment operator.
     *
     * \param rhs The instance to copy values from.
     * 
     * \return A reference to the current instance.
     */
    template <class C, class P>
    HasMany<C, P>& HasMany<C, P>::operator=(const HasMany& rhs)
    {
        return *this;
    }
    
    /*!
     * Virtual destructor.
     */
    template <class C, class P>
    HasMany<C, P>::~HasMany()
    {
    }

    /*!
     * Returns a boolean value stating whether the current instance 
     * has children elements in it.
     *
     * \return A boolean value stating whether there are children (true) or not (false)
     */
    template <class C, class P>
    const bool HasMany<C, P>::hasChildren() const
    {
        return !_children.empty();
    }

    /*!
     * Adds the pointer passed as parameter to the collection of child instances.
     *
     * \param child The pointer to add to the children collection.
     */
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
            child->setParent(dynamic_cast<P*>(this));
            dynamic_cast<P*>(this)->setDirty();
        }
    }

    /*!
     * Returns the number of children associated to the current instance.
     *
     * \return The number of children.
     */
    template <class C, class P>
    const int HasMany<C, P>::getChildrenCount() const
    {
        return _children.size();
    }

    /*!
     * Returns the child whose name is passed as parameter.
     *
     * \param name The name of the child being sought.
     *
     * \return A pointer to the instance, or NULL if none was found.
     */
    template <class C, class P>
    C* HasMany<C, P>::getChild(const std::string& name)
    {
        return _children[name];
    }

    /*!
     * Removes the child whose name is passed as parameter.
     *
     * \param name The name of the child to be deleted.
     */
    template <class C, class P>
    void HasMany<C, P>::removeChild(const std::string& name)
    {
        C* element = _children[name];
        if (element)
        {
            element->destroy();
            delete element;
            _children.erase(name);
            dynamic_cast<P*>(this)->setDirty();
        }
    }

    /*!
     * Removes all the child elements associated to the current instance.
     */
    template <class C, class P>
    void HasMany<C, P>::removeAllChildren()
    {
        // For the explanation of the "typename" keyword below, see
        // http://gcc.gnu.org/ml/gcc-help/2008-01/msg00137.html and
        // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18

        typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            C* element = (*iter).second;
            element->destroy();
            delete element;
        }
        _children.clear();
    }
    
    /*!
     * Saves all the child elements associated to the current instance.
     */
    template <class C, class P>
    void HasMany<C, P>::saveChildren()
    {
        typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            iter->second->save();
        }
    }
}

#endif /* HASMANY_H_ */
