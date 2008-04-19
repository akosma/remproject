/*!
 * \file UseCaseBubble.h
 *
 * Contains the interface of the ui::UseCaseBubble class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#ifndef USECASEBUBBLE_H_
#define USECASEBUBBLE_H_

#ifndef FIGURE_H_
#include "Figure.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class UseCaseBubble
     *
     *  
     */
    class UseCaseBubble : public Figure
    {
    public:

        /*!
         *  UseCaseBubble constructor.
         */
        UseCaseBubble(ContentComponent*);

        /*!
         *  UseCaseBubble virtual destructor.
         */
        virtual ~UseCaseBubble();

    protected:
        virtual void drawFigure(Path&);

    private:
        Label* _nameLabel;
    };
}

#endif /* USECASEBUBBLE_H_ */
