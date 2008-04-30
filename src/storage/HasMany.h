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
	template <class C, class P>
    class HasMany
    {
    public:
    
        typedef std::map<std::string, C*> InternalMap;

        /*!
         *  HasMany constructor.
         */
        HasMany();

        /*!
         *  HasMany virtual destructor.
         */
        virtual ~HasMany();

        const bool isEmpty() const;

        void addChild(C*);
        
        const int getChildrenCount() const;
        
        C* getChild(const std::string&);
        
        void removeChild(const std::string&);
		
		void removeAllChildren();
        
        void saveChildren();

    private:
        InternalMap _children;
    };

    /*!
     * HasMany<C, P> Constructor.
     */
	template <class C, class P>
    HasMany<C, P>::HasMany()
    : _children()
    {
    }
    
    /*!
     * HasMany<C, P> Virtual destructor.
     */
	template <class C, class P>
    HasMany<C, P>::~HasMany()
    {
        this->removeAllChildren();
    }
    
	template <class C, class P>
    const bool HasMany<C, P>::isEmpty() const
    {
        return _children.empty();
    }
    
	template <class C, class P>
    void HasMany<C, P>::addChild(C* child)
    {
        if (child)
        {
            _children[child->getName()] = child;
            
            // The logic behind the "dynamic_cast" below is brilliantly
            // explained here:
            // http://carcino.gen.nz/tech/cpp/multiple_inheritance_this.php
            // Also look at 
            // http://www.acm.org/crossroads/xrds3-1/ovp3-1.html
            // for a good explanation of the different C++ cast operators.

            // Basically, when using multiple inheritance, you must use 
            // the dynamic_cast operator to get the correct "this" pointer
            // value needed. And this also explains the need of a second
            // template class parameter, with the type of the parent.
            child->setParent(dynamic_cast<P*>(this));
        }
    }
    
	template <class C, class P>
    const int HasMany<C, P>::getChildrenCount() const
    {
        return _children.size();
    }
    
	template <class C, class P>
    C* HasMany<C, P>::getChild(const std::string& name)
    {
        return _children[name];
    }
    
	template <class C, class P>
    void HasMany<C, P>::removeChild(const std::string& name)
    {
        C* element = _children[name];
		if (element)
		{
			delete element;
			_children.erase(name);
		}
    }
	
	template <class C, class P>
	void HasMany<C, P>::removeAllChildren()
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
    
    template <class C, class P>
    void HasMany<C, P>::saveChildren()
    {
		typename InternalMap::iterator iter;
        for (iter = _children.begin(); iter != _children.end(); ++iter)
        {
            iter->second->save();
        }
    }
}

#endif /* HASMANY_H_ */
