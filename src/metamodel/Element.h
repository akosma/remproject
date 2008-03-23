/*!
 * \file Element.h
 *
 * Contains the interface of the MetaModel::Element class.
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
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
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
