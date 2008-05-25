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

/*!
 * \namespace utility
 * Insert a description for the namespace here
 */
namespace utility
{
    /*!
     * \class Singleton
     *
     *  
     */
    template <class T>
    class Singleton
    {
    public:

        /*!
         *  Singleton constructor.
         */
        Singleton();

        /*!
         *  Singleton virtual destructor.
         */
        virtual ~Singleton();

    protected:

    private:
        std::string _param;
    };
}

#endif /* SINGLETON_H_ */
