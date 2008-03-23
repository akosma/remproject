/*!
 * \file Diagram.cpp
 *
 * Contains the implementation of the metamodel::Diagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Diagram.h"

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * Diagram Constructor.
     */
    Diagram::Diagram(const std::string& name)
	: Container<Element>(),
	  _name(name)
    {
    }
    
    /*!
     * Diagram Virtual destructor.
     */
    Diagram::~Diagram()
    {
    }

    const std::string& Diagram::getName() const
    {
        return _name;
    }
}
