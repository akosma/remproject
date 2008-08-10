/*!
 * \file ActiveWindowStatusChanged.cpp
 *
 * Contains the implementation of the notifications::ActiveWindowStatusChanged class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#include "ActiveWindowStatusChanged.h"

namespace notifications
{
    ActiveWindowStatusChanged::ActiveWindowStatusChanged(const bool status)
    : Notification()
    , _status(status)
    {
    }
    
    ActiveWindowStatusChanged::~ActiveWindowStatusChanged()
    {
    }
    
    const bool ActiveWindowStatusChanged::getStatus() const
    {
        return _status;
    }
}
