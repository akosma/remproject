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
        P* getParent();
        std::string getParentColumn();
        
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
    BelongsTo<P>::BelongsTo(const BelongsTo<P>& source)
    : _parent(source._parent)
    , _parentColumn(source._parentColumn)
    {
    }
    
    template <class P>
    BelongsTo<P>& BelongsTo<P>::operator=(const BelongsTo<P>& source)
    {
        if (this != &source)
        {
            this->_parent = source._parent;
            this->_parentColumn = source._parentColumn;
        }

        return *this;
    }
    
    template <class P>
    void BelongsTo<P>::setParent(P* parent)
    {
        _parent = parent;
    }
    
    template <class P>
    P* BelongsTo<P>::getParent()
    {
        return _parent;
    }
    
    template <class P>
    std::string BelongsTo<P>::getParentColumn()
    {
        return _parentColumn;
    }
}

#endif /* BELONGSTO_H_ */
