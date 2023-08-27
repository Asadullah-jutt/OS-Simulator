//
//  Page_Replacement.h
//  OS Project
//
//  Created by MAC on 28/04/2023.
//

#ifndef Page_Replacement_h
#define Page_Replacement_h

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <queue>
#include <cmath>

#include<string.h>



using namespace std;

class Frame{
public:
    int val ;
    bool use ;
    
public:
    Frame()
    {
        val = 0 ;
        use = 0 ;
    }
    Frame(int a , int b)
    {
        val = a ;
        use = b ;
    }
    void set()
    {
        use = 1 ;
    }

//    bool Replace
    
};


// Define the Node class
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
};

// Define the CircularLinkedList class
template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    // Constructor
    CircularLinkedList() {
        head = nullptr;
    }

    // Destructor
    ~CircularLinkedList() {
        if (head == nullptr) {
            return;
        }
        Node<T>* curr = head->next;
        while (curr != head) {
            Node<T>* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
    }

    // Insert a new node at the beginning of the list
    void insertAtBeginning(T data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            return;
        }
        Node<T>* curr = head;
        while (curr->next != head) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->next = head;
        head = newNode;
    }

    // Insert a new node at the end of the list
    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            return;
        }
        Node<T>* curr = head;
        while (curr->next != head) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->next = head;
    }
    
    bool Search(int d , Node<T>* &temp , bool headd = 0 )
    {
        if(headd == 1)
        {
            temp = head ;
        }
        Node<T>* p = temp ;
        Node<T>* curr = temp;
        do
        {
            if(curr->data.val == d)
            {
                curr->data.set();
                temp = p ;
                return true ;
            }
            curr = curr->next;
        }while (curr != temp);
        do
        {
            if(curr->data.val == -1)
            {
                curr->data.val = d ;
                curr->data.set();
                temp = curr->next ;
                return false ;
            }
            curr = curr->next;
        }while (curr != temp);

        do
        {
           
            if(curr->data.use == 1)
            {
                curr->data.use = 0 ;
            }
            else
            {
                curr->data.val = d ;
                curr->data.set() ;
                temp = curr->next ;
                return false ;
            }
            curr = curr->next;
        }while (1);
        
        return false ;

    }

    // Remove the first occurrence of a node with the given data
    void remove(T data) {
        if (head == nullptr) {
            return;
        }
        Node<T>* curr = head;
        Node<T>* prev = nullptr;
        while (curr->data != data && curr->next != head) {
            prev = curr;
            curr = curr->next;
        }
        if (curr->data != data) {
            return;
        }
        if (curr == head && curr->next == head) {
            head = nullptr;
            delete curr;
            return;
        }
        if (curr == head) {
            prev = head;
            while (prev->next != head) {
                prev = prev->next;
            }
            head = head->next;
            prev->next = head;
        }
        else if (curr->next == head) {
            prev->next = head;
        }
        else {
            prev->next = curr->next;
        }
        delete curr;
    }

    // Print the contents of the list
    string printList(Node<T>* ptr) {
        string pp;
        pp = "\n";
        Node<T>* curr = head;
        do {
            pp = pp + to_string (curr->data.val) + "  " + to_string(curr->data.use) ;
            if(ptr == curr)
                pp = pp + " < ";
            
            pp = pp + "\n";
            curr = curr->next;
            
        } while (curr != head);
        
        return pp;
    }
};

vector<string> Page_Replacement_with_Second_Chance(int frame_size , vector<int> ref_pages )
{
    CircularLinkedList<Frame> PageSlots;
    
    int page_faults = 0 ;
    Frame a(-1,0);
   

    for(int i = 0 ; i < frame_size ; i++)
    PageSlots.insertAtBeginning(a);

    vector<string> BB(ref_pages.size() + 1);



    
 
    
    
    Node <Frame>* ptr ;
    PageSlots.Search(ref_pages[0], ptr,1);
    page_faults++;
    BB[0] = BB[0] + "Iteration no : 1 , Page val : " + to_string(ref_pages[0]) + "\n\n";
   BB[0] = BB[0] + PageSlots.printList(ptr);
    BB[0] = BB[0] + "\n  --------- Page Fault Occured ----------\n ";
    bool flag = 0 ;
    for(int i = 1 ; i < ref_pages.size() ; i++)
    {
        BB[i] = "Iteration no : " + to_string(i + 1) + " , Page val : " + to_string(ref_pages[i]) + "\n\n";
        flag = 0 ;
        if(!PageSlots.Search(ref_pages[i], ptr))
        {
            flag = 1 ;
            page_faults++;
        }
        BB[i] = BB[i] + PageSlots.printList(ptr);

        if (flag == 1)
            BB[i] = BB[i] + "\n  --------- Page Fault Occured ----------\n\n";
        else
            BB[i] = BB[i] + "\n  --------- No Page Fault Occured ----------\n\n";

        
                    
    }
    int s = ref_pages.size();
    float prob = (float)page_faults / s;
    BB[s] = BB[s ] + "Total Page Faults : " + to_string(page_faults) + "\n";
    BB[s ] = BB[s ] + "Page Fault Probability : " + to_string(prob) + "\n";
    BB[s ] = BB[s ] + "Page Fault Percentage : " + to_string(prob * 100) + "%\n";

    
    cout<<"Total Page Faults : "<<page_faults<<endl;
    cout<<"Page Fault Probability : "<<prob<<endl;
    cout<<"Page Fault Percentage : "<<prob*100<<" % "<<endl;

    return BB;
    
}


#endif /* Page_Replacement_h */
//vector<int> ref_page{3,3,5,4,7,1,5,5,1,4,3,7,6,3,4,1};
//
//Page_Replacement_with_Second_Chance(4, ref_page);
//vector<int> ref_page{1,2,3,4,5,2,3,1,2,3};
//
//Page_Replacement_with_Second_Chance(3, ref_page);
