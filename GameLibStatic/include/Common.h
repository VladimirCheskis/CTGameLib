#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_STD(Class)\
  typedef std::shared_ptr<Class> Class##Ptr;\
  typedef std::weak_ptr<Class> Class##WeakPtr;\
  typedef std::vector< std::shared_ptr<Class> > Class##Vector;\
  typedef std::shared_ptr<const Class> Class##ConstPtr;\
  typedef std::vector< std::shared_ptr<const Class> > Class##ConstVector;\
  typedef std::vector< std::weak_ptr<Class> > Class##WeakVector;\
  typedef std::vector< std::weak_ptr<const Class> > Class##WeakConstVector;\

////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void removeDeleted(std::vector< std::weak_ptr<T> >& v)
{
    if (v.empty())
        return;
    for ( int i = int(v.size()) - 1; i >= 0; --i )
    {
        if (!v[i].lock())
        {
            v.erase(v.begin() + i);
        }
    }
}

#endif //COMMON_H
