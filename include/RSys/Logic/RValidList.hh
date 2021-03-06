#ifndef RVALIDLIST_HH
#define RVALIDLIST_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/**********************************************************************************************/

/********************************************* RS *********************************************/
/*                                         RValidList                                         */
/**********************************************************************************************/
template <class T>
class RValidList
{
  public:
    _T typename T::Value          Value;

  private:
    _M T*             m_list0;
    _M T*             m_list1;

  public:
    class Iterator
    {
      private:
        _T typename T::ConstIterator              ConstIterator;

      private:
        ConstIterator        m_it;
        bool                 m_list: 1;
        RValidList<T>*       m_container;

      public:
        _M Vacuum          Iterator(RValidList<T>* container, ConstIterator it, bool list):
          m_it(it), m_list(list), m_container(container) { }
        _M Vacuum          ~Iterator() { }
        _M Iterator&       operator = (const Iterator& other)
        {
          m_it        = other.m_it;
          m_list      = other.m_list;
          m_container = other.m_container;
          return *this;
        }
        _M bool            operator == (const Iterator& other) const
          { return m_it == other.m_it; }
        _M bool            operator != (const Iterator& other) const
          { return m_it != other.m_it; }

        // sitas buvo neiskaitomas, tai perrasiau, kad makintu bent kiek sense
        _M Iterator&       operator ++ ()
        {
          if (m_list == 0)
          {
            for (++m_it; m_it != m_container->m_list0->end(); ++m_it)
              if ((*m_it)->isValid())
                return *this;

            if (m_container->m_list1)
            {
              m_list  = 1;
              m_it    = m_container->m_list1->begin();
            }
          }
          else
            ++m_it;

          if (m_list == 1)
          {
            for (; m_it != m_container->m_list1->end(); ++m_it)
              if ((*m_it)->isValid())
                return *this;
          }

          return *this;
        }

        _M Iterator        operator ++(int)
          { Iterator old(*this); ++(*this); return old; }
        _M Value           operator * () const
          { return *m_it; }
        _M Value*          operator -> () const
          { return &*m_it; }
    };

  public:
    _M Vacuum           RValidList(T* list0, T* list1):
      m_list0(list0), m_list1(list1) { }
    _M Vacuum           RValidList(T* list0):
      m_list0(list0), m_list1(NULL) { } // GCC 4.7: RValidList(list0, NULL) { }
    _M Vacuum           RValidList() { }
    _M Vacuum           ~RValidList() { }
    _M Iterator         begin()
    {
      Iterator it = (m_list0->isEmpty() && m_list1)
                    ? Iterator(this, m_list1->begin(), 1)
                    : Iterator(this, m_list0->begin(), 0);
      while (it != end() && (*it)->isValid() == false) it++;
      return it;
    }

    _M Iterator         end()
    { return   (m_list1)
             ? Iterator(this, m_list1->end(), 1)
             : Iterator(this, m_list0->end(), 0);
    }
};

/**********************************************************************************************/


#endif // RVALIDLIST_HH
