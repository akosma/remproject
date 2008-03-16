/*!  
 * \file untitled 2.h
 * 
 * Contains the implementation of the Metamodel::Project class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "Project.h"

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * Project Constructor.
     */
    Project::Project()
    : _diagrams(DiagramMap())
    {
    }
    
    /*!
     * Project Virtual destructor.
     */
    Project::~Project()
    {
    }
    
    const bool Project::empty() const
    {
        return _diagrams.empty();
    }
    
    void Project::addDiagram(Diagram* diagram)
    {
        _diagrams[diagram->getName()] = diagram;
    }
    
    const int Project::getDiagramCount() const
    {
        return _diagrams.size();
    }
    
    Diagram* Project::getDiagram(const std::string& name)
    {
        return _diagrams[name];
    }
    
    void Project::removeDiagram(const std::string& diagramName)
    {
        _diagrams.erase(diagramName);
    }
}
