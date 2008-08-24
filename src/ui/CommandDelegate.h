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

//! Contains the interface of the ui::CommandDelegate class.
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

#ifndef SINGLETON_H_
#include "../utility/Singleton.h"
#endif

namespace controllers
{
    class FileController;
}
using controllers::FileController;
using utility::Singleton;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! Main target for command invocations of the application.
    /*!
     * \class CommandDelegate
     *
     * Represents the main target for command invocations of the application.
     * The Window instance has a reference to this singleton class, and uses
     * it to forward all commands, which are executed from here.
     */
    class CommandDelegate : public ApplicationCommandTarget, 
                            public Singleton<CommandDelegate>
    {
    public:

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~CommandDelegate();
        
        //! Returns the next ApplicationCommandTarget instance in the invocation chain.
        /*!
         * Returns the next ApplicationCommandTarget instance in the invocation chain.
         * In this case, it returns NULL, since this class is the only command target.
         *
         * \return A pointer to an ApplicationCommandTarget instance.
         */
        virtual ApplicationCommandTarget* getNextCommandTarget();
        
        //! Returns all the commands supported by the application.
        /*!
         * Returns all the commands supported by the application.
         * This information is used to know which menu items should be displayed.
         * 
         * \param commands A reference to an array, which is filled with commands.
         */
        virtual void getAllCommands(Array<CommandID>&);
        
        //! Provides information about a given command.
        /*!
         * For any given command, it provides information such as title, description,
         * modifier keys and other details.
         * 
         * \param command The command whose information is required.
         * \param info A reference to a structure to be filled with information.
         */
        virtual void getCommandInfo(const CommandID, ApplicationCommandInfo&);
        
        //! Executes a command.
        /*!
         * Executes a command.
         *
         * \param info A reference to an InvocationInfo instance.
         */
        virtual bool perform(const InvocationInfo&);
        
        //! Unique IDs for each command that can be performed in the application.
        /*!
         * Unique IDs for each command that can be performed in the application.
         */
        enum CommandIDs
        {
            //! File / New Project
            fileNewProject = 0x2000,
            
            //! File / Open
            fileOpen = 0x2001,
            
            //! File / Close
            fileClose = 0x2002,
            
            //! File / Save
            fileSave = 0x2003,
            
            //! File / Save As...
            fileSaveAs = 0x2004,
            
            //! File / Export As PNG...
            fileExportPNG = 0x2005,
            
            //! File / Quit
            fileQuit = StandardApplicationCommandIDs::quit,

            //! Edit / Undo
            editUndo = 0x2020,
            
            //! Edit / Cut
            editCut = 0x2021,
            
            //! Edit / Copy
            editCopy = 0x2022,
            
            //! Edit / Paste
            editPaste = 0x2023,
            
            //! Edit / Delete
            editDelete = 0x2024,

            //! Project / New Use Case Diagram
            projectNewUseCaseDiagram = 0x2030,

            //! Project / New Class Diagram
            projectNewClassDiagram = 0x2031,

            //! Project / New Sequence Diagram
            projectNewSequenceDiagram = 0x2032,

            //! Diagram / Add Actor
            diagramAddActor = 0x2040,

            //! Diagram / Add Use Case
            diagramAddUseCase = 0x2041,

            //! Diagram / Add Arrow
            diagramAddArrow = 0x2042,

            //! Diagram / Add Line
            diagramAddLine = 0x2043,

            //! Diagram / Toggle Grid
            diagramToggleGrid = 0x2044,
            
            //! Help / About
            helpAbout = 0x2060
        };
    
    private:
        //! Private constructor.
        CommandDelegate();

        //! Allow the Singleton template class to access the private constructor.
        friend CommandDelegate& Singleton<CommandDelegate>::get();

        //! Performs the tasks required to save the project in a new file
        void performFileSaveAs();
        
        //! Prompts the user to open a project stored in a file.
        void performFileOpen();
        
    private:
        //! Reference to the singleton controllers::FileController class.
        FileController& _fileController;
    };
}

#endif /* COMMANDDELEGATE_H_ */
