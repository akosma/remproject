/*!
 * \file Container.h
 *
 * Contains the interface of the metamodel::Container class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <Poco/SharedPtr.h>
#include <string>
#include <map>

using Poco::SharedPtr;

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * \class Container
     *
     *  
     */
	template <class T>
    class Container
    {
    public:
    
        typedef std::map<std::string, SharedPtr<T>*> InternalMap;

        /*!
         *  Container constructor.
         */
        Container();

        /*!
         *  Container virtual destructor.
         */
        virtual ~Container();

        const bool empty() const;

        void addElement(T*);
        
        const int getCount() const;
        
        T* getElement(const std::string&);
        
        void removeElement(const std::string&);
		
		void removeAllElements();

    private:
        InternalMap _elements;
    };

    /*!
     * Container<T> Constructor.
     */
	template <typename T>
    Container<T>::Container()
    : _elements(InternalMap())
    {
    }
    
    /*!
     * Container<T> Virtual destructor.
     */
	template <typename T>
    Container<T>::~Container()
    {
        this->removeAllElements();
    }
    
	template <typename T>
    const bool Container<T>::empty() const
    {
        return _elements.empty();
    }
    
	template <typename T>
    void Container<T>::addElement(T* element)
    {
        if (element)
        {
            SharedPtr<T>* ptr = new SharedPtr<T>(element);
            _elements[element->getName()] = ptr;
        }
    }
    
	template <typename T>
    const int Container<T>::getCount() const
    {
        return _elements.size();
    }
    
	template <typename T>
    T* Container<T>::getElement(const std::string& name)
    {
        SharedPtr<T>* el = _elements[name];
        if (el)
        {
            return el->get();
        }
        else
        {
            return NULL;
        }
    }
    
	template <typename T>
    void Container<T>::removeElement(const std::string& name)
    {
        SharedPtr<T>* element = _elements[name];
		if (element)
		{
			delete element;
			_elements.erase(name);
		}
    }
	
	template <typename T>
	void Container<T>::removeAllElements()
	{
        // For the explanation of the "typename" keyword below, see
        // http://gcc.gnu.org/ml/gcc-help/2008-01/msg00137.html and
        // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18

		typename InternalMap::iterator iter;
        for (iter = _elements.begin(); iter != _elements.end(); ++iter)
        {
            delete (*iter).second;
        }

		_elements.clear();
	}

}

#endif /* CONTAINER_H_ */
