//
//  ResourceAllocation.h
//  OS Project
//
//  Created by MAC on 24/04/2023.
//

#ifndef ResourceAllocation_h
#define ResourceAllocation_h

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <queue>
#include <string>
using namespace std ;

class Resourses{
    vector<int> max ;
    vector<int> allocated ;
    bool finished = 0 ;
    friend bool Safe_State(string &ss,Resourses* arr ,int no_of_processes, vector<int> &avaiable , vector<int> &safe_seq);
    
    friend bool Resourses_req(vector<string> &ss , Resourses* arr ,int no_of_processes,int req_idx , vector<int> req , vector<int> &avaiable , vector<int> &safe_seq);

public:
    Resourses()
    {
        max.clear() ;
        allocated.clear() ;
        finished = 0 ;
    }
    Resourses( vector<int> max_ , vector<int> allocated_)
    {
        for(int i = 0 ; i < max_.size() ; i++)
        {
            max.push_back( max_[i]) ;
            allocated.push_back( allocated_[i] ) ;
        }
        finished = 0 ;
    }
    void input(int s)
    {
        int in ;

        cout<<"MAX : "<<endl;
        for(int i = 0 ; i < s ; i++)
        {
            cout<<"For "<<char(65+i) <<" : ";
            cin >> in ;
            max.push_back(in) ;
        }
        cout<<"Allocated : "<<endl;
        for(int i = 0 ; i < s ; i++)
        {
            cout<<"For "<<char(65+i) <<" : ";
            cin >> in ;
            if(in > max[i] || in < 0)
            {
                cout<<"Invalid Input "<<endl;
                max.clear();
                allocated.clear();
                break;
            }
            allocated.push_back(in) ;
        }

    }
    void Set_Max_Allocated(vector<int> a , vector<int> b)
    {
        max.clear() ;
        allocated.clear() ;
        max = a ;
        allocated = b ;
    }
    int need(int i)
    {
        return max[i] - allocated[i] ;
    }
    bool operator == (vector<int> &available)
    {
        if(finished == 1)
            return false ;
        
        for(int i = 0 ; i < this->max.size(); i++)
        {
            if(available[i] < this->need(i))
                return false ;
        }
        return true ;
    }
    string display()
    {
        string ss;
        for(int i = 0 ; i < this->max.size(); i++)
            ss = ss + to_string( max[i]) + " ";
        
        ss = ss + "  |  ";
        
        for(int i = 0 ; i < this->max.size(); i++)
            ss = ss + to_string(allocated[i]) + " ";
        
        ss = ss + "  |  ";
        
        for(int i = 0 ; i < this->max.size(); i++)
            ss = ss + to_string( need(i)) + " ";
        
        ss = ss + '\n';
        return ss;


    }
    Resourses & operator - (vector<int> &available)
    {
        for(int i = 0 ; i < this->max.size(); i++)
        {
            available[i] = available[i] + allocated[i] ;
            allocated[i] = 0 ;
        }
        finished = 1 ;
        return *this ;
    }
};

bool Resourses_req(vector<string> &ss , Resourses* arr ,int no_of_processes,int req_idx , vector<int> req , vector<int> &avaiable , vector<int> &safe_seq)
{
    ss.push_back(" P  |   MAX   | ALLOCATED |  NEED  | \n");
    
    for (int i = 0; i < no_of_processes; i++)
        ss[0] = ss[0] + "P" + to_string(i) + "  |  " + arr[i].display();
    
    for(int i = 0 ; i < req.size() ; i++)
        if(req[i] > arr[req_idx].need(i))
        {
            ss.push_back("Request is Less then Need.... \n First Check Failed");
            return false ;
        }
    ss.push_back("Request is Greater then or Equal to Need.... \n First Check Passed \n");
    
    for(int i = 0 ; i < req.size() ; i++)
        if(req[i] > avaiable[i])
        {
            ss.push_back("Request is Less then Available.... \n Second Check Failed");
            return false ;
        }
    ss.push_back("Request is Greater then Available.... \n Second Check Passed \n");

    string l;
    l = "Available Before : ";
    for (int i = 0; i < req.size(); i++)
        l = l + to_string(avaiable[i]) + " ";
    l = l + "\n";
    
    for(int i = 0 ; i < req.size() ; i++)
        avaiable[i] = avaiable[i] - req[i] ;
    ss.push_back(l);
    l = "Available After : ";
    for (int i = 0; i < req.size(); i++)
        l = l + to_string(avaiable[i]) + " ";
    l = l + "\n";
    ss.push_back(l);
    for(int i = 0 ; i < req.size() ; i++)
        arr[req_idx].allocated[i] += req[i] ;
//    cout<<"Done";
    
//    for(int i = 0 ; i < no_of_processes ; i++)
//    arr[i].display();

    string aa;
    bool a=  Safe_State(aa, arr, no_of_processes, avaiable, safe_seq);
    if (a == 1)
    {
        ss.push_back("Request Granted to P" + to_string(req_idx) + "\n Safe Sequence : " + aa + " \n");
    }
    else
        ss.push_back("Request Can't be Granted to P" + to_string(req_idx));
    return a;
    
}

bool Safe_State(string &ss ,Resourses* arr ,int no_of_processes, vector<int> &avaiable , vector<int> &safe_seq)
{
    
    bool flag = 0 ;
    do
    {
        flag = 0 ;
        for(int i = 0 ; i < no_of_processes ; i++)
        {
            if(arr[i] == avaiable)
            {
                flag = 1 ;
                arr[i] = arr[i] - avaiable ;
//                cout<<endl;
//                for(int i = 0 ; i < avaiable.size() ; i++)
//                    cout<<avaiable[i]<<" , ";
//                cout<<endl;
                safe_seq.push_back(i);
            }
        }
        if(flag == 0)
        {
            string aa = " DeadLock ";
            ss = aa;
            for(int i = 0 ; i < no_of_processes ; i++)
                if(arr[i].finished == 0)
                    return false ;
            
            aa = "< ";
            for (int i = 0; i < no_of_processes; i++)
                aa = aa + "P" + to_string(safe_seq[i]) + ",";
            aa = aa + "> \n NO DEADLOCK";
            ss = ss + aa;
            return true ;
        }
    }while(1);
    return true ;
}


#endif /* ResourceAllocation_h */
//    Resourses arr[5];
////    for(int i = 0 ; i < 5 ; i++)
////    {
////        arr[i].input(3);
////    }
//
//
//
//    arr[0].Set_Max_Allocated({7,5,3}, {0,1,0});
//    arr[1].Set_Max_Allocated({3,2,2}, {2,0,0});
//    arr[2].Set_Max_Allocated({9,0,2}, {3,0,2});
//    arr[3].Set_Max_Allocated({2,2,2}, {2,1,1});
//    arr[4].Set_Max_Allocated({4,3,3}, {0,0,2});
////
////    for(int i = 0 ; i < 5 ; i++)
////    arr[i].display();
//
//
//    vector<int> available = {3,3,2} ;
//    vector<int> seq ;
//    Resourses_req(arr, 5, 0, {0,2,0}, available, seq) ;
//
//
////    Safe_State(arr, 5, available,seq);
////    cout<<endl;
//    for(int i = 0 ; i < seq.size() ; i++)
//        cout<<"P"<<seq[i]<<" , ";
    
//    Process_t a ;
//    Process_t b ;
//    cout<<a.pid<<endl;
//    cout<<b.pid<<endl;

//Resourses arr[5];
//        for(int i = 0 ; i < 5 ; i++)
//        {
//            arr[i].input(3);
//        }


//                                max      allocated
//arr[0].Set_Max_Allocated({2,5,1}, {0,1,0});
//arr[1].Set_Max_Allocated({3,1,1}, {2,0,0});
//arr[2].Set_Max_Allocated({3,0,2}, {1,0,2});
//arr[3].Set_Max_Allocated({2,4,3}, {2,1,0});
//arr[4].Set_Max_Allocated({2,3,1}, {0,0,2});
//
//    for(int i = 0 ; i < 5 ; i++)
//    arr[i].display();


//vector<int> available = {1,1,2} ;
//vector<int> seq ;
//        Resourses_req(arr, 5, 0, {0,2,0}, available, seq) ;

//
//if(Safe_State(arr, 5, available,seq))
//    cout<<"Safe Sequence"<<endl;
//else
//cout<<"No Safe Sequence"<<endl;
////    cout<<endl;
//for(int i = 0 ; i < seq.size() ; i++)
//    cout<<"P"<<seq[i]<<" , ";
//
//cout<<endl;
