//
//  HashMap.h
//  OS Project
//
//  Created by MAC on 28/04/2023.
//

#ifndef HashMap_h
#define HashMap_h

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std ;

//Task 2: To avoid collisions, implement the linear probing technique.
template<typename T>
class NodeBST
{
public:
    T data;
    NodeBST <T>*left;
    NodeBST <T>*right;
    
    NodeBST()  // Defauft-Construcotor
    {
        data = 0 ;
        left = nullptr ;
        right = nullptr ;
    }
    // Parameterized-Construcotor
    
    // Node Destructor
    ~NodeBST()
    {
        
        left = nullptr ;
        right = nullptr ;
    }
};

template <class X>
class NodeAVL {
public:
    int height;
    X data;
    NodeAVL <X>*left;
    NodeAVL <X>*right;
    
    NodeAVL()  // Defauft-Construcotor
    {
        data = 0 ;
        left = nullptr ;
        right = nullptr ;
        height = 0 ;
    }
    // Parameterized-Construcotor
    
    // Node Destructor
    ~NodeAVL()
    {
        height = 0 ;
        left = nullptr ;
        right = nullptr ;
    }
};


template <class D>
class NodeLL {
public:
    D data;
    int d ;
    NodeLL<D>* next;
    
    // Parameterised constructor with default argument
    NodeLL(D val = 0 , int d_ = 0)
    {
        data = val ;
        d = d_ ;
        next = nullptr ;
    }
    ~NodeLL()
    {
        data = 0 ;
        d = 0 ;
        next = nullptr ;
    }
    
};
template <class Z>
class LinkedList
{
    // Head pointer
    NodeLL<Z>* head;
    int size ;
    
public:
    // default constructor. Initializing head pointer
    LinkedList()
    {
        head = nullptr ;
        size = 0 ;
    }
    bool isEmpty()
    {
        if(head == nullptr)
            return true ;
        return false ;
    }
    // inserting elements (At start of the list)
    void insert(Z val , int d )
    {
        // make a new node
        NodeLL<Z>* new_node = new NodeLL<Z>(val,d);
        
        // If list is empty, make the new node, the head
        if (head == nullptr)
        {
            head = new_node;
        }
        // else, make the new_node the head and its next, the previous
        // head
        else
        {
            new_node->next = head;
            head = new_node;
        }
        size++ ;
    }
    
    // loop over the list. return true if element found
    bool search(Z val ,int &d, int &cc )
    {
        NodeLL<Z>* temp = head;
        while(temp != nullptr)
        {
            cc++;
            if (temp->data == val)
            {
                temp->d = d ;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    
    void Get_All_Data(Z* &arr ,int* &d, int &sizee )
    {
//        cout<<size;
        sizee = this->size ;
        arr = new Z[sizee];
        d = new int[sizee];
        NodeLL<Z>* temp = head;
        int i = 0 ;
        while(temp != nullptr)
        {
            arr[i] = temp->data ;
            d[i] = temp->d ;
            temp = temp->next;
            i++;
        }
        
    }
    bool Delete(Z val)
    {
        NodeLL<Z>* temp = head;
        // If the head is to be deleted
        if (temp != nullptr && temp->data == val)
        {
            head = temp->next;
            size--;
            delete temp;
        }
        // Else loop over the list and search for the node to delete
        else
        {
            NodeLL<Z>* curr = head;
            while(temp != nullptr && temp->data != val)
            {
                // When node is found, delete the NodeAVL and modify the pointers
                curr = temp;
                temp = temp->next;
            }
            // If values is not found in the linked list
            if(temp == nullptr)
                return false;
            
            curr->next = temp->next;
            size--;
            delete temp;
        }
        return true ;
    }
    
    string Print()
    {
        string ss;
        ss = "PageNo. | FrameNo.\n";
        cout<<"PageNo. | FrameNo."<<endl;
        NodeLL<Z>* temp = head;
        while(temp != nullptr)
        {
            ss = ss + to_string(temp->data) + " | " + to_string(temp->d) + "\n";
            cout << temp->data << " | "<<temp->d<<endl;
            temp = temp->next;
        }
        cout<<endl<<"---------------------"<<endl;
        cout << endl;
        return ss;
    }
};



template <class k>
struct HashItem
{
    long key;
    int d ;
    bool chaining;
    k* chain ;
    short status;
public:
    HashItem()
    {
        key = 0 ;
        status = 0 ;
        chaining = 0 ;
        d = 0 ;
        chain = nullptr ;
    }
    
   ~HashItem()
    {
        key = 0 ;
        status = 0 ;
        chaining = 0 ;
        d = 0 ;
//        if(chain != nullptr)
//            delete chain ;
        chain = nullptr ;
    }
    
    
    
};

template <class k>
class HashMap
{
protected:
    HashItem<k>* hashArray;
    int capacity;
    int currentElements;
    bool Chaining_Allowed;
    int collision;
    int compreq ;
    float getLoadFactor()
    {
        return ((float)currentElements/(float)capacity) ;
    }
    void doubleCapacity()
    {
        collision = 0;
        capacity = capacity + capacity + 7 ; // taking 7 as a prime number
        HashItem<k>* oldhashArray = hashArray ;
        hashArray = new HashItem<k>[capacity];
        currentElements = 0 ;
        for(int i = 0 ; i < capacity/2 ; i++)
        {
            if(oldhashArray[i].status == 2)
            {
                insert(oldhashArray[i].key,oldhashArray[i].d);
                if(oldhashArray[i].chaining == 1)
                {
                    int* p ;
                    int* d ;
                    int size ;
                    oldhashArray[i].chain->Get_All_Data(p,d,size);
                    for(int i = 0 ; i < size ; i++)
                        insert(p[i],d[i]);
                    delete [] p;
                    delete [] d;
                }
            }
            
        }
//        cout<<"Capacity : "<<capacity<<endl;
        delete []oldhashArray;
    }
    int Hash(long key,int size)
    {
        return key % size ;
    }
    int getNextCandidateIndex(long key, int i)  // Linear Probing
    {
        return Hash(key,capacity)+i ;
    }
    
public:
    HashMap( bool chaining )
    {
        Chaining_Allowed = chaining ;
        capacity = 20 ;
        currentElements = 0 ;
        collision = 0 ;
        compreq = 0 ;
        hashArray = new HashItem<k>[capacity] ;
    }
    HashMap(int const capacity_ , bool chaining )
    {
        Chaining_Allowed = chaining ;
        capacity = capacity_ ;
        currentElements = 0 ;
        collision = 0 ;
        compreq = 0 ;
        hashArray = new HashItem<k>[capacity] ;
    }
    int GetCollision()
    {
        return collision ;
    }
    int GetComparisions()
    {
        return compreq ;
    }
    void insert(long const key , int d )
    {
        
        int idx = Hash(key, capacity) ;
        if(hashArray[idx].status == 0)
        {
            
            hashArray[idx].key = key ;
            hashArray[idx].d = d ;
            hashArray[idx].status = 2 ;
            currentElements++;
            // cout<<" Load Factor : "<<getLoadFactor()<<endl;
        }
        else
        {
           
            if(Chaining_Allowed == 0)
            {
                int next = 0 ;
                for(int i = 1 ; i <= capacity ; i++)
                {
                    collision++;
                    next = getNextCandidateIndex(key, i);
                    if(next >= capacity )
                        next = next % capacity ;
                    
                    if(hashArray[next].status == 0)
                    {
                        hashArray[next].key = key ;
                        hashArray[idx].d = d ;
                        hashArray[next].status = 2 ;
                        currentElements++;
                        // cout<<" Load Factor : "<<getLoadFactor()<<endl;
                        break ;
                    }
                }
            }
            else
            {
                collision++;
                if(hashArray[idx].key != key)
                {
                    
                    if(hashArray[idx].chaining == 0 )
                    {
                        hashArray[idx].chaining = 1 ;
                        hashArray[idx].chain = new k();
                        hashArray[idx].chain->insert(key,d);
                    }
                    else
                        hashArray[idx].chain->insert(key,d);
                }
            }
        }
        if(getLoadFactor() >= 0.85)
        {
//            cout<<"Size Doubled "<<endl;
            doubleCapacity();
        }
        
    }
    bool deleteKey(long const key)
    {
        if(currentElements >= 0 )
        {
            
            int idx = Hash(key, capacity) ;
            if(hashArray[idx].status == 2 && hashArray[idx].key == key )
            {
                
                hashArray[idx].status = 1 ;
                currentElements--;
                //                cout<<"deleted at idx : "<<idx<< endl;
                return true ;
            }
            else
            {
                if(Chaining_Allowed == 0)
                {
                    int  next = 0 ;
                    for(int i = 1 ; i <= capacity ; i++)
                    {
                        next = getNextCandidateIndex(key, i);
                        if(next >= capacity )
                            next = next % capacity ;
                        
                        if(hashArray[next].status == 2 && hashArray[next].key == key)
                        {
                            
                            hashArray[next].status = 1 ;
                            currentElements--;
                            //                            cout<<"Deleted at idx : "<<next<< endl;
                            return true ;
                        }
                    }
                }
                else
                {
                    if(hashArray[idx].chaining == 1 )
                    {
                        bool flag = hashArray[idx].chain->Delete(key) ;
                        if(hashArray[idx].chain->isEmpty())
                        {
                            delete hashArray[idx].chain ;
                            hashArray[idx].chaining = 0 ;
                        }
                        return flag ;
                    }
                }
            }
            
        }
        return false ;
        
    }
    bool Search(long const key ,int &p)
    {
        int compcount = 0 ;
        if(currentElements >= 0 )
        {
            
            int idx = Hash(key, capacity) ;
            if( hashArray[idx].key == key )
            {
                if(hashArray[idx].status !=1)
                {
                    p = hashArray[idx].d ;
                    return true ;
                }
            }
            else
            {
                if(Chaining_Allowed == 0)
                {
                    int  next = 0 ;
                    for(int i = 1 ; i <= capacity ; i++)
                    {
                        compcount++;
                        next = getNextCandidateIndex(key, i);
                        if(next >= capacity )
                            next = next % capacity ;
                        
                        if( hashArray[next].key == key )
                            if(hashArray[next].status !=1)
                            {
                                p = hashArray[next].d ;
                                return true ;
                            }
                        
                    }
                    return false ;
                }
                else
                {
                    if(hashArray[idx].chaining == 1 )
                    {
                        bool flag = hashArray[idx].chain->search(key,p,compcount) ;
                        
                        return flag ;
                        
                    }
                }
            }
        }
        return 0 ;
    }
    string print()
    {
        string ss;
        ss = "Capacity : " + to_string(capacity) + '\n';
        cout<<"Capacity : "<<capacity<<endl;
        for(int i = 0 ; i < capacity ; i++)
        {
            if (hashArray[i].status == 2)
            {
                cout << "-> ( " << i << " ), key : " << hashArray[i].key << endl;
                ss = ss + " p = " + to_string(i) + " | f = " + to_string(hashArray[i].key) + "\n";
            }
            if(hashArray[i].chaining == 1)
            {
                cout<<"   ---->    Data Chained at Index : "<<i<<" : ";
                hashArray[i].chain->Print();
                cout<<endl;
            }
        }
        return ss;
    }
    ~HashMap()
    {
        if(hashArray!=nullptr)
            delete []hashArray ;
        cout<<endl<<" HashMap Deleted "<<endl;
        
    }
};


#endif /* HashMap_h */
