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

#ifndef NEWUSECASEDIAGRAMADDED_H_
#include "../notifications/NewUseCaseDiagramAdded.h"
#endif

#ifndef FILECONTROLLER_H_
#include "../controllers/FileController.h"
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
using notifications::NewUseCaseDiagramAdded;

namespace ui
{
    CommandDelegate::CommandDelegate()
    : ApplicationCommandTarget()
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
            fileClose,
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
            
            diagramToggleGrid
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
                info.addDefaultKeypress(110, ModifierKeys::commandModifier);
                info.setActive(false);
                break;
            }

            case fileOpen:
            {
                info.shortName = "Open...";
                info.description = "Opens a project in disk";
                info.flags = 0;
                info.addDefaultKeypress(111, ModifierKeys::commandModifier);
                info.setActive(false);
                break;
            }

            case fileClose:
            {
                info.shortName = "Close";
                info.description = "Closes the current project";
                info.flags = 0;
                info.addDefaultKeypress(119, ModifierKeys::commandModifier);
                info.setActive(false);
                break;
            }

            case fileSave:
            {
                info.shortName = "Save...";
                info.description = "Saves the current project to disk";
                info.flags = 0;
                info.addDefaultKeypress(115, ModifierKeys::commandModifier);
                info.setActive(true);
                break;
            }

            case fileSaveAs:
            {
                info.shortName = "Save As...";
                info.description = "Saves the current project with a new file name";
                info.flags = 0;
                info.addDefaultKeypress(115, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
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
                info.addDefaultKeypress(81, ModifierKeys::commandModifier);
                info.setActive(true);
                break;
            }
#endif

            case projectNewUseCaseDiagram:
            {
                info.shortName = "Use Case Diagram";
                info.description = "Creates a new use-case diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(117, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(true);
                break;
            }

            case projectNewClassDiagram:
            {
                info.shortName = "Class Diagram";
                info.description = "Creates a new class diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(99, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(false);
                break;
            }

            case projectNewSequenceDiagram:
            {
                info.shortName = "Sequence Diagram";
                info.description = "Creates a new sequence diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(100, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(false);
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
            case fileExportPNG:
            {
                ExportDiagramAsPNG* notification = new ExportDiagramAsPNG();
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case diagramToggleGrid:
            {
                DiagramToggleGrid* notification = new DiagramToggleGrid();
                NotificationCenter::defaultCenter().postNotification(notification);
                break;
            }
            
            case fileQuit:
            {
                JUCEApplication::getInstance()->systemRequestedQuit();
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
            
            case projectNewUseCaseDiagram:
            {
                NewUseCaseDiagramAdded* notification = new NewUseCaseDiagramAdded();
                NotificationCenter::defaultCenter().postNotification(notification);
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
}
