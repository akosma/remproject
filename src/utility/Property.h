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

//! Contains the interface and implementation of the utility::Property template class.
/*!
 * \file Property.h
 *
 * Contains the interface and implementation of the utility::Property template class.
 * This code is adapted from page 51 of
 * Duffy, Daniel J.; "Financial Instrument Pricing Using C++",
 * 2004, John Wiley & Sons, ISBN 0-470-85509-6
 * (C) Datasim Education BV 2002-2004
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <string>

//! Contains several classes used throughout the project.
/*!
 * \namespace utility
 *
 * Contains several classes used throughout the project.
 */
namespace utility
{
    //! Represents a tuple "name=value"
    /*!
     * \class Property
     *
     * Represents a strongly-typed structure with a name and a value.
     */
    template <class N = std::string, class V = double>
    class Property
    {
    public:
        /*!
         * Property constructor. Creates a new Property instance with default values.
         */
        Property();
        
        /*!
         * Property constructor. Creates a new Property with the name passed as parameter.
         * 
         * \param name The name of the new instance.
         */
        Property(const N&);
        
        /*!
         * Property constructor. Creates a new Property with the name and value passed as parameters.
         * 
         * \param name The name of the new instance.
         * \param value The value of the new instance.
         */
        Property(const N&, const V&);
        
        /*!
         * Copy constructor.
         *
         * \param rhs A Property instance to copy name and values from.
         */
        Property(const Property<N, V>&);

        /*!
         * Virtual destructor.
         */
        virtual ~Property();
        
        /*!
         * Assignment operator.
         *
         * \param rhs A Property instance to copy name and values from.
         * 
         * \return A reference to the current instance.
         */
        Property<N, V>& operator=(const Property<N, V>&);

        /*!
         * Comparison operator. Tests whether the current instance is "equal" (that is,
         * whether it has the same name and value) as the Property 
         * passed as parameter.
         * 
         * \param rhs The Property instance to compare to.
         *
         * \return A boolean stating whether both instances were equal (true) or not (false)
         */
        const bool operator==(const Property<N, V>&);

        /*!
         * Parenthesis operator. Same as Property::getValue()
         *
         * \return The value of the current instance.
         */
        virtual V operator()() const;
        
        /*!
         * Returns the value of the current instance.
         *
         * \return The value of the current instance.
         */
        virtual V getValue() const;

        /*!
         * Parenthesis operator. Same as Property::setValue(const V& value)
         *
         * \param value The new value for the current instance.
         */
        virtual void operator()(const V&);

        /*!
         * Sets the value of the current instance.
         *
         * \param value The new value for the current instance.
         */
        virtual void setValue(const V&);

        /*!
         * Returns the name of the current Property.
         *
         * \return The name of the current Property.
         */
        virtual N getName() const;

    private:
        //! The name of the current instance.
        N name;
        
        //! The value of the current instance.
        V value;
    };

    template <class N, class V> 
    Property<N, V>::Property()
    {
        this->name = N();
        this->value = V();
    }

    template <class N, class V> 
    Property<N, V>::Property(const N& name)
    {
        this->name = name;
        this->value = V();
    }

    template <class N, class V> 
    Property<N, V>::Property(const N& name, const V& value)
    {
        this->name = name;
        this->value = value;
    }

    template <class N, class V> 
    Property<N, V>::Property(const Property<N, V>& rhs)
    : name(rhs.name)
    , value(rhs.value)
    {
    }

    template <class N, class V> 
    Property<N, V>::~Property()
    {
    }

    template <class N, class V>  
    Property<N, V>& Property<N, V>::operator=(const Property<N, V>& rhs)
    {
        if (this != &rhs)
        {
            this->name = rhs.name;
            this->value = rhs.value;
        }

        return *this;
    }

    template <class N, class V> 
    const bool Property<N, V>::operator==(const Property<N, V>& rhs)
    {
        if (this->name != rhs.name)
        {
            return false;
        }
        if (this->value != rhs.value)
        {
            return false;
        }
        return true;
    }

    template <class N, class V> 
    V Property<N, V>::operator()() const
    {
        return this->value;
    }

    template <class N, class V> 
    V Property<N, V>::getValue() const
    {
        return this->value;
    }

    template <class N, class V>
    void Property<N, V>::operator()(const V& value)
    {
        this->value = value;
    }

    template <class N, class V>
    void Property<N, V>::setValue(const V& value)
    {
        this->value = value;
    }

    template <class N, class V> 
    N Property<N, V>::getName() const
    {
        return this->name;
    }
}

#endif /* PROPERTY_H_ */
