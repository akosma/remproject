/*!
 * \file Toolbox.h
 *
 * Contains the interface of the ui::Toolbox class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/20/08
 */

#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <string>
#include <vector>

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class Toolbox
     *
     *  
     */
    class Toolbox
    {
    public:

        /*!
         *  Toolbox constructor.
         */
        Toolbox();

        /*!
         *  Toolbox virtual destructor.
         */
        virtual ~Toolbox();

    protected:

    private:
        std::string _param;
    };
}

#endif /* TOOLBOX_H_ */
