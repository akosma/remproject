/*!
 * \file Element.cpp
 *
 * Contains the implementation of the MetaModel::Element class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Element.h"

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * Element Constructor.
     */
    Element::Element(const std::string& name)
	:_name(name)
    {
    }
    
    /*!
     * Element Virtual destructor.
     */
    Element::~Element()
    {
    }
	
	const std::string& Element::getName() const
	{
		return _name;
	}
}
