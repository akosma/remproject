/*!
 * \file ArrowCanvas.cpp
 *
 * Contains the implementation of the ui::ArrowCanvas class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/21/08
 */

#include "ArrowCanvas.h"

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
     * ArrowCanvas Constructor.
     */
    ArrowCanvas::ArrowCanvas(ContentComponent* parent)
    : _parent(parent)
    , _strokeWidth(1.0f)
    {
        setBroughtToFrontOnMouseClick(false);
        setBufferedToImage(true);
        setInterceptsMouseClicks(false, false);
    }
    
    /*!
     * ArrowCanvas Virtual destructor.
     */
    ArrowCanvas::~ArrowCanvas()
    {
    }

    void ArrowCanvas::paint(Graphics& g)
    {
        g.fillAll(Colours::white);
        g.setColour(Colours::black);
        Path arrows;
        arrows.addArrow(10.0f, 10.0f, 400.0f, 400.0f, 1.0f, 20.0f, 20.0f);
        g.strokePath(arrows, PathStrokeType (1.0f));
    }
}
