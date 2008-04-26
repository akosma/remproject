/*!
 * \file Toolbox.cpp
 *
 * Contains the implementation of the ui::Toolbox class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/20/08
 */

#include "Toolbox.h"

#ifndef TOOLBOXITEMFACTORY_H_
#include "ToolboxItemFactory.h"
#endif

#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * Toolbox Constructor.
     */
    Toolbox::Toolbox(ContentComponent* parent)
    : _initWidth(50.0)
    , _initHeight(200.0)
    , _factory(0)
    , _parent(parent)
    {
        setVertical(true);
        setBounds(0, 0, 50, 600);
        _factory = new ToolboxItemFactory();
        addDefaultItems(*_factory);
    }
    
    /*!
     * Toolbox Virtual destructor.
     */
    Toolbox::~Toolbox()
    {
        delete _factory;
    }
    
    void Toolbox::resized()
    {
    }
}
