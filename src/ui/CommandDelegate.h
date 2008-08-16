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
    /*!
     * \class CommandDelegate
     *
     *  
     */
    class CommandDelegate : public ApplicationCommandTarget, 
                            public Singleton<CommandDelegate>
    {
    public:

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

            diagramAddActor = 0x2040,
            diagramAddUseCase = 0x2041,
            diagramAddArrow = 0x2042,
            diagramAddLine = 0x2043,
            diagramToggleGrid = 0x2044,
            
            helpAbout = 0x2060
        };
    
    private:
        //! Private constructor.
        CommandDelegate();

        //! Allow the Singleton template class to access the private constructor.
        friend CommandDelegate& Singleton<CommandDelegate>::get();
    
    private:
        void performFileSaveAs();
        
    private:
        FileController& _fileController;
    };
}

#endif /* COMMANDDELEGATE_H_ */
