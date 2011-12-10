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
  private:
    _M T*           m_list0;
    _M T*           m_list1;

  public:
    class Iterator: public std::iterator<std::forward_iterator_tag, T>
    {
      private:
        _T typename T::ConstIterator               ConstIterator;
        _T typename T::ConstIterator::value_type  value_type;

      private:
        ConstIterator        m_it;
        bool                 m_list: 1;
        RValidList<T>*       m_container;

      public:
        _M Vacuum        Iterator(RValidList<T>* container, ConstIterator it, bool list):
          m_it(it), m_list(list), m_container(container) { }
        _M Vacuum        ~Iterator() { }
        _M Iterator&     operator=(const Iterator& other)
          { m_it = other.m_it; m_list = other.m_list; return *this; }
        _M bool          operator==(const Iterator& other)
          { return m_it == other.m_it; }
        _M bool          operator!=(const Iterator& other)
          { return m_it != other.m_it; }
        _M Iterator&     operator++()
          {
            if (m_list == 1)
            {
              while (m_it != m_container->m_list1->end() && (*m_it)->isValid() == false);
              {
                m_it++;
              }
            } else if (m_it != m_container->m_list0->end()) {
              do
              {
                m_it++;
                if (m_it == m_container->m_list0->end() && m_container->m_list1 != NULL)
                {
                  m_list = 1;
                  m_it = m_container->m_list1->begin();
                  while (m_it != m_container->m_list1->end() && (*m_it)->isValid() == false)
                  {
                    m_it++;
                  }
                }
              } while (m_list == 0 && m_it != m_container->m_list0->end() && !(*m_it)->isValid());
            }
            return *this;
          }
        _M Iterator&     operator++(int)
          { Iterator old(*this); ++(*this); return old; }
        _M value_type    operator*()
          { return *m_it; }
        _M value_type*   operator->()
          { return &*(*this); }
    };

  public:
    _M Vacuum           RValidList(T* list0, T* list1):
      m_list0(list0), m_list1(list1) { }
    _M Vacuum           RValidList(T* list):
      m_list0(list) { } // GCC 4.7: RValidList(list, NULL) { }
    _M Vacuum           RValidList() { }
    _M Vacuum           ~RValidList() { }
    _M Iterator         begin()
      { return Iterator(this, m_list0->begin(), 0); }
    _M Iterator         end()
      { return (m_list1 == NULL ? Iterator(this, m_list0->end(), 0)
                                : Iterator(this, m_list1->end(), 1)); }
};

/**********************************************************************************************/


#endif // RVALIDLIST_HH
