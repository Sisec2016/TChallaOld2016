#pragma once

#include <vector>
#include <list>
#include <deque>

template<class T> void SafeDelete(T* &p)
{
	if (NULL != p)
	{
		delete p;
		p = NULL;
	}
}
template< class T, int nsize > 
void SafeDelete( T* (&data)[nsize])
{
    for (int i = 0; i < nsize; i++)
    {
        SafeDelete(data[i]);
    }
}
template<class T, class _Ax, template<typename, typename> class container> 
void SafeDelete(container<T*,_Ax>& sco)
{
	for (typename container<T*,_Ax>::iterator it = sco.begin(); it != sco.end(); it++)
	{
		SafeDelete(*it);
	}
    sco.erase(sco.begin(), sco.end());
}