/*!
 * \file Toolbox.h
 *
 * Contains the interface of the ui::Toolbox class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/20/08
 */

#include "juce.h"

#ifndef TOOLBOX_H_
#define TOOLBOX_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ToolboxItemFactory;
    class ContentComponent;
    
    /*!
     * \class Toolbox
     *
     *  
     */
    class Toolbox : public Toolbar
    {
    public:

        /*!
         *  Toolbox constructor.
         */
        Toolbox(ContentComponent*);

        /*!
         *  Toolbox virtual destructor.
         */
        virtual ~Toolbox();
        
        void resized();
        
    private:
        const int _initWidth;
        const int _initHeight;
        ToolboxItemFactory* _factory;
        ContentComponent* _parent;
    };
}

#endif /* TOOLBOX_H_ */
