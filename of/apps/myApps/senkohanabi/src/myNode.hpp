//
//  myNode.hpp
//  senkohanabi
//
//  Created by 佐藤優成 on 2020/08/22.
//

#ifndef myNode_hpp
#define myNode_hpp

#include <stdio.h>

#if (0)
#define MAX_NODE 16

template <class X_CLS>
class myNode {
    myNode<X_CLS> * parent ;
    myNode<X_CLS> * child[MAX_NODE] ;
    int child_cnt = 0;
public:
    X_CLS val;
    myNode();
    myNode(myNode<X_CLS> * parent);
    void setParent(myNode<X_CLS> * parent);
    void setChild(myNode<X_CLS> * child);
    myNode<X_CLS> * getParent();
    
    void clear();

    /* ~myNode(); */
};

#endif

#endif /* myNode_hpp */
