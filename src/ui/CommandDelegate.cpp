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

//! Contains the implementation of the ui::CommandDelegate class.
/*!
 * \file CommandDelegate.cpp
 *
 * Contains the implementation of the ui::CommandDelegate class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/3/08
 */

#include <Poco/NotificationCenter.h>

#ifndef EXPORTDIAGRAMASPNG_H_
#include "../notifications/ExportDiagramAsPNG.h"
#endif

#ifndef DIAGRAMTOGGLEGRID_H_
#include "../notifications/DiagramToggleGrid.h"
#endif

#ifndef NEWDIAGRAMADDED_H_
#include "../notifications/NewDiagramAdded.h"
#endif

#ifndef PROJECTFILEOPENED_H_
#include "../notifications/ProjectFileOpened.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "../notifications/NewFigureAdded.h"
#endif

#ifndef FILECONTROLLER_H_
#include "../controllers/FileController.h"
#endif

#ifndef NEWPROJECTCREATED_H_
#include "../notifications/NewProjectCreated.h"
#endif

#ifndef DELETESELECTEDFIGURES_H_
#include "../notifications/DeleteSelectedFigures.h"
#endif

#ifndef WINDOW_H_
#include "Window.h"
#endif

#ifndef APPLICATION_H_
#include "Application.h"
#endif

#include "CommandDelegate.h"

using Poco::NotificationCenter;
using controllers::FileController;
using notifications::ExportDiagramAsPNG;
using notifications::DiagramToggleGrid;
using notifications::NewDiagramAdded;
using notifications::NewFigureAdded;
using notifications::ProjectFileOpened;
using notifications::NewProjectCreated;
using notifications::DeleteSelectedFigures;

namespace ui
{
    CommandDelegate::CommandDelegate()
    : ApplicationCommandTarget()
    , Singleton<CommandDelegate>()
    , _fileController(FileController::get())
    {
    }
    
    CommandDelegate::~CommandDelegate()
    {
    }
    
    ApplicationCommandTarget* CommandDelegate::getNextCommandTarget()
    {
        return NULL;
    }
    
    void CommandDelegate::getAllCommands(Array<CommandID>& commands)
    {
        const CommandID ids[] = { 
            fileNewProject,
            fileOpen,
            fileSave,
            fileSaveAs,
            fileExportPNG,
#if JUCE_WIN32 || JUCE_LINUX
            fileQuit,
#endif
            editUndo,
            editCut,
            editCopy,
            editPaste,
            editDelete,
            
            projectNewUseCaseDiagram,
            projectNewClassDiagram,
            projectNewSequenceDiagram,
            
            diagramAddActor,
            diagramAddUseCase,
            diagramAddArrow,
            diagramAddLine,
            diagramToggleGrid,
            
            helpAbout
        };
        commands.addArray(ids, numElementsInArray(ids));
    }

    void CommandDelegate::getCommandInfo(const CommandID command, ApplicationCommandInfo& info)
    {
        switch (command)
        {
            case fileNewProject:
            {
                info.shortName = "New Project";
                info.description = "Creates a new project, closing the current one if needed";
                info.flags = 0;
                info.addDefaultKeypress(110, ModifierKeys::commandModifier);  // CTRL + N
                info.setActive(true);
                break;
            }

            case fileOpen:
            {
                info.shortName = "Open...";
                info.description = "Opens a project in disk";
                info.flags = 0;
                info.addDefaultKeypress(111, ModifierKeys::commandModifier); // CTRL + O
                info.setActive(true);
                break;
            }

            case fileSave:
            {
                info.shortName = "Save";
                info.description = "Saves the current project to disk";
                info.flags = 0;
                info.addDefaultKeypress(115, ModifierKeys::commandModifier); // CTRL + S
                info.setActive(true);
                break;
            }

            case fileSaveAs:
            {
                info.shortName = "Save As...";
                info.description = "Saves the current project with a new file name";
                info.flags = 0;
                info.addDefaultKeypress(115, ModifierKeys::commandModifier | ModifierKeys::shiftModifier); // CTRL + SHIFT + S
                info.setActive(true);
                break;
            }
                
            case fileExportPNG:
            {
                info.shortName = "Export As PNG...";
                info.description = "Saves a snapshot of the current diagram as a PNG file";
                info.flags = 0;
                info.setActive(true);
                break;
            }

#if JUCE_WIN32 || JUCE_LINUX
            case fileQuit:
            {
                info.shortName = "Quit";
                info.description = "Quit the application";
                info.flags = 0;
                info.addDefaultKeypress(81, ModifierKeys::commandModifier);  // CTRL + Q
                info.setActive(true);
                break;
            }
#endif

            case editDelete:
            {
                info.shortName = "Delete";
                info.description = "Delete the currently selected element";
                info.flags = 0;
                info.addDefaultKeypress(127, 0); // "Delete"
                info.addDefaultKeypress(8, 0); // "Backspace"
                info.setActive(true);
                break;
            }

            case projectNewUseCaseDiagram:
            {
                info.shortName = "Use Case Diagram";
                info.description = "Creates a new use-case diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(117, ModifierKeys::commandModifier | ModifierKeys::shiftModifier); // CTRL + SHIFT + U
                info.setActive(true);
                break;
            }

            case projectNewClassDiagram:
            {
                info.shortName = "Class Diagram";
                info.description = "Creates a new class diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(99, ModifierKeys::commandModifier | ModifierKeys::shiftModifier); // CTRL + SHIFT + C
                info.setActive(false);
                break;
            }

            case projectNewSequenceDiagram:
            {
                info.shortName = "Sequence Diagram";
                info.description = "Creates a new sequence diagram on the current project"; // CTRL + SHIFT + D
                info.flags = 0;
                info.addDefaultKeypress(100, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(false);
                break;
            }
            
            case diagramAddActor:
            {
                info.shortName = "Add Actor";
                info.description = "Add an actor figure to the current diagram";
                info.flags = 0;
                info.setActive(true);
                break;
            }
            
            case diagramAddUseCase:
            {
                info.shortName = "Add Use Case Bubble";
                info.description = "Add a use case bubble to the current diagram";
                info.flags = 0;
                info.setActive(true);
                break;
            }
            
            case diagramAddArrow:
            {
                info.shortName = "Add an Arrow";
                info.description = "Add an arrow to the current diagram";
                info.flags = 0;
                info.setActive(true);
                break;
            }

            case diagramAddLine:
            {
                info.shortName = "Add a Line";
                info.description = "Add a line to the current diagram";
                info.flags = 0;
                info.setActive(true);
                break;
            }

            case diagramToggleGrid:
            {
                info.shortName = "Toggle Grid";
                info.description = "Shows / hides the grid of the diagrams";
                info.flags = 0;
                info.setActive(true);
                break;
            }
            
            case helpAbout:
            {
                info.shortName = "About";
                info.description = "About Rem";
                info.flags = 0;
                info.setActive(true);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    bool CommandDelegate::perform(const InvocationInfo &info)
    {
        switch (info.commandID)
        {
            case fileNewProject:
            {
                NewProjectCreated* notification1 = new NewProjectCreated();
                NotificationCenter::defaultCenter().postNotification(notification1);
                NewDiagramAdded* notification2 = new NewDiagramAdded(NewDiagramAdded::UseCase);
                NotificationCenter::defaultCenter().postNotification(notification2);
                break;
            }

            case fileExportPNG:
            {
                ExportDiagramAsPNG* notification = new ExportDiagramAsPNG();
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case fileQuit:
            {
                JUCEApplication::getInstance()->systemRequestedQuit();
                break;
            }
            
            case fileOpen:
            {
                performFileOpen();
                break;
            }
            
            case fileSave:
            {
                if (_fileController.isProjectNew())
                {
                    performFileSaveAs();
                }
                else
                {
                    _fileController.saveProject();
                }
                break;
            }
            
            case fileSaveAs:
            {
                performFileSaveAs();
                break;
            }
            
            case editDelete:
            {
                DeleteSelectedFigures* notification = new DeleteSelectedFigures();
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case projectNewUseCaseDiagram:
            {
                NewDiagramAdded* notification = new NewDiagramAdded(NewDiagramAdded::UseCase);
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case diagramAddActor:
            {
                NewFigureAdded* notification = new NewFigureAdded(NewFigureAdded::Actor);
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case diagramAddUseCase:
            {
                NewFigureAdded* notification = new NewFigureAdded(NewFigureAdded::UseCase);
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case diagramAddArrow:
            {
                NewFigureAdded* notification = new NewFigureAdded(NewFigureAdded::Arrow);
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case diagramAddLine:
            {
                NewFigureAdded* notification = new NewFigureAdded(NewFigureAdded::Line);
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case diagramToggleGrid:
            {
                DiagramToggleGrid* notification = new DiagramToggleGrid();
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case helpAbout:
            {
                AlertWindow::showNativeDialogBox(String("Rem"), String("Rem Application\nCopyright (c) 2008 Adrian Kosmaczewski"), false);
                break;
            }

            default:
            {
                ApplicationCommandInfo appInfo(info.commandID);
                getCommandInfo(info.commandID, appInfo);
                return AlertWindow::showNativeDialogBox(appInfo.shortName, appInfo.description, false);
                break;
            }
        }
        return true;
    }
    
    void CommandDelegate::performFileSaveAs()
    {
        FileChooser fileChooser("Choose a file name for the project", File::getSpecialLocation(File::userDesktopDirectory), "*.rem", NATIVE_DIALOG);
        if (fileChooser.browseForFileToSave(true))
        {
            File file = fileChooser.getResult();
            if (file.exists())
            {
                file.deleteFile();
            }
            std::string fileName = std::string(file.getFullPathName().toUTF8());
            _fileController.saveProjectAs(fileName);
        }
    }

    void CommandDelegate::performFileOpen()
    {
        FileChooser fileChooser("Choose a file", File::getSpecialLocation(File::userDesktopDirectory), "*.rem", NATIVE_DIALOG);
        if (fileChooser.browseForFileToOpen(NULL))
        {
            File file = fileChooser.getResult();
            std::string fileName = std::string(file.getFullPathName().toUTF8());
            const bool ok = _fileController.openProject(fileName);
            if (ok)
            {
                ProjectFileOpened* notification = new ProjectFileOpened();
                NotificationCenter::defaultCenter().postNotification(notification);
            }
            else
            {
                AlertWindow::showNativeDialogBox(String("Error"), String("The file is not a valid Rem project file."), false);
            }
        }
    }
}
