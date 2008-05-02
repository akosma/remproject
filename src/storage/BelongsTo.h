/*!
 * \file BelongsTo.h
 *
 * Contains the interface of the storage::BelongsTo class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/28/08
 */

#ifndef BELONGSTO_H_
#define BELONGSTO_H_

#include <sstream>

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
{
    /*!
     * \class BelongsTo
     *
     *  
     */
    template <class P>
    class BelongsTo
    {
    public:

        /*!
         *  BelongsTo constructor.
         */
        BelongsTo();

        /*!
         *  BelongsTo virtual destructor.
         */
        virtual ~BelongsTo();
        BelongsTo(const BelongsTo<P>&);
        BelongsTo<P>& operator=(const BelongsTo<P>&);
        
        void setParent(P*);
        P* getParent() const;
        const storage::ID getParentId() const;
        const std::string& getParentColumn() const;
        
    private:
        P* _parent;
        std::string _parentColumn;
    };

    /*!
     * 
     */
    template <class P>
    BelongsTo<P>::BelongsTo()
    : _parent(0)
    , _parentColumn("")
    {
        std::stringstream name;
        name << P::getTableName();
        name << "_id";
        _parentColumn = name.str();
    }
    
    template <class P>
    BelongsTo<P>::~BelongsTo()
    {
    }
    
    template <class P>
    BelongsTo<P>::BelongsTo(const BelongsTo<P>& rhs)
    : _parent(0)
    , _parentColumn("")
    {
    }
    
    template <class P>
    BelongsTo<P>& BelongsTo<P>::operator=(const BelongsTo<P>& rhs)
    {
        return *this;
    }
    
    template <class P>
    void BelongsTo<P>::setParent(P* parent)
    {
        _parent = parent;
    }
    
    template <class P>
    P* BelongsTo<P>::getParent() const
    {
        return _parent;
    }
    
    template <class P>
    const storage::ID BelongsTo<P>::getParentId() const
    {
        if (_parent)
        {
            return _parent->getId();
        }
        else
        {
            return storage::DEFAULT_ID;
        }
    }
    
    template <class P>
    const std::string& BelongsTo<P>::getParentColumn() const
    {
        return _parentColumn;
    }
}

#endif /* BELONGSTO_H_ */
