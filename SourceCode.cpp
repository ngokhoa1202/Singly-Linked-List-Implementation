#include <iostream>
#include <string>

using namespace std;

class IntSLinkedList {
public:
    class Node; // Forward declaration

private:
    Node* head;
    Node* tail;
    int count;

    void add_recursively_helper(Node* pPrevious, int& index, int& element, int i = 0) {
        if (i+1 == index) {
            Node* pNew = new Node(element);
            pNew->next = pPrevious->next;
            pPrevious->next = pNew;
            this->count++;
            return;
        }
        add_recursively_helper(pPrevious->next, index, element, i+1);
    }

    int get_recursively_helper(Node* pCurrent, int& index, int i = 0) {
        if (i == index) 
            return pCurrent->data;
        return get_recursively_helper(pCurrent->next, index, i+1);
    }

    void set_recursively_helper(Node* pCurrent, int& index, int& element, int i = 0) {
        if (i == index) {
            pCurrent->data = element;
            return;
        }
        set_recursively_helper(pCurrent->next, index, element, i+1);
    }

    int indexOf_recursively_helper(Node* pCurrent, int& item, int i = 0) {
        //base case
        if (pCurrent == nullptr) return -1;
        if (pCurrent->data == item) return i; 

        // or 
        /* if (pCurrent->data == item) {
            return 0;
        }
        int posFountIndex = indexOf_recursively_helper(pCurrent->next, item);
        return (posFountIndex != -1) ? posFountIndex + 1 : -1; */

        //general case
        return indexOf_recursively_helper(pCurrent->next, item, i+1);
    } 

    bool contains_recursively_helper(Node* pCurrent, int& item, int i = 0) {
        if (pCurrent == nullptr) return false;
        if (pCurrent->data == item) return true;
        return contains_recursively_helper(pCurrent->next, item, i+1);
    }
    
    int removeAt_recursively_helper(Node* pPrevious, int& index, int i = 0) {
        if (i+1 == index) {
            Node* pTemp = pPrevious->next;
            pPrevious->next = pPrevious->next->next;
            int result = pTemp->data;
            delete pTemp;

            if (pPrevious->next == nullptr) {
                this->tail = pPrevious;
            }
            this->count--;

            return result;
        }
        return removeAt_recursively_helper(pPrevious->next, index, i+1);

    } 

    bool removeItem_recursively_helper(Node* pPrevious, int& item) {
        if (pPrevious == this->tail) return false;
        if (pPrevious->next->data == item) {
            delete pPrevious->next;
            pPrevious->next = pPrevious->next->next;
            this->count--;
            if (pPrevious->next == nullptr) {
                this->tail = pPrevious;
            }
            return true;
        }
        return removeItem_recursively_helper(pPrevious->next, item);
    }

    void clear_helper_recursively(Node* pCurrent) {
        if (pCurrent == nullptr) {
            this->head = nullptr;
            this->tail = nullptr;
            this->count = 0;
            return;
        }
        Node* pNext = pCurrent->next;
        delete pCurrent;
        clear_helper_recursively(pNext);
    }

    void checkIndex(int index, bool isAddFunction = false) {
        if (isAddFunction) {
            if (index < 0 || index > this->count) 
                throw std::out_of_range("Index is out of range");
        } else {
            if (index < 0 || index >= this->count) {
                throw std::out_of_range("Index is out of range");
            }
        }
    }

public:
    IntSLinkedList() : head(NULL), tail(NULL), count(0) {};
    void add(int element) {
        Node* pNew = new Node(element);
        if (this->head == nullptr) {
            this->head = this->tail = pNew;
        } else {
            this->tail->next= pNew;
            this->tail = pNew;
        }
        this->count++;
    }

    void add(int index, int element) {
        this->checkIndex(index, true);
        if (index == this->count) {
          this->add(element);
        } else if (index == 0) { //add at Head
            Node* pNew = new Node(element);
            (*pNew).next = this->head;
            this->head = pNew;
            this->count++;
        } else {
          add_recursively_helper(this->head, index, element);
        }
    }

    int removeAt(int index) {
        this->checkIndex(index);
        int result;

        if (index == 0) { 
            Node* pTemp = this->head;
            result = (*(*this).head).data;
            this->head = this->head->next;
            delete pTemp;
            if (this->head == nullptr) {
                this->tail = nullptr;
            }
            this->count--;
        } 
        
        else {
            result = removeAt_recursively_helper(this->head, index);
        }
        this->count--;
        return result;
    }

    bool removeItem(int item) {
        if (item == this->head->data) {
            Node* pTemp = this->head;
            this->head = this->head->next;
            delete pTemp;
            if (this->head == nullptr) {
                this->tail = nullptr;
            }
            this->count--;
            return true;
        } else {
            return removeItem_recursively_helper(this->head, item);
        }
        return false;
    }

    bool empty() {
        return (this->count == 0);
    }

    int size() {
        return this->count;
    }
    
    int get(int index) {
        this->checkIndex(index);
        return get_recursively_helper(this->head, index);
    }

    void set(int index, int element) {
        this->checkIndex(index);
        set_recursively_helper(this->head, index, element);
    }

    int indexOf(int item) {
        return indexOf_recursively_helper(this->head, item);
    }

    bool contains(int item) {
        //return contains_recursively_helper(this->head, item);
        return (indexOf(item) != -1);
    }
    
    void clear() {
        clear_helper_recursively(this->head);
    }

    std::string toString();
public:
    class Node {
    public:
        int data;
        Node* next;

    public:
        Node() : next(NULL) {};
        Node(int data) : 
            data(data), next(NULL) {};
    };
};

int main() {
    IntSLinkedList list;
    int values[]   = {10, 15, 2,  6,  4,  2,  40,  8};
    int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
    for (int idx = 0; idx < 8; idx++){
        list.add(index[idx], values[idx]);
    }

    bool removed = list.removeItem(2);
    cout << removed << endl;
    cout << list.toString();
    return EXIT_SUCCESS;
}

std::string IntSLinkedList::toString() {
    std::string result ="The linked list is: ";
    Node* pCurrent = (*this).head;
    while (pCurrent != nullptr) {
        result += to_string((*pCurrent).data) + " ";
        pCurrent = (*pCurrent).next;
    }
    result += '\n';
    return result;
}
        
