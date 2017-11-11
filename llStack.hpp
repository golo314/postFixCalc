/*
 Project: PostFix Notation
 File Name: llStack.h
 Created by Aleksandr Golovin on 10/30/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
 */

#include <stdio.h>
#include <stdexcept>

#ifndef llStack_h
#define llStack_h

template <class Type>
class LLStack
{
private:
    
    //Private Node Class
    class node
    {
    private:
        
        //Private members
        Type value;
        node * pNxt;
        
    public:
        
        //Default Constructor
        node() { pNxt = NULL;}
        
        //Overloaded constructor
        node(const Type & newItem)
        {
            value = newItem;
            pNxt = NULL;
        }
        
        //Sets pointer to next item
        void setNxt(node * nxt) { pNxt = nxt; }
        
        //Returns pointer to next item
        node * getNxt() const { return pNxt; }
        
        //Returns value
        Type & getVal() { return value; }
    };
    
    //pointer to top node
    node * pTop;
    
    //Private Function: Deletes all items on stack
    void deleteStack()
    {
        if (pTop)
        {
            //Loops through stack, deleting items
            while (!empty())
            {
                pop();
            }
            pTop = NULL;
        }
    }
    
public:
    
    //Default Constructor
    LLStack() { pTop = NULL;}
    
    //Copy Constructor uses overloaded assignment operator
    LLStack(const LLStack & rhs)
    {
        pTop = NULL;
        *this = rhs;
    }
    
    //Overloaded assignment operator
    LLStack<Type> & operator = (const LLStack<Type> & rhs)
    {
        //Checks to make sure stack isn't assigned to itself
        if (this != &rhs)
        {
            //Clears stack
            deleteStack();
            
            node* pRhs = rhs.pTop;
            node * curnt;
            
            //Traverses down stack coping nodes
            while (pRhs)
            {
                if (!pTop)
                {
                    curnt= pTop = new node(pRhs->getVal());
                }
                else
                {
                    node * temp = new node(pRhs->getVal());
                    curnt->setNxt(temp);
                    curnt = curnt->getNxt();
                }
                pRhs = pRhs->getNxt();
            }
        }
        return *this;
    }
    
    //Pushes items onto top of stack
    void push(const Type & newItem)
    {
        if (!pTop)
        {
            pTop = new node(newItem);
        }
        else
        {
            node * nwItm = new node(newItem);
            nwItm->setNxt(pTop);
            pTop = nwItm;
        }
    }
    
    //Removes top item from stack
    void pop()
    {
        if (pTop)
        {
            node * toDlt = pTop;
            pTop = toDlt->getNxt();
            delete toDlt;
        }
    }
    
    //Returns item on top of stack, throw expection if stack empty
    Type & top() const
    {
        if (pTop)
        {
            return (pTop->getVal());
        }
        else
        {
            throw std::logic_error("Stack is empty");
        }
    }
    
    //Returns bool to whether stack is empty
    bool empty() const
    {
        return (!pTop);
    }
    
    //Return num. elements in stack
    int size() const
    {
        int count = 0;
        node * travler = pTop;
        
        //Traverses down stack counting nodes
        while (travler)
        {
            count++;
            travler = travler->getNxt();
        }
        return count;
    }
    
    //Virtual destructor, calls deleteStack()
    virtual ~LLStack()
    {
        deleteStack();
    }
};

#endif /* llStack_h */



