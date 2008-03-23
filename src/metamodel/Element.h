/*!
 * \file Element.h
 *
 * Contains the interface of the metamodel::Element class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include <map>

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * \class Element
     *
     *  
     */
    class Element
    {
    public:

        /*!
         *  Element constructor.
         */
        Element(const std::string&);

        /*!
         *  Element virtual destructor.
         */
        virtual ~Element();
		
		const std::string& getName() const;

    protected:

    private:
        std::string _name;
    };
}

#endif /* ELEMENT_H_ */
