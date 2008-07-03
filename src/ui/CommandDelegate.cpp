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

#include "CommandDelegate.h"

namespace ui
{
    CommandDelegate::CommandDelegate()
    : ApplicationCommandTarget()
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
            fileNewUseCaseDiagram,
            fileNewClassDiagram,
            fileNewSequenceDiagram,
            fileOpen,
            fileClose,
            fileSave,
            fileSaveAs,
#if JUCE_WIN32 || JUCE_LINUX
            fileQuit,
#endif
            editUndo,
            editCut,
            editCopy,
            editPaste,
            editDelete
        };
        commands.addArray(ids, numElementsInArray(ids));
    }

    void CommandDelegate::getCommandInfo(const CommandID command, ApplicationCommandInfo& info)
    {
        switch (command)
        {
            case fileNewProject:
                info.shortName = "New Project";
                info.description = "Creates a new project, closing the current one if needed";
                info.flags = 0;
                info.addDefaultKeypress(110, ModifierKeys::commandModifier);
                info.setActive(true);
                break;

            case fileNewUseCaseDiagram:
                info.shortName = "Use Case Diagram";
                info.description = "Creates a new use-case diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(117, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(true);
                break;

            case fileNewClassDiagram:
                info.shortName = "Class Diagram";
                info.description = "Creates a new class diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(99, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(true);
                break;

            case fileNewSequenceDiagram:
                info.shortName = "Sequence Diagram";
                info.description = "Creates a new sequence diagram on the current project";
                info.flags = 0;
                info.addDefaultKeypress(100, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(true);
                break;

            case fileOpen:
                info.shortName = "Open...";
                info.description = "Opens a project in disk";
                info.flags = 0;
                info.addDefaultKeypress(111, ModifierKeys::commandModifier);
                info.setActive(true);
                break;

            case fileClose:
                info.shortName = "Close";
                info.description = "Closes the current project";
                info.flags = 0;
                info.addDefaultKeypress(119, ModifierKeys::commandModifier);
                info.setActive(true);
                break;

            case fileSave:
                info.shortName = "Save...";
                info.description = "Saves the current project to disk";
                info.flags = 0;
                info.addDefaultKeypress(115, ModifierKeys::commandModifier);
                info.setActive(true);
                break;

            case fileSaveAs:
                info.shortName = "Save As...";
                info.description = "Saves the current project with a new file name";
                info.flags = 0;
                info.addDefaultKeypress(115, ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
                info.setActive(true);
                break;

#if JUCE_WIN32 || JUCE_LINUX
            case fileQuit:
                info.shortName = "Quit";
                info.description = "Quit the application";
                info.flags = 0;
                info.addDefaultKeypress(81, ModifierKeys::commandModifier);
                info.setActive(true);
                break;
#endif
            default:
                break;
        }
    }

    bool CommandDelegate::perform(const InvocationInfo &info)
    {
        ApplicationCommandInfo appInfo(info.commandID);
        getCommandInfo(info.commandID, appInfo);
        return AlertWindow::showNativeDialogBox(appInfo.shortName, appInfo.description, false);
    }
}
