/*!
 * \file Container.h
 *
 * Contains the interface of the MetaModel::Container class.
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

#include <string>
#include <map>

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * \class Container "$URL$"
     *
     *  
     */
	template<class T>
    class Container
    {
    public:

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
        std::map<std::string, T*> _elements;
    };

    /*!
     * Container<T> Constructor.
     */
	template <typename T>
    Container<T>::Container()
    : _elements(std::map<std::string, T*>())
    {
    }
    
    /*!
     * Container<T> Virtual destructor.
     */
	template <typename T>
    Container<T>::~Container<T>()
    {
		_elements.clear();
    }
    
	template <typename T>
    const bool Container<T>::empty() const
    {
        return _elements.empty();
    }
    
	template <typename T>
    void Container<T>::addElement(T* element)
    {
        _elements[element->getName()] = element;
    }
    
	template <typename T>
    const int Container<T>::getCount() const
    {
        return _elements.size();
    }
    
	template <typename T>
    T* Container<T>::getElement(const std::string& name)
    {
        return _elements[name];
    }
    
	template <typename T>
    void Container<T>::removeElement(const std::string& name)
    {
        T* element = _elements[name];
		if (element)
		{
			delete element;
			_elements.erase(name);
		}
    }
	
	template <typename T>
	void Container<T>::removeAllElements()
	{
		// TODO: add pointer deletion here for all the elements in the map!
		_elements.clear();
	}

}

#endif /* CONTAINER_H_ */
