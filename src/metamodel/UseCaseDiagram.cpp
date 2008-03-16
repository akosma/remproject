/*!
 * \file UseCaseDiagram.cpp
 *
 * Contains the implementation of the MetaModel::UseCaseDiagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "UseCaseDiagram.h"

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * UseCaseDiagram Constructor.
     */
    UseCaseDiagram::UseCaseDiagram(const std::string& name)
	: Diagram(name)
    {
    }
    
    /*!
     * UseCaseDiagram Virtual destructor.
     */
    UseCaseDiagram::~UseCaseDiagram()
    {
    }
}
