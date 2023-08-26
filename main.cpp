#include <iostream>
#include <mutex>
using namespace std;

struct Node
{
    int _value;
    Node* _next;
    mutex* _node_mutex;

    Node(int value, Node* next = nullptr) : _value(value), _next(next)
    {};
};

class FineGrainedQueue
{
    Node* head;
    mutex* queue_mutex;
public:
    void insertIntoMiddle(int value, int pos);
};

int main()
{

    return 0;
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* prev, * cur;

    Node* _newNode = new Node(value);



    prev = this->head;
    cur = this->head->_next;

    int index = 0;


    while (cur != nullptr && index < pos)
    {
        Node* old_prev = prev;
        prev = cur;
        cur = cur->_next;
        index++;
    }

    lock_guard<mutex> prevLock(*prev->_node_mutex);

    if (cur == nullptr)
    {
        prev->_next = _newNode;
    }
    else
    {
        lock_guard<mutex> curLock(*cur->_node_mutex);

        _newNode->_next = cur;
        prev->_next = _newNode;
    }
    
}