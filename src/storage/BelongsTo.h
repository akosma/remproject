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
    template <class T>
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
        BelongsTo(const BelongsTo<T>&);
        BelongsTo<T>& operator=(const BelongsTo<T>&);
        
        void setParent(T*);
        T* getParent();
        std::string getParentColumn();
        
    private:
        T* _parent;
        std::string _parentColumn;
    };

    /*!
     * 
     */
    template <class T>
    BelongsTo<T>::BelongsTo()
    : _parent(0)
    , _parentColumn("")
    {
        std::stringstream name;
        name << T::getTableName();
        name << "_id";
        _parentColumn = name.str();
    }
    
    template <class T>
    BelongsTo<T>::~BelongsTo()
    {
    }
    
    template <class T>
    BelongsTo<T>::BelongsTo(const BelongsTo<T>& source)
    : _parent(source._parent)
    , _parentColumn(source._parentColumn)
    {
    }
    
    template <class T>
    BelongsTo<T>& BelongsTo<T>::operator=(const BelongsTo<T>& source)
    {
        if (this != &source)
        {
            this->_parent = source._parent;
            this->_parentColumn = source._parentColumn;
        }

        return *this;
    }
    
    template <class T>
    void BelongsTo<T>::setParent(T* parent)
    {
        _parent = parent;
    }
    
    template <class T>
    T* BelongsTo<T>::getParent()
    {
        return _parent;
    }
    
    template <class T>
    std::string BelongsTo<T>::getParentColumn()
    {
        return _parentColumn;
    }
}

#endif /* BELONGSTO_H_ */
