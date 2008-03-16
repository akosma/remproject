/*!  
 * \file untitled 2.h
 * 
 * Contains the interface of the MetaModel::Project class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#ifndef DIAGRAM_H_
#include "Diagram.h"
#endif

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * \class Project "$URL$"
     *
     *  
     */
    class Project
    {
    public:

        /*!
         *  Project constructor.
         */
        Project();

        /*!
         * Project virtual destructor.
         */
        virtual ~Project();
        
        const bool empty() const;

        void addDiagram(Diagram* diagram);
        
        const int getDiagramCount() const;
        
        Diagram* getDiagram(const std::string& name);
        
        void removeDiagram(const std::string& diagramName);

    private:
        DiagramMap _diagrams;
    };

}

#endif /* PROJECT_H_ */
