/*************************************************************************
	> File Name: linklist.h
	> Author: 
	> Mail: 
	> Created Time: 2020年06月06日 星期六 09时31分39秒
 ************************************************************************/

#ifndef _LINKLIST_H
#define _LINKLIST_H


#define offset(T, name) ((long long)(&(((T *)(0))->name)))
#define Head(p, T, name) ((T *)(((char *)p) - offset(T, name)))

struct LinkNode {
    struct LinkNode *next;
};


#endif
