/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the interface of the ui::UMLDiagram class.
/*!
 * \file UMLDiagram.h
 *
 * Contains the interface of the ui::UMLDiagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include <Poco/AutoPtr.h>
#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>
#include <string>

#include "PlatformDefinitions.h"

#ifndef UMLDIAGRAM_H_
#define UMLDIAGRAM_H_

#ifndef ACTORFIGURE_H_
#include "ActorFigure.h"
#endif

#ifndef USECASEFIGURE_H_
#include "UseCaseFigure.h"
#endif

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

#ifndef FIGURESELECTED_H_
#include "../notifications/FigureSelected.h"
#endif

#ifndef ARROWCANVASCLICKED_H_
#include "../notifications/ArrowCanvasClicked.h"
#endif

#ifndef FIGURECHANGED_H_
#include "../notifications/FigureChanged.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "../notifications/NewFigureAdded.h"
#endif

// Forward declaration to avoid includes
namespace metamodel
{
    class Diagram;
}

using Poco::AutoPtr;
using Poco::NotificationCenter;
using Poco::NObserver;
using notifications::FigureSelected;
using notifications::ArrowCanvasClicked;
using notifications::FigureChanged;
using notifications::NewFigureAdded;
using metamodel::Diagram;
using std::string;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    class Figure;
    class ArrowCanvas;
    class FigureLassoSource;
    class DiagramToolbar;
    class LineFigure;
    
    /*!
     * \class UMLDiagram
     *
     *  
     */
    class UMLDiagram : public Component
    {
    public:
        UMLDiagram(const string&);
        virtual ~UMLDiagram();

        void paint (Graphics&);

        void resize();

        void toggleGrid();
        const string& getUniqueId() const;
        void deleteSelectedFigures();
        
        virtual DiagramToolbar* createToolbar() = 0;
        virtual void addFigure(const AutoPtr<NewFigureAdded>&) = 0;
        virtual void populateFrom(Diagram*) = 0;

    protected:
        const int getSelectedItemsCount() const;
        const Array<Figure*>& getSelectedItems();
        Figure* getFigureByUniqueId(const string& uniqueId);
        void setGridVisible(const bool);
        
    protected:
        void handleFigureSelected(const AutoPtr<FigureSelected>&);
        void handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>&);
        void handleFigureChanged(const AutoPtr<FigureChanged>&);
        void addLineToCanvas(LineFigure*);
        
    private:
        ArrowCanvas* _canvas;
        SelectedItemSet<Figure*> _selection;
        NObserver<UMLDiagram, FigureSelected>* _figureObserver;
        NObserver<UMLDiagram, ArrowCanvasClicked>* _arrowObserver;
        NObserver<UMLDiagram, FigureChanged>* _changeObserver;
        const string _id;
    };
}

#endif /* UMLDIAGRAM_H_ */
