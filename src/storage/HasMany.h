/*!
 * \file HasMany.h
 *
 * Contains the interface of the storage::HasMany class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef HASMANY_H_
#define HASMANY_H_

#include <string>
#include <map>

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
{
    /*!
     * \class HasMany
     *
     *  
     */
	template <class T>
    class HasMany
    {
    public:
    
        typedef std::map<std::string, T*> InternalMap;

        /*!
         *  HasMany constructor.
         */
        HasMany();

        /*!
         *  HasMany virtual destructor.
         */
        virtual ~HasMany();

        const bool isEmpty() const;

        void addChild(T*);
        
        const int getChildrenCount() const;
        
        T* getChild(const std::string&);
        
        void removeChild(const std::string&);
		
		void removeAllChildren();

    private:
        InternalMap _children;
    };

    /*!
     * HasMany<T> Constructor.
     */
	template <typename T>
    HasMany<T>::HasMany()
    : _children()
    {
    }
    
    /*!
     * HasMany<T> Virtual destructor.
     */
	template <typename T>
    HasMany<T>::~HasMany()
    {
        this->removeAllChildren();
    }
    
	template <typename T>
    const bool HasMany<T>::isEmpty() const
    {
        return _children.empty();
    }
    
	template <typename T>
    void HasMany<T>::addChild(T* child)
    {
        if (child)
        {
            _children[child->getName()] = child;
        }
    }
    
	template <typename T>
    const int HasMany<T>::getChildrenCount() const
    {
        return _children.size();
    }
    
	template <typename T>
    T* HasMany<T>::getChild(const std::string& name)
    {
        return _children[name];
    }
    
	template <typename T>
    void HasMany<T>::removeChild(const std::string& name)
    {
        T* element = _children[name];
		if (element)
		{
			delete element;
			_children.erase(name);
		}
    }
	
	template <typename T>
	void HasMany<T>::removeAllChildren()
	{
        // For the explanation of the "typename" keyword below, see
        // http://gcc.gnu.org/ml/gcc-help/2008-01/msg00137.html and
        // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18

		typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            delete (*iter).second;
        }

		_children.clear();
	}

}

#endif /* HASMANY_H_ */
