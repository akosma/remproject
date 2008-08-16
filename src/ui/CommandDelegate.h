/*!
 * \file CommandDelegate.h
 *
 * Contains the interface of the ui::CommandDelegate class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/3/08
 */

#ifndef COMMANDDELEGATE_H_
#define COMMANDDELEGATE_H_

#include "PlatformDefinitions.h"

namespace controllers
{
    class FileController;
}
using controllers::FileController;

namespace ui
{
    /*!
     * \class CommandDelegate
     *
     *  
     */
    class CommandDelegate : public ApplicationCommandTarget
    {
    public:

        /*!
         *  CommandDelegate constructor.
         */
        CommandDelegate();

        /*!
         *  CommandDelegate virtual destructor.
         */
        virtual ~CommandDelegate();
        
        virtual ApplicationCommandTarget* getNextCommandTarget();
        virtual void getAllCommands(Array<CommandID>&);
        virtual void getCommandInfo(const CommandID, ApplicationCommandInfo&);
        virtual bool perform(const InvocationInfo&);
        
        enum CommandIDs
        {
            fileNewProject = 0x2000,
            fileOpen = 0x2001,
            fileClose = 0x2002,
            fileSave = 0x2003,
            fileSaveAs = 0x2004,
            fileExportPNG = 0x2005,
            fileQuit = StandardApplicationCommandIDs::quit,

            editUndo = 0x2020,
            editCut = 0x2021,
            editCopy = 0x2022,
            editPaste = 0x2023,
            editDelete = 0x2024,

            projectNewUseCaseDiagram = 0x2030,
            projectNewClassDiagram = 0x2031,
            projectNewSequenceDiagram = 0x2032,

            diagramToggleGrid = 0x2040,
            
            helpAbout = 0x2060
        };
        
    private:
        void performFileSaveAs();
        
    private:
        FileController& _fileController;
    };
}

#endif /* COMMANDDELEGATE_H_ */
