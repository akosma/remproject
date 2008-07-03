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

#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif

#ifndef COMMANDDELEGATE_H_
#define COMMANDDELEGATE_H_

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
            fileNewUseCaseDiagram = 0x2001,
            fileNewClassDiagram = 0x2002,
            fileNewSequenceDiagram = 0x2003,
            fileOpen = 0x2004,
            fileClose = 0x2005,
            fileSave = 0x2006,
            fileSaveAs = 0x2007,
            fileQuit = StandardApplicationCommandIDs::quit,
            editUndo = 0x2008,
            editCut = 0x2009,
            editCopy = 0x2010,
            editPaste = 0x2011,
            editDelete = 0x2012
        };
    };
}

#endif /* COMMANDDELEGATE_H_ */
