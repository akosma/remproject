/*!
 * \file Diagram.h
 *
 * Contains the interface of the MetaModel::Diagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef DIAGRAM_H_
#define DIAGRAM_H_

#ifndef CONTAINER_H_
#include "Container.h"
#endif

#ifndef ELEMENT_H_
#include "Element.h"
#endif

#include <map>
#include <string>

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * \class Diagram
     *
     *  
     */
    class Diagram : public Container<Element>
    {
    public:

        /*!
         *  Diagram constructor.
         */
        Diagram(const std::string&);

        /*!
         *  Diagram virtual destructor.
         */
        virtual ~Diagram();

        const std::string& getName() const;
		
	private:
		std::string _name;
	};
}

#endif /* DIAGRAM_H_ */
