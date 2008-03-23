/*!
 * \file Property.h
 *
 * Contains the interface of the storage::Property class.
 * This code is adapted from page 51 of
 * Duffy, Daniel J.; "Financial Instrument Pricing Using C++",
 * 2004, John Wiley & Sons, ISBN 0-470-85509-6
 * (C) Datasim Education BV 2002-2004
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <string>

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
{
    /*!
     * \class Persistable
     *
     *  
     */
    template <class N = std::string, class V = double>
    class Property
    {
    public:
        Property();
        Property(const N&);
        Property(const N&, const V&);
        Property(const Property<N, V>&);
        Property<N, V>& operator = (const Property<N, V>&);
        virtual ~Property();
        
        virtual V operator()() const;
        virtual V getValue() const;
        virtual void operator()(const V&);
        virtual void setValue(const V&);

        virtual N getName() const;


        bool operator == (const Property<N, V>&);

    private:
        N name;
        V value;
    };

    template <class N, class V> 
    Property<N, V>::Property()
    {
        this->name = N();
        this->value = V();
    }

    template <class N, class V> 
    Property<N, V>::Property(const N& name)
    {
        this->name = name;
        this->value = V();
    }

    template <class N, class V> 
    Property<N, V>::Property(const N& name, const V& value)
    {
        this->name = name;
        this->value = value;
    }

    template <class N, class V> 
    Property<N, V>::Property(const Property<N, V>& source) 
    {
        this->name = source.name;
        this->value = source.value;
    }

    template <class N, class V> 
    Property<N, V>::~Property()
    {
    }

    template <class N, class V>  
    Property<N, V>& Property<N, V>::operator =(const Property<N, V>& source)
    {
        if (this == &source)
            return *this;

        this->name = source.name;
        this->value = source.value;

        return *this;
    }

    template <class N, class V> 
    V Property<N, V>::operator()() const
    {
        return this->value;
    }
    
    template <class N, class V> 
    V Property<N, V>::getValue() const
    {
        return this->value;
    }

    template <class N, class V>
    void Property<N, V>::operator()(const V& value)
    {
        this->value = value;
    }
    
    template <class N, class V>
    void Property<N, V>::setValue(const V& value)
    {
        this->value = value;
    }
    
    template <class N, class V> 
    N Property<N, V>::getName() const
    {
        return this->name;
    }

    template <class N, class V> 
    bool Property<N, V>:: operator == (const Property<N, V>& prop2)
    {
        if (this->name != prop2.name())
            return false;
        if (this->value != prop2.value)
            return false;
        return true;
    }
}

#endif /* PROPERTY_H_ */
