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

#include <map>
#include <string>

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    class Diagram;

    typedef std::map<std::string, Diagram*> DiagramMap;
    
    /*!
     * \class Diagram "$URL$"
     *
     *  
     */
    class Diagram
    {
    public:

        /*!
         *  Diagram constructor.
         */
        Diagram(const std::string& name);

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
