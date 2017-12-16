//
// Created by ulyanin on 14.10.17.
//

#ifndef INC_14_10_2017_LOCK_FREE_STACK_H
#define INC_14_10_2017_LOCK_FREE_STACK_H


#include <atomic>
#include <set>

//template <class T>
//class Node
//{
//public:
//    Node * next;
//    T item;
//};
//
//
//template <class T>
//class lock_free_stack
//{
//public:
//    void push(const T &data) {
//        Node<T> * new_node = new Node<T>(data);
//        while (!__sync_bool_compare_and_swap()
//    }
//};


template <class T>
class Node
{
public:
    T item;
    std::atomic<Node *> Next;
    Node(T value)
            : item(value)
            , Next(nullptr)
    { }

    Node()
            : item(T())
            , Next(nullptr)
    {}

    static Node<T> * getNext(Node<T> * node)
    {
        return node ? node->Next.load() : nullptr;
    }
};


template <class T>
class lock_free_stack
{
public:
    typedef Node<T> * NodePtr;
    lock_free_stack()
            : top_(nullptr)
    {}

    ~lock_free_stack()
    {
        for (NodePtr cur = top_.load(), tmp; cur != nullptr; cur = tmp) {
            tmp = cur->Next.load();
//            std::cout << "stack deleting " << cur->item << std::endl;
            delete cur;
        }
    }

    void push(T item) {
        NodePtr itemPtr = new Node<T>(item);
        push_(itemPtr);
    }

    bool pop(T& item) {
        NodePtr itemPtr;
        if (!pop_(itemPtr)) {
            return false;
        }
        item = itemPtr->item;
        delete itemPtr;
        return true;
    }

protected:
    void push_(NodePtr new_node)
    {
//        std::cout << "push" << std::endl;
        while (true) {
            NodePtr new_node_next = top_;
            new_node->Next.store(new_node_next);
            if (top_.compare_exchange_strong(new_node_next, new_node)) {
                return;
            }
        }
    }

    bool pop_(NodePtr &res_node)
    {
        NodePtr curr_top = top_;
        res_node = nullptr;
//        std::cout << "pop" << std::endl;
        while (true) {
            if (!curr_top) {
                return false;
            }
            if (top_.compare_exchange_strong(curr_top, curr_top->Next)) {
                res_node = curr_top;
                return true;
            }
        }
    }

protected:
    std::atomic<NodePtr> top_;
};

#endif //INC_14_10_2017_LOCK_FREE_STACK_H
