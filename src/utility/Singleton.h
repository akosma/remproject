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

//! Contains the interface of the utility::Singleton class.
/*!
 * \file Singleton.h
 *
 * Contains the interface of the utility::Singleton class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <string>
#include <vector>

//! Contains several classes used throughout the project.
/*!
 * \namespace utility
 * Contains several classes used throughout the project.
 */
namespace utility
{
    //! Adds a static methods returning a single instance for a class.
    /*!
     * \class Singleton
     *
     * Adds a static methods returning a single instance for a class.
     * Classes inheriting from this template should have a private 
     * constructor, together with a "friend" declaration for the static
     * "get()" method, providing a singleton suitable for single-threaded 
     * applications (this singleton is not thread-safe).
     */
    template <class T>
    class Singleton
    {
    public:

        //! Constructor.
        /*!
         * Constructor. Since this class is a singleton, 
         * only the static method "get()" is used to build and get a unique
         * instance for all the application. This singleton is not
         * thread-safe, but for this application, this is more than
         * enough.
         */
        Singleton();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~Singleton();

        //! Returns the singleton instance of this class.
        /*!
         * Returns the singleton instance of this class.
         * 
         * \return A reference to the singleton instance.
         */
        static T& get();
        
    private:

        //! Private copy constructor.
        /*!
         * Private copy constructor.
         * 
         * This trick comes from "Effective C++, Third Edition"
         * by Scott Meyers (ISBN 0-321-33487-6)
         * "Item 6: Explicitly disallow the use of compiler-generated
         * functions you do not want", page 37
         * 
         * \param rhs The SQLiteWrapper reference to copy from.
         */
        Singleton(const Singleton& rhs);

        //! Private assignment operator.
        /*!
         * Private assignment operator.
         * 
         * This trick comes from "Effective C++, Third Edition"
         * by Scott Meyers (ISBN 0-321-33487-6)
         * "Item 6: Explicitly disallow the use of compiler-generated
         * functions you do not want", page 37
         * 
         * \param rhs The SQLiteWrapper reference to copy from.
         * 
         * \return A reference to the current SQLiteWrapper.
         */
        Singleton& operator=(const Singleton& rhs);
    };
    
    template <class T>
    Singleton<T>::Singleton()
    {
    }
    
    template <class T>
    Singleton<T>::~Singleton()
    {
    }

    template <class T>
    T& Singleton<T>::get()
    {
        // Optimized Singleton instance for single-threaded applications
        // taken from http://www.inquiry.com/techtips/cpp_pro/10min/10min0200.asp
        // Classes using this template must have a "friend" declaration 
        // allowing this method to access their private constructor.
        static T _instance;
        return _instance;
    }
}

#endif /* SINGLETON_H_ */
