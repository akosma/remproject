/*!
 * \file Controller.h
 *
 * Contains the interface of the rem::Controller class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef rem_Controller
#define rem_Controller

#include <string>
#include <vector>

/*!
 * \namespace rem
 * Insert a description for the namespace here
 */
namespace rem
{
    /*!
     * \class Controller
     *
     *  
     */
    class Controller
    {
    public:

        /*!
         *  Controller constructor.
         */
        Controller();

        /*!
         *  Controller virtual destructor.
         */
        virtual ~Controller();

    protected:

    private:
        std::string _param;
    };
}

#endif /* rem_Controller */
