//
//  myNode.cpp
//  senkohanabi
//
//  Created by 佐藤優成 on 2020/08/22.
//

#include "myNode.hpp"

#if (0)

template <class X_CLS>
myNode<X_CLS>::myNode()
{
    
}

template <class X_CLS>
myNode<X_CLS>::myNode(myNode<X_CLS> * parent)
{
    this->parent = parent;
}

template <class X_CLS>
void myNode<X_CLS>::setParent(myNode<X_CLS> * parent)
{
    this->parent = parent;
}

template <class X_CLS>
myNode<X_CLS> * myNode<X_CLS>::getParent()
{
    return this->parent;
}

template <class X_CLS>
void myNode<X_CLS>::setChild(myNode<X_CLS> * child)
{
    this->child[child_cnt] = child;
    child_cnt++;
}

template <class X_CLS>
void myNode<X_CLS>::clear()
{
    this->parent = nullptr;
    for (int i = 0 ; i < child_cnt; i++)
    {
        this->child = nullptr;
    }
    child_cnt = 0;
}

/*
myNode::~myNode() {
    
}
 */
#endif

