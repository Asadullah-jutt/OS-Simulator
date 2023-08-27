//
//  CPU.h
//  OS Project
//
//  Created by MAC on 25/04/2023.
//

#ifndef CPU_h
#define CPU_h

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "Minheap.h"
#include <queue>

using namespace std;


bool checka(vector<int> arr)
{
    for(int i = 0 ; i < arr.size() ; i++)
    {
        if(arr[i] != 0)
            return false ;
    }
    return true ;
}

class Process_t
{
public:
    int pid ;
    int pirority ;
    int arival_time ;
    int brust_time ;
    int type ;
 //    static int a ;
    

    Process_t()
    {
        brust_time = 0 ;
        arival_time = 0 ;
        pid = 0 ;
        pirority = 0 ;
//        a++ ;
        type = -1 ;
    }
    Process_t(int pid_ , int _Atime , int Btime , int pir , int typ )
    {
        pid = pid_ ;
        arival_time = _Atime ;
        brust_time = Btime ;
        pirority = pir ;
        type = typ ;
//        a++ ;
    }
    void print()
    { 
        cout<<pid<<"  |  "<<pirority<<"  |  "<<arival_time<<"  |  "<<brust_time <<endl;
    }
//    Process_t(Process_t &copy)
//    {
//        brust_time = copy.brust_time ;
//        arival_time = copy.arival_time ;
//        pid = copy.pid ;
//        pirority = pirority ;
//        a++ ;
//    }
    ~Process_t()
    {
        brust_time = 0 ;
        arival_time = 0 ;
        pid = 0 ;
        pirority = 0 ;
        type = 0;
//        a--;
    }
//    Process_t & operator = (Process_t a)
//    {
//        brust_time = a.brust_time ;
//        arival_time = a.arival_time ;
//        pid = a.pid ;
//        pirority = a.pirority ;
//        type = a.type ;
//        return *this ;
//    }

    Process_t & operator - (int a)
    {
        this->brust_time -= a ;
        return *this ;
    }

};
//int Process_t ::  a = 1 ;
void remove_val(MinHeap<Process_t> &a , int val)
{
    queue<Process_t> tt ;
//    cout<<a.size()<<" 66"<<endl;
    while(a.isEmpty() == 0)
    {
//        cout<<a.size()<<" 00"<<endl;

        if(a.getpid() == val)
        {
            a.extractMin();
            break;
        }
        tt.push(a.extractMin());
    }
    
    while(!tt.empty())
    {
        a.insertKey(tt.front().arival_time, tt.front());
        tt.pop();
    }
//    cout<<a.size()<<" 66"<<endl;
}


//void Multi_Level_Feedback_Queue( Process_t* arr , int size , int RR_stime )
//{
//    
//}
//
void plusplus_minusminus(vector<pair<int,int>> & vec  , int idx  , Process_t &pro)
{
    if(vec[idx].second == 1)
    {
        vec[idx].first++ ;
        

        if(vec[idx].first == 10)
        {
            pro.type++ ;
            cout<<"Process "<<pro.pid<<" Demoted "<<endl;
        }
        else if(vec[idx].first == 20)
        {
            pro.type++ ;
            cout<<"Process "<<pro.pid<<" Demoted "<<endl;
        }
    }
    else if(vec[idx].second == 2)
    {
        vec[idx].first-- ;

        if(vec[idx].first == 10)
        {
            cout<<"Process "<<pro.pid<<" Promoted "<<endl;
            pro.type-- ;
        }
        else if(vec[idx].first == 20)
        {
            cout<<"Process "<<pro.pid<<" Demoted "<<endl;
            pro.type++ ;
        }
    }
    else if(vec[idx].second == 3)
    {
        vec[idx].first-- ;

        if(vec[idx].first == 20)
        {
            cout<<"Process "<<pro.pid<<" Promoted "<<endl;
            pro.type-- ;
        }
        else if(vec[idx].first == 10)
        {
            cout<<"Process "<<pro.pid<<" Promoted "<<endl;
            pro.type-- ;
        }
    }
}

string Multi_Level_Feedback_Queue( Process_t* arr , int size , int RR_stime)
{
    string s;
    s = "ProcessID | Arrival Time | Burst Time \n\n";
    for (int i = 0; i < size; i++)
        s = s + "          P" + to_string(arr[i].pid) + "             |               " + to_string(arr[i].arival_time) + "           |        " + to_string(arr[i].brust_time) + "\n";
    s = s + "\n\n";
    vector<pair<int,int>> pirority(size) ;
    MinHeap<Process_t> Queue(size) ;
    vector<int> waiting_time(size,0) ;
    vector<int> completion_time(size,0) ;
    vector<int> turn_time(size,0) ;
    vector<int> seq;
//    0-30
    MinHeap<Process_t> S1(size) , S2(size) , S3(size) ;
    for(int i = 0 ; i < size ; i++)
    {
        Queue.insertKey(arr[i].arival_time, arr[i]) ;
        if(arr[i].type == 1)
        {
            S1.insertKey(arr[i].arival_time, arr[i]) ;
            pirority[arr[i].pid].first = 5 ;
            pirority[arr[i].pid].second = 1 ;
        }
        else if(arr[i].type == 2)
        {
            S2.insertKey(arr[i].arival_time, arr[i]) ;
            pirority[arr[i].pid].first = 15 ;
            pirority[arr[i].pid].second = 1 ;

        }
        else if(arr[i].type == 3)
        {
            S3.insertKey(arr[i].arival_time, arr[i]) ;
            pirority[arr[i].pid].first = 25 ;
            pirority[arr[i].pid].second = 1 ;
        }
    }
    
    MinHeap<Process_t> Queue_temp(size) ;
    Process_t f = Queue.extractMin() , end;
    
    bool inflag = 0 ;
    int time = 0 ;
    
    Queue_temp.insertKey(f.arival_time, f);
    while(1)
    {
        cout<<"time : "<<time<<endl;
//        cout<<Queue.isEmpty()<<" Queue.isEmpty() "<<endl;
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() == f.arival_time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(temp.arival_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }
        if(Queue_temp.isEmpty())
        {
            cout<<Queue.isEmpty()<<" Queue.isEmpty()"<<endl;
            if(Queue.isEmpty())
                break;
            else
            {
                inflag = 0 ;
                if(Queue.isEmpty() != 1)
                {
                    while(inflag == 0)
                    {
                        if(Queue.isEmpty() != 1)
                        {
                            if(Queue.getMinA() >= end.arival_time)
                            {
                                Process_t temp = Queue.extractMin();
                                Queue_temp.insertKey(-temp.brust_time, temp);
                            }
                            else
                                inflag = 1 ;
                        }
                        else
                            inflag = 1 ;
                    }
                }
                if(Queue_temp.getMinA() > time )
                    time = Queue_temp.getMinA();
            }
        }
        cout<<Queue_temp.size()<<endl;
        if(Queue_temp.size()!=1)
        {
//            cout<<"ttt"<<endl;
            queue<Process_t> innerQueue[3];
            Process_t temp ;
            while(!Queue_temp.isEmpty())
            {
                temp = Queue_temp.extractMin() ;
                
                innerQueue[temp.type-1].push(temp);
            }
            
            if(!innerQueue[0].empty())
            {
                
                MinHeap<Process_t> INN(innerQueue[0].size());
                
                while(!innerQueue[0].empty())
                {
                    INN.insertKey(innerQueue[0].front().arival_time ,innerQueue[0].front() );
                    innerQueue[0].pop();
                }
                while(INN.isEmpty()==0)
                {
                    innerQueue[0].push(INN.extractMin());

                }
                
                vector<int> stemp ;
                while(!innerQueue[0].empty())
                {
                    end = innerQueue[0].front() ;
                    cout<<end.pid<<" Demoted "<<endl;
                    innerQueue[0].pop();
                    end.type++ ;
                    
                    int temm = end.brust_time*0.5 ;
                    time = time +  temm ;
                    end.brust_time = end.brust_time - temm ;
                    turn_time[end.pid] = turn_time[end.pid] + time - end.arival_time ;

                    innerQueue[1].push(end) ;
                    stemp.push_back(end.pid);
                }
                
                for(int i = 0 ; i < stemp.size() ; i++)
                {
                    remove_val(S1, stemp[i]) ;
                }

                while(!innerQueue[1].empty())
                {
                    Process_t a = innerQueue[1].front();
                    plusplus_minusminus(pirority, a.pid, a);
                    Queue_temp.insertKey(innerQueue[1].front().arival_time ,a );
                    innerQueue[1].pop();
                }
                
                while(!innerQueue[2].empty())
                {
                    Process_t a = innerQueue[2].front();
                    plusplus_minusminus(pirority, a.pid, a);
                    Queue_temp.insertKey(innerQueue[2].front().arival_time ,a );
                    innerQueue[2].pop();
                }


                

            }
            else if(!innerQueue[1].empty())
            {
                MinHeap<Process_t> INN(innerQueue[1].size());
                
                while(!innerQueue[1].empty())
                {
                    INN.insertKey(innerQueue[1].front().brust_time ,innerQueue[1].front() );
                    innerQueue[1].pop();
                }
                while(INN.isEmpty()==0)
                {
                    innerQueue[1].push(INN.extractMin());

                }
               
 
                end = innerQueue[1].front() ;
                

                int L ;
                bool flagin = 0 ;
                while(1)
                {
                    flagin = 0 ;
                    L = S1.getMinA() ;
                    
                    S2.extractMin();
                    int LS = S2.getMinA() ;
                    if(LS != -1)
                    {
                        cout<<"LS"<<LS<<endl;
                        if(LS < L || L == -1)
                        {
                            flagin = 1 ;
                            L = LS ;
                        }
                    }
                    if(L >=time || L == -1)
                        break;
                    
                }
                
                cout<<"L : "<<L<<endl;
                cout<<flagin<<endl;
                if(L == -1)
                {
                    while(!innerQueue[1].empty())
                    {
                        end = innerQueue[1].front();
                        cout<<end.pid<<" Demoted"<<endl;
                        innerQueue[1].pop();
                        end.type++ ;
                        int temm = end.brust_time*0.3 ;
                        time = time +  temm ;
                        turn_time[end.pid] =  time - end.arival_time ;
                        waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                        end.brust_time = end.brust_time - temm ;
                        innerQueue[2].push(end) ;
//                        remove_val(S2, end.pid) ;
                        
                    }
                }
                else if(flagin == 0)
                {
                    while(!innerQueue[1].empty())
                    {
                        end = innerQueue[1].front() ;
                        if(time + end.brust_time > L)
                        {
//                            cout<<end.pid<<" Endedee"<<endl;
                            innerQueue[1].pop();
                            end.type++ ;
                            int temm = end.brust_time*0.3 ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                            time = time + temm ;
                            end.brust_time = end.brust_time - temm ;
                            innerQueue[2].push(end) ;

                            remove_val(S2, end.pid) ;
                            break;
                        }
                        else
                        {
//                            cout<<end.pid<<" Endedee"<<endl;
                            innerQueue[1].pop();
                            end.type++ ;
                            int temm = end.brust_time*0.3 ;
                            time = time +  temm ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                            end.brust_time = end.brust_time - temm ;
                            innerQueue[2].push(end) ;
                            remove_val(S2, end.pid) ;
                            
                        }
                    }
                }
                else if(flagin == 1)
                {
                    end = innerQueue[1].front() ;
                    end.print();
                    while(!innerQueue[1].empty())
                    {
                        if(time + end.brust_time > L)
                        {
                            int ttm = L - time  ;
                            cout<<ttm<<endl;
        
                            end.brust_time = end.brust_time - ttm;
                            cout<<time<<"tttt"<<endl;
                            time = time + ttm ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = waiting_time[end.pid] + time - ttm ;
                            cout<<"innnn"<<time;
                            if(end.brust_time > S2.getB())
                            {
                                cout<<end.pid<<" runned for "<<ttm<<"s"<<endl;
                                innerQueue[1].pop() ;
                                innerQueue[1].push(end) ;
                                end = innerQueue[1].front() ;
                            }
                            S2.extractMin() ;
                            L = S2.getMinA() ;
                            if(L == -1)
                            {
//                                innerQueue[2].push(end) ;
                                break;
                            }
                        }
                        else
                        {
                            cout<<end.pid<<" Endedee"<<endl;
                            innerQueue[1].pop();
                            end.type++ ;
                            int temm = end.brust_time*0.3 ;
                            time = time +  temm ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                            end.brust_time = end.brust_time - temm ;
                            innerQueue[2].push(end) ;
                            remove_val(S2, end.pid) ;

                            S2.extractMin() ;
                            L = S2.getMinA() ;
                            if(L == -1)
                                break;
                        }
                    }
                }
                while(!innerQueue[1].empty())
                {
                    Process_t a = innerQueue[1].front();
                    plusplus_minusminus(pirority, a.pid, a);

                    Queue_temp.insertKey(innerQueue[1].front().arival_time ,a );
                    innerQueue[1].pop();
                }
                while(!innerQueue[2].empty())
                {
                    Process_t a = innerQueue[2].front();
                    plusplus_minusminus(pirority, a.pid, a);

                    Queue_temp.insertKey(innerQueue[2].front().arival_time ,a );
                    innerQueue[2].pop();
                }
            }
            else if(!innerQueue[2].empty())
            {
                if(innerQueue[2].size() == 1)
                {
                    if(S1.size() == 0)
                    {
                        end = innerQueue[2].front() ;
                        cout<<end.pid<<" Endedf"<<endl;
                        innerQueue[2].pop();
                        time = time +  end.brust_time ;
                        completion_time[end.pid] = time  ;
                        turn_time[end.pid] = turn_time[end.pid] +time - end.arival_time ;
                        waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time ;

                        seq.push_back(end.pid);
                        remove_val(S3, end.pid) ;
                    }
                    else
                    {
                        int L ;
                        bool flagin = 0 ;
                        while(1)
                        {
                            flagin = 0 ;
                            L = S1.getMinA() ;
                            
                            if( L == -1 )
                               L = S2.getMinA() ;
                            else
                            {
                               int LL = S2.getMinA();
                               if ( LL != -1)
                                   L = min(L,LL) ;
                            }
                            cout<<L<<"L"<<endl;
                            S3.extractMin();
                            int LS = S3.getMinA() ;
                            if(LS != -1)
                            {
                                cout<<"LS"<<LS<<endl;
                                if(LS < L || L == -1)
                                {
                                    flagin = 1 ;
                                    L = LS ;
                                }
                            }
                            if(L >=time || L == -1)
                                break;
                            
                        }
                        

                        if(end.brust_time <= L)
                        {
                            cout<<end.pid<<" Ended"<<endl;
                            innerQueue[2].pop();
                            time = time +  end.brust_time ;
                            completion_time[end.pid] = time  ;
                            turn_time[end.pid] =turn_time[end.pid] + time - end.arival_time ;
                            waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time ;
                            seq.push_back(end.pid);
                            remove_val(S3, end.pid) ;
                        }
                        else
                        {
                            cout<<end.pid<<" Runned for "<<L<<"s and Stoped "<<endl;
                            end.brust_time = end.brust_time - L ;
//                            Queue_temp.insertKey(end.arival_time, end);
                            time = time + L ;
                            innerQueue[2].pop();
                            innerQueue[2].push(end);

                        }
                        
                    }
                }
                else
                {
                
                    if(S1.size() == 0 && S2.size() == innerQueue[2].size())
                    {
//                        cout<<"++"<<endl;
                        while(!innerQueue[2].empty())
                        {
                            end = innerQueue[2].front() ;

                            if(innerQueue[2].size()== 1)
                            {
                              cout<<end.pid<<" Endedss&&"<<endl;
                              innerQueue[2].pop();
                              time = time +  end.brust_time ;
                              completion_time[end.pid] = time  ;
                              turn_time[end.pid] =turn_time[end.pid] + time - end.arival_time ;
                                waiting_time[end.pid] = waiting_time[end.pid] + time -end.brust_time ;

                              seq.push_back(end.pid);
                              remove_val(S2, end.pid) ;
                              break;
                            }
                            
                            if(end.brust_time > RR_stime)
                            {
                                end = innerQueue[2].front() ;

                                end.brust_time = end.brust_time - RR_stime;
                                cout<<end.pid<<" Runnedss for "<<RR_stime<<"s and Stoped "<<endl;

                             
                                time = time + RR_stime ;
                                innerQueue[2].pop();
                                innerQueue[2].push(end) ;
                            }
                            else
                            {
                                cout<<end.pid<<" Endedss%%"<<endl;
                                innerQueue[2].pop();
                                time = time +  end.brust_time ;
                                completion_time[end.pid] = time  ;
                                turn_time[end.pid] =turn_time[end.pid] + time - end.arival_time ;
                                waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time;
                                seq.push_back(end.pid);
                                remove_val(S3, end.pid) ;
                            }
//
                        }
                    }
                    else
                    {
                        int L = INT16_MAX ;
                        while(1)
                        {
                            S1.extractMin();
                            if(S1.size() != 0)
                                L = S1.getMinA();
                            if(L == -1 || L > time)
                                break;
                        }
//                        int size = innerQueue[2].size();
//                        for(int i = 0 ; i < size ; i++)
//                        {
//                            remove_val(S3, innerQueue[2].front().pid);
//                            innerQueue[2].push( innerQueue[2].front());
//                            innerQueue[2].pop() ;
//                        }
                        int k  = INT16_MAX ;
                        while(1)
                        {
                            S2.extractMin();
                            k = S2.getMinA();
                            if(k == -1 || k > time)
                                break;
                        }

                        L = min(L,k) ;
                        

                        cout<<L<<"]]";
                        while(1)
                        {
                            k = S3.getMinA();
                            if(k == -1 || k > time)
                                break;
                            cout<<k<<endl;
                            S3.extractMin();

                        }
                        L = min(L,k) ;

                        if(L == -1 )
                            L = INT16_MAX;
                        cout<<"L ="<<L<<"jjj"<<endl;

                        while(!innerQueue[2].empty())
                        {
                            if(time + RR_stime >= L)
                            {
                                end = innerQueue[2].front() ;

                                int ttm = L - time;
                                
                                if(end.brust_time > ttm)
                                {
                                    end.brust_time = end.brust_time - ttm;
                                    cout<<end.pid<<" Runned for "<<ttm<<"s and Stopedpp "<<endl;

                                    
                                    time = time + ttm ;
                                    innerQueue[2].pop();
                                    innerQueue[2].push(end) ;
                                }
                                else
                                {
                                    
                                    cout<<end.pid<<" Ended"<<endl;
                                    innerQueue[2].pop();
                                    time = time +  end.brust_time ;
                                    completion_time[end.pid] = time  ;
                                    turn_time[end.pid] = turn_time[end.pid] + time - end.arival_time ;
                                    waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time ;
                                    
                                    seq.push_back(end.pid);
                                    remove_val(S3, end.pid) ;
                                }
                                
                                break;
                            }
                            if(innerQueue[2].size()== 1)
                            {
                                end = innerQueue[2].front() ;
                                cout<<end.pid<<" Ended"<<endl;
                                innerQueue[2].pop();
                                time = time +  end.brust_time ;
                                completion_time[end.pid] = time  ;
                                turn_time[end.pid] =turn_time[end.pid] + time - end.arival_time ;
                                waiting_time[end.pid] = waiting_time[end.pid] + time  - end.brust_time ;
                                
                                seq.push_back(end.pid);
                                remove_val(S3, end.pid) ;
                                break;
                            }

                            end = innerQueue[2].front() ;
                            if(end.brust_time > RR_stime)
                            {
                                end.brust_time = end.brust_time - RR_stime;
                                cout<<end.pid<<" Runneddd for "<<RR_stime<<"s and Stoped "<<endl;
//                                cout<<innerQueue[1].size()<<" =="<<endl;

//                                Queue_temp.insertKey(end.arival_time, end);
//                                cout<<innerQueue[1].size()<<" =="<<endl;

                                time = time + RR_stime ;
                                innerQueue[2].pop();
                                innerQueue[2].push(end) ;
                            }
                            else
                            {
                                cout<<end.pid<<" Ended"<<endl;
                                innerQueue[2].pop();
                                time = time +  end.brust_time ;
                                completion_time[end.pid] = time  ;
                                turn_time[end.pid] = turn_time[end.pid] + time - end.arival_time ;
                                waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time ;
                                
                                seq.push_back(end.pid);
                                remove_val(S3, end.pid) ;
                            }
                        }
                    }
                }
                while(!innerQueue[2].empty())
                {
                    cout<<"Error";
                    Process_t a = innerQueue[2].front();
                    plusplus_minusminus(pirority, a.pid, a);

                    Queue_temp.insertKey(innerQueue[2].front().arival_time ,a );
                    innerQueue[2].pop();
                }
                

                

            }

                            
            
        }
        else
        {
            end = Queue_temp.extractMin() ;
    //
            if(end.type == 1)
            {
//                end = Queue_temp.extractMin() ;
        //        cout<<end.pid<<"ff"<<endl;
                int temm = end.brust_time*0.5 ;
                time = time +  temm ;
                end.type++ ;
                turn_time[end.pid] = turn_time[end.pid] + time - end.arival_time ;
                waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                cout<<"waiting_time[end.pid] : "<<waiting_time[end.pid]<<endl;
                end.brust_time = end.brust_time - temm ;
                Queue.insertKey(end.brust_time, end) ;
                remove_val(S1, end.pid) ;

            }
            else if(end.type == 2)
            {
                if(S1.size() == 0 && S2.size() == 1)
                {
                    cout<<end.pid<<"ff"<<endl;
                    int temm = end.brust_time*0.3 ;
                    time = time +  temm ;
                    end.type++ ;
                    turn_time[end.pid] = turn_time[end.pid] + time - end.arival_time ;
                    waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                    cout<<"waiting_time[end.pid] : "<<waiting_time[end.pid]<<endl;

                    end.brust_time = end.brust_time - temm ;
                    Queue.insertKey(end.brust_time, end) ;
                    remove_val(S2, end.pid) ;
                }
                else
                {
                    
                    int L  = INT16_MAX;
                    if(S1.size() != 0)
                        L = S1.getMinA();
                    
                    remove_val(S2, end.pid);
                    if(S2.size() != 0)
                        L = min(L , S2.getMinA());
                    S2.insertKey(end.arival_time, end);
                    
                    
                       
                    cout<<end.pid<<"ff"<<endl;
                    int temm = end.brust_time*0.3 ;
                    time = time +  temm ;
                    turn_time[end.pid] = turn_time[end.pid] + time - end.arival_time ;
                    waiting_time[end.pid] = waiting_time[end.pid] + time - temm ;
                    cout<<"waiting_time[end.pid] : "<<waiting_time[end.pid]<<endl;

                    end.type++;
                    end.brust_time = end.brust_time - temm ;
                    Queue.insertKey(end.brust_time, end) ;
                    remove_val(S2, end.pid) ;
                        
                }

            }
            else if(end.type == 3)
            {
                cout<<Queue_temp.size()<<"Out Size "<<endl;
                int L = S1.getMinA() ;
                while(1)
                {
                    L = S1.getMinA() ;
                    if(L == -1 || L > time)
                        break;
                    S1.extractMin();
                }
                int LL = S2.getMinA();
                if( L == -1 )
                   L = S2.getMinA() ;
                else
                {
                    
                   while(1)
                   {
                       LL = S2.getMinA();
                       if(LL == -1 || LL > time)
                       {
                           break;
                       }
                       S2.extractMin();
                   }
                }
                L = min(L,LL);
                cout<<L<<"L"<<endl;
                bool flagin = 0 ;
                while(1)
                {
                    S3.extractMin();
                    int LS = S3.getMinA() ;
                    if(LS != -1)
                    {
                        cout<<"LS"<<LS<<endl;
                        if(LS < L )
                        {
                            flagin = 1 ;
                            L = LS ;
                        }
                        
                    }
                    else if( LS == -1)
                    {
                        break;
                        
                    }
                    if(LS > time)
                    {
                        L = LS ;
                        break;
                    }
                }
                
                cout<<"L : "<<L<<endl;
                if(L == -1)
                {
                    cout<<end.pid<<" Ended"<<endl;
                    time = time +  end.brust_time ;
                    completion_time[end.pid] = time  ;
                    turn_time[end.pid] = time - end.arival_time ;
                    waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time ;
                    seq.push_back(end.pid);
                    remove_val(S3, end.pid) ;

                }
                else
                {
                    if(time + end.brust_time >= L)
                    {
                        cout<<"L"<<L<<endl;
                          cout<<time<<endl;
                          int ttm = L - time;
                          cout<<ttm<<"ttm";
                          if(time + end.brust_time > ttm)
                          {
                              end.brust_time = end.brust_time - ttm;
                              cout<<end.pid<<" Runned for "<<ttm<<"s and Stoped "<<endl;

                              Queue_temp.insertKey(end.arival_time, end);
                              time = time + ttm ;


                          }
                          else
                          {
                              cout<<end.pid<<" Endeds"<<endl;
                              time = time +  end.brust_time ;
                              completion_time[end.pid] = time  ;
                              turn_time[end.pid] = time - end.arival_time ;
                              waiting_time[end.pid] = waiting_time[end.pid] + time - end.brust_time ;
                              seq.push_back(end.pid);
                              remove_val(S3, end.pid) ;
                          }
                    }
                }
            }
        }
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() <= time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(-temp.brust_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }

        
        
    }
    s = s + "ProcessID | Waiting Time | TurnAround Time | Completion Time \n\n";
    for (int i = 0; i < seq.size(); i++)
    {
        s = s + to_string(seq[i]) + "    |    " + to_string(waiting_time[seq[i]]) + "    |    " + to_string(turn_time[seq[i]]) + "    |    " + to_string(completion_time[seq[i]]) + "\n";
        cout << "pid : " << seq[i] << " | " << waiting_time[seq[i]] << " | " << turn_time[seq[i]] << " | " << completion_time[seq[i]] << endl;
    }
    return s;
//    cout<<S1.size();


}

string Multi_Level_Queue( Process_t* arr , int size , int RR_stime)
{
    string s;
    s = "ProcessID | Arrival Time | Burst Time \n\n";
    for (int i = 0; i < size; i++)
        s = s + "          P" + to_string(arr[i].pid) + "             |               " + to_string(arr[i].arival_time) + "           |        " + to_string(arr[i].brust_time) + "\n";
    s = s + "\n\n";
    MinHeap<Process_t> Queue(size) ;
    vector<int> waiting_time(size,0) ;
    vector<int> completion_time(size,0) ;
    vector<int> turn_time(size,0) ;
    vector<int> seq;
    
    MinHeap<Process_t> S1(size) , S2(size) , S3(size) ;
    for(int i = 0 ; i < size ; i++)
    {
        Queue.insertKey(arr[i].arival_time, arr[i]) ;
        if(arr[i].type == 1)
            S1.insertKey(arr[i].arival_time, arr[i]) ;
        else if(arr[i].type == 2)
            S2.insertKey(arr[i].arival_time, arr[i]) ;
        else if(arr[i].type == 3)
            S3.insertKey(arr[i].arival_time, arr[i]) ;
    }
    
    MinHeap<Process_t> Queue_temp(size) ;
    Process_t f = Queue.extractMin() , end;
    bool inflag = 0 ;
    int time = 0 ;
    Queue_temp.insertKey(f.arival_time, f);
    while(1)
    {
        cout<<time<<"f"<<endl;

        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() == f.arival_time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(temp.arival_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }
        if(Queue_temp.isEmpty())
        {
            if(Queue.isEmpty())
                break;
            else
            {
                inflag = 0 ;
                if(Queue.isEmpty() != 1)
                {
                    while(inflag == 0)
                    {
                        if(Queue.isEmpty() != 1)
                        {
                            if(Queue.getMinA() >= end.arival_time)
                            {
                                Process_t temp = Queue.extractMin();
                                Queue_temp.insertKey(-temp.brust_time, temp);
                            }
                            else
                                inflag = 1 ;
                        }
                        else
                            inflag = 1 ;
                    }
                }
                if(Queue_temp.getMinA() > time )
                    time = Queue_temp.getMinA();
            }
        }
//        cout<<Queue_temp.size()<<endl;
        if(Queue_temp.size()!=1)
        {
//            cout<<"ttt"<<endl;
            queue<Process_t> innerQueue[3];
            Process_t temp ;
            while(!Queue_temp.isEmpty())
            {
                temp = Queue_temp.extractMin() ;
                innerQueue[temp.type-1].push(temp);
            }
            
            if(!innerQueue[0].empty())
            {
                
                MinHeap<Process_t> INN(innerQueue[0].size());
                while(!innerQueue[0].empty())
                {
                    INN.insertKey(-(innerQueue[0].front().pirority) ,innerQueue[0].front() );
                    innerQueue[0].pop();
                }
                while(INN.isEmpty()==0)
                {
                    innerQueue[0].push(INN.extractMin());
//                    cout<<"1";
                }
                vector<int> stemp ;
                while(!innerQueue[0].empty())
                {
                    end = innerQueue[0].front() ;
                    cout<<end.pid<<" Ended"<<endl;
                    innerQueue[0].pop();
                    time = time +  end.brust_time ;
                    completion_time[end.pid] = time  ;
                    turn_time[end.pid] = time - end.arival_time ;
                    waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

                    seq.push_back(end.pid);
                    stemp.push_back(end.pid);
                }
//                cout<<S1.size()<<"ff";
                for(int i = 0 ; i < stemp.size() ; i++)
                {
                    remove_val(S1, stemp[i]) ;
                }
//                cout<<S1.size()<<"ff";
                while(!innerQueue[1].empty())
                {
                    Queue_temp.insertKey(innerQueue[1].front().arival_time ,innerQueue[1].front() );
                    innerQueue[1].pop();
                }
                
                while(!innerQueue[2].empty())
                {
                    Queue_temp.insertKey(innerQueue[2].front().arival_time ,innerQueue[2].front() );
                    innerQueue[2].pop();
                }


                
//
            }
            else if(!innerQueue[1].empty())
            {
               
                if(innerQueue[1].size() == 1)
                {
                    if(S1.size() == 0)
                    {
                        end = innerQueue[1].front() ;
                        cout<<end.pid<<" Endedf"<<endl;
                        innerQueue[1].pop();
                        time = time +  end.brust_time ;
                        completion_time[end.pid] = time  ;
                        turn_time[end.pid] = time - end.arival_time ;
                        waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
//                        cout<<time<<"f";
                        seq.push_back(end.pid);
                        remove_val(S2, end.pid) ;
                    }
                    else
                    {
                        int L = S1.getMinA();
                        end = innerQueue[1].front() ;
                        L = L - time ;
                        if(end.brust_time <= L)
                        {
                            cout<<end.pid<<" Ended"<<endl;
                            innerQueue[1].pop();
                            time = time +  end.brust_time ;
                            completion_time[end.pid] = time  ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                            seq.push_back(end.pid);
                            remove_val(S2, end.pid) ;
                        }
                        else
                        {
                            cout<<end.pid<<" Runned for "<<L<<"s and Stoped "<<endl;
                            end.brust_time = end.brust_time - L ;
//                            Queue_temp.insertKey(end.arival_time, end);
                            time = time + L ;
                            innerQueue[1].pop();
                            innerQueue[1].push(end);

                        }
                        
                    }
                }
                else
                {
                
                    if(S1.size() == 0 && S2.size() == innerQueue[1].size())
                    {
//                        cout<<"++"<<endl;
                        while(!innerQueue[1].empty())
                        {
                            end = innerQueue[1].front() ;

                            if(innerQueue[1].size()== 1)
                            {
                              cout<<end.pid<<" Endedss&&"<<endl;
                              innerQueue[1].pop();
                              time = time +  end.brust_time ;
                              completion_time[end.pid] = time  ;
                              turn_time[end.pid] = time - end.arival_time ;
                              waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

                              seq.push_back(end.pid);
                              remove_val(S2, end.pid) ;
                              break;
                            }
                            
                            if(end.brust_time > RR_stime)
                            {
                                end = innerQueue[1].front() ;

                                end.brust_time = end.brust_time - RR_stime;
                                cout<<end.pid<<" Runnedss for "<<RR_stime<<"s and Stoped "<<endl;

                             
                                time = time + RR_stime ;
                                innerQueue[1].pop();
                                innerQueue[1].push(end) ;
                            }
                            else
                            {
                                cout<<end.pid<<" Endedss%%"<<endl;
                                innerQueue[1].pop();
                                time = time +  end.brust_time ;
                                completion_time[end.pid] = time  ;
                                turn_time[end.pid] = time - end.arival_time ;
                                waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                                
                                seq.push_back(end.pid);
                                remove_val(S2, end.pid) ;
                            }
//
                        }
                    }
                    else
                    {
                        int L = INT16_MAX ;
                        if(S1.size() != 0)
                            L = S1.getMinA();
                        int size = innerQueue[1].size();
                        for(int i = 0 ; i < size ; i++)
                        {
                            remove_val(S2, innerQueue[1].front().pid);
                            innerQueue[1].push( innerQueue[1].front());
                            innerQueue[1].pop() ;
                        }
                        if(S2.size() !=0)
                            L = min(L,S2.getMinA()) ;
                        
                        for(int i = 0 ; i < size ; i++)
                        {
                            S2.insertKey(innerQueue[1].front().arival_time, innerQueue[1].front()) ;
                            innerQueue[1].push( innerQueue[1].front());
                            innerQueue[1].pop() ;
                        }
                        cout<<L<<"jjj"<<endl;
                        
                        while(!innerQueue[1].empty())
                        {
                            if(time + RR_stime >= L)
                            {
                                end = innerQueue[1].front() ;

                                int ttm = L - time;
                                
                                if(end.brust_time > ttm)
                                {
                                    end.brust_time = end.brust_time - ttm;
                                    cout<<end.pid<<" Runned for "<<ttm<<"s and Stopedpp "<<endl;
                                    time = time + ttm ;
                                    innerQueue[1].pop();
                                    innerQueue[1].push(end) ;
                                }
                                else
                                {
                                    
                                    cout<<end.pid<<" Ended"<<endl;
                                    innerQueue[1].pop();
                                    time = time +  end.brust_time ;
                                    completion_time[end.pid] = time  ;
                                    turn_time[end.pid] = time - end.arival_time ;
                                    waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                                    
                                    seq.push_back(end.pid);
                                    remove_val(S2, end.pid) ;
                                }
                                
                                break;
                            }
                            if(innerQueue[1].size()== 1)
                            {
                                end = innerQueue[1].front() ;
                                cout<<end.pid<<" Ended"<<endl;
                                innerQueue[1].pop();
                                time = time +  end.brust_time ;
                                completion_time[end.pid] = time  ;
                                turn_time[end.pid] = time - end.arival_time ;
                                waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                                
                                seq.push_back(end.pid);
                                remove_val(S2, end.pid) ;
                                break;
                            }

                            end = innerQueue[1].front() ;
                            if(end.brust_time > RR_stime)
                            {
                                end.brust_time = end.brust_time - RR_stime;
                                cout<<end.pid<<" Runneddd for "<<RR_stime<<"s and Stoped "<<endl;
//                                cout<<innerQueue[1].size()<<" =="<<endl;

//                                Queue_temp.insertKey(end.arival_time, end);
//                                cout<<innerQueue[1].size()<<" =="<<endl;

                                time = time + RR_stime ;
                                innerQueue[1].pop();
                                innerQueue[1].push(end) ;
                            }
                            else
                            {
                                cout<<end.pid<<" Ended"<<endl;
                                innerQueue[1].pop();
                                time = time +  end.brust_time ;
                                completion_time[end.pid] = time  ;
                                turn_time[end.pid] = time - end.arival_time ;
                                waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                                
                                seq.push_back(end.pid);
                                remove_val(S2, end.pid) ;
                            }
                                                   
                        }

                    }
                }
                while(!innerQueue[1].empty())
                {
                    Queue_temp.insertKey(innerQueue[1].front().arival_time ,innerQueue[1].front() );
                    innerQueue[1].pop();
                }
                while(!innerQueue[2].empty())
                {
                    Queue_temp.insertKey(innerQueue[2].front().arival_time ,innerQueue[2].front() );
                    innerQueue[2].pop();
                }

                
            }
            
            
            else if(!innerQueue[2].empty())
            {
                cout<<innerQueue[2].size()<<"In Size "<<endl;
                MinHeap<Process_t> INN(innerQueue[2].size()) ;
                while(!innerQueue[2].empty())
                {
                    INN.insertKey(innerQueue[2].front().brust_time ,innerQueue[2].front() );
                    innerQueue[2].pop();
                }
                while(INN.isEmpty() == 0)
                {
                    innerQueue[2].push(INN.extractMin());
                }
//
//
                end = innerQueue[2].front() ;
                
                end.print();

                cout<<innerQueue[2].size()<<" bbb"<<endl<<endl;
                int L ;
                bool flagin = 0 ;
                while(1)
                {
                    flagin = 0 ;
                    L = S1.getMinA() ;
                    
                    if( L == -1 )
                       L = S2.getMinA() ;
                    else
                    {
                       int LL = S2.getMinA();
                       if ( LL != -1)
                           L = min(L,LL) ;
                    }
                    cout<<L<<"L"<<endl;
                    S3.extractMin();
                    int LS = S3.getMinA() ;
                    if(LS != -1)
                    {
                        cout<<"LS"<<LS<<endl;
                        if(LS < L || L == -1)
                        {
                            flagin = 1 ;
                            L = LS ;
                        }
                    }
                    if(L >=time || L == -1)
                        break;
                    
                }
                
                cout<<"L : "<<L<<endl;
                cout<<flagin<<endl;
                if(L == -1)
                {
                    while(!innerQueue[2].empty())
                    {
                        cout<<end.pid<<" Endeddd"<<endl;
                        innerQueue[2].pop();
                        time = time +  end.brust_time ;
                        completion_time[end.pid] = time  ;
                        turn_time[end.pid] = time - end.arival_time ;
                        waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

                        seq.push_back(end.pid);
//                        remove_val(S3, end.pid) ;
                        end = innerQueue[2].front() ;
                    }
                }
                else if(flagin == 0)
                {
                    while(!innerQueue[2].empty())
                    {
                        end = innerQueue[2].front() ;
                        if(time + end.brust_time > L)
                        {
                            int ttm = L - time  ;
                            end.brust_time = end.brust_time - ttm;
                            cout<<end.pid<<" Runned for "<<ttm<<"s and Stoped "<<endl;
                            innerQueue[2].push(end) ;
                            time = time + ttm ;
                            break;
                        }
                        else
                        {
                            cout<<end.pid<<" Endedee"<<endl;
                            innerQueue[2].pop();
                            time = time +  end.brust_time ;
                            completion_time[end.pid] = time  ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                            seq.push_back(end.pid);
                            remove_val(S3, end.pid) ;
//                            end = innerQueue[2].front() ;
                            
                        }
                    }
                }
                else if(flagin == 1)
                {
                    end = innerQueue[2].front() ;
                    end.print();
                    while(!innerQueue[2].empty())
                    {
                        if(time + end.brust_time > L)
                        {
                            int ttm = L - time  ;
                            cout<<ttm<<endl;
        
                            end.brust_time = end.brust_time - ttm;
                            cout<<time<<"tttt"<<endl;
                            time = time + ttm ;
                            
                            cout<<"innnn"<<time;
                            if(end.brust_time > S3.getB())
                            {
                                cout<<end.pid<<" runned for "<<ttm<<"s"<<endl;
                                innerQueue[2].pop() ;
                                innerQueue[2].push(end) ;
                                end = innerQueue[2].front() ;
                            }
                            S3.extractMin() ;
                            L = S3.getMinA() ;
                            if(L == -1)
                            {
//                                innerQueue[2].push(end) ;
                                break;
                            }

                        }
                        else
                        {
                            cout<<end.pid<<" Endedee"<<endl;
                            innerQueue[2].pop();
                            time = time +  end.brust_time ;
                            completion_time[end.pid] = time  ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                            seq.push_back(end.pid);
                            remove_val(S3, end.pid) ;

                            S3.extractMin() ;
                            L = S3.getMinA() ;
                            if(L == -1)
                                break;

                            
                        }
                    }
                }

                while(!innerQueue[2].empty())
                {
                    Queue_temp.insertKey(innerQueue[2].front().arival_time ,innerQueue[2].front() );
                    innerQueue[2].pop();
                }

                    
                

            }

                            
            
        }
        else
        {
            end = Queue_temp.extractMin() ;
    //
            if(end.type == 1)
            {
//                end = Queue_temp.extractMin() ;
        //        cout<<end.pid<<"ff"<<endl;
                time = time +  end.brust_time ;
                completion_time[end.pid] = time  ;
                turn_time[end.pid] = time - end.arival_time ;
                waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

                seq.push_back(end.pid);
                remove_val(S1, end.pid) ;

            }
            else if(end.type == 2)
            {
                if(S1.size() == 0 && S2.size() == 1)
                {
                    cout<<end.pid<<" Ended"<<endl;
                    time = time +  end.brust_time ;
                    completion_time[end.pid] = time  ;
                    turn_time[end.pid] = time - end.arival_time ;
                    waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

                    seq.push_back(end.pid);
                    remove_val(S2, end.pid) ;
                }
                else
                {
                    
                    int L  = INT16_MAX;
                    if(S1.size() != 0)
                        L = S1.getMinA();
                    
                    remove_val(S2, end.pid);
                    if(S2.size() != 0)
                        L = min(L , S2.getMinA());
                    S2.insertKey(end.arival_time, end);
                    
                    if(time + end.brust_time >= L)
                    {
                        cout<<time<<endl;
                        int ttm = L - time;
                        cout<<ttm<<"ttm";
                        if(time + end.brust_time > ttm)
                        {
                            end.brust_time = end.brust_time - ttm;
                            cout<<end.pid<<" Runned for "<<ttm<<"s and Stoped "<<endl;
                           
                            Queue_temp.insertKey(end.arival_time, end);
                            time = time + ttm ;

                            
                        }
                        else
                        {
                            cout<<end.pid<<" Endeds"<<endl;
                            time = time +  end.brust_time ;
                            completion_time[end.pid] = time  ;
                            turn_time[end.pid] = time - end.arival_time ;
                            waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
                            
                            seq.push_back(end.pid);
                            remove_val(S2, end.pid) ;
                        }
                    }

                }

            }
            else if(end.type == 3)
            {
                cout<<Queue_temp.size()<<"Out Size "<<endl;
                int L = S1.getMinA() ;
                
                if( L == -1 )
                   L = S2.getMinA() ;
                else
                {
                   int LL = S2.getMinA();
                   if ( LL != -1)
                       L = min(L,LL) ;
                }
                cout<<L<<"L"<<endl;
                bool flagin = 0 ;
                S3.extractMin();
                int LS = S3.getMinA() ;
                if(LS != -1)
                {
                    cout<<"LS"<<LS<<endl;
                    if(LS < L )
                    {
                        flagin = 1 ;
                        L = LS ;
                    }
                }
                
                cout<<"L : "<<L<<endl;
                if(L == -1)
                {
                    cout<<end.pid<<" Ended"<<endl;
                    time = time +  end.brust_time ;
                    completion_time[end.pid] = time  ;
                    turn_time[end.pid] = time - end.arival_time ;
                    waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
    
                    seq.push_back(end.pid);
                    remove_val(S3, end.pid) ;

                }
                else
                {
                    if(time + end.brust_time >= L)
                    {
                        cout<<"L"<<L<<endl;
                          cout<<time<<endl;
                          int ttm = L - time;
                          cout<<ttm<<"ttm";
                          if(time + end.brust_time > ttm)
                          {
                              end.brust_time = end.brust_time - ttm;
                              cout<<end.pid<<" Runned for "<<ttm<<"s and Stoped "<<endl;

                              Queue_temp.insertKey(end.arival_time, end);
                              time = time + ttm ;


                          }
                          else
                          {
                              cout<<end.pid<<" Endeds"<<endl;
                              time = time +  end.brust_time ;
                              completion_time[end.pid] = time  ;
                              turn_time[end.pid] = time - end.arival_time ;
                              waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

                              seq.push_back(end.pid);
                              remove_val(S3, end.pid) ;
                          }
                    }
                }

//                cout<<end.pid<<" Ended"<<endl;
//                time = time +  end.brust_time ;
//                completion_time[end.pid] = time  ;
//                turn_time[end.pid] = time - end.arival_time ;
//                waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
//
//                seq.push_back(end.pid);
//                remove_val(S2, end.pid) ;
                
//                else
//                {
//
//                    int L  = INT8_MAX;
//                    if(S1.size() != 0)
//                        L = S1.getMinA();
//
//                    remove_val(S3, end.pid);
//                    if(S2.size() != 0)
//                        L = min(L , S2.getMinA());
//
//                    if(S3.size() != 0)
//                        L = min(L , S3.getMinA());
//
//                    S3.insertKey(end.arival_time, end);
//
//                    if(time + end.brust_time >= L)
//                    {
//                        cout<<"L"<<L<<endl;
//                        cout<<time<<endl;
//                        int ttm = L - time;
//                        cout<<ttm<<"ttm";
//                        if(time + end.brust_time > ttm)
//                        {
//                            end.brust_time = end.brust_time - ttm;
//                            cout<<end.pid<<" Runned for "<<ttm<<"s and Stoped "<<endl;
//
//                            Queue_temp.insertKey(end.arival_time, end);
//                            time = time + ttm ;
//
//
//                        }
//                        else
//                        {
//                            cout<<end.pid<<" Endeds"<<endl;
//                            time = time +  end.brust_time ;
//                            completion_time[end.pid] = time  ;
//                            turn_time[end.pid] = time - end.arival_time ;
//                            waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;
//
//                            seq.push_back(end.pid);
//                            remove_val(S2, end.pid) ;
//                        }
//                    }
//
//                }
//
            }

        }
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() <= time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(-temp.brust_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }

        
        
    }
    s = s + "ProcessID | Waiting Time | TurnAround Time | Completion Time \n\n";
    for (int i = 0; i < seq.size(); i++)
    {
        s = s + to_string(seq[i]) + "    |    " + to_string(waiting_time[seq[i]]) + "    |    " + to_string(turn_time[seq[i]]) + "    |    " + to_string(completion_time[seq[i]]) + "\n";
        cout << "pid : " << seq[i] << " | " << waiting_time[seq[i]] << " | " << turn_time[seq[i]] << " | " << completion_time[seq[i]] << endl;
    }
    return s;
//    cout<<S1.size();

}

string Lowest_Feedback_Ratio_Next_Scheduling(Process_t* arr , int size)
{
    string s;
    s = "ProcessID | Arrival Time | Burst Time \n\n";
    for (int i = 0; i < size; i++)
        s = s + "          P" + to_string(arr[i].pid) + "             |               " + to_string(arr[i].arival_time) + "           |        " + to_string(arr[i].brust_time) + "\n";
    s = s + "\n\n";
    MinHeap<Process_t> Queue(size) ;
    vector<int> waiting_time(size,0) ;
    vector<int> completion_time(size,0) ;
    vector<int> turn_time(size,0) ;
    vector<int> seq;
    for(int i = 0 ; i < size ; i++)
        Queue.insertKey(arr[i].arival_time, arr[i]) ;
    
    MinHeap<Process_t> Queue_temp(size) ;
    Process_t f = Queue.extractMin() , end;
    bool inflag = 0 ;
    int time = 0 ;
    Queue_temp.insertKey(f.arival_time, f);
    while(1)
    {
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() == f.arival_time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(temp.arival_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }
        if(Queue_temp.isEmpty())
        {
            if(Queue.isEmpty())
                break;
            else
            {
                inflag = 0 ;
                if(Queue.isEmpty() != 1)
                {
                    while(inflag == 0)
                    {
                        if(Queue.isEmpty() != 1)
                        {
                            if(Queue.getMinA() >= end.arival_time)
                            {
                                Process_t temp = Queue.extractMin();
                                Queue_temp.insertKey(temp.arival_time, temp);
                            }
                            else
                                inflag = 1 ;
                        }
                        else
                            inflag = 1 ;
                    }
                }
                time = Queue_temp.getMinA();
            }
        }
//        cout<<Queue_temp.size()<<endl;
        if(Queue_temp.size()==1)
            end = Queue_temp.extractMin() ;
        else
        {
            MinHeap<Process_t> innerQueue(size);
            Process_t temp ;
            while(!Queue_temp.isEmpty())
            {
                temp = Queue_temp.extractMin() ;
                float fd = (time - temp.arival_time)  + temp.brust_time ;
                fd = (float)(fd/temp.brust_time);
//                cout<<temp.pid<<" fd : "<<fd<<endl;
                innerQueue.insertKey(fd*100,temp);
            }
            end = innerQueue.extractMin();
            while(!innerQueue.isEmpty())
            {
                temp = innerQueue.extractMin() ;
                Queue_temp.insertKey(temp.arival_time,temp);
            }

            
            
        }

        time = time +  end.brust_time ;
        completion_time[end.pid] = time  ;
        turn_time[end.pid] = time - end.arival_time ;
        waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

        seq.push_back(end.pid);
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() <= time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(temp.arival_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }

        
        
    }
    s = s + "ProcessID | Waiting Time | TurnAround Time | Completion Time \n\n";
    for (int i = 0; i < seq.size(); i++)
    {
        s = s + to_string(seq[i]) + "    |    " + to_string(waiting_time[seq[i]]) + "    |    " + to_string(turn_time[seq[i]]) + "    |    " + to_string(completion_time[seq[i]]) + "\n";
        cout << "pid : " << seq[i] << " | " << waiting_time[seq[i]] << " | " << turn_time[seq[i]] << " | " << completion_time[seq[i]] << endl;
    }
    return s;
}

//Process_t arr[5] ;
//Process_t a(1,3,3,30,1);
//Process_t b(2,6,3,20,2);
//Process_t c(3,0,4,40,3);
//Process_t d(4,2,5,60,2);
//Process_t e(4,0,1,20,3);
//arr[0] = a ;
//arr[1] = b ;
//arr[2] = c ;
//arr[3] = d ;
//arr[4] = e ;
//
//Longest_Job_First(arr, 4 );


string Longest_Job_First( Process_t* arr , int size)
{
    string s;
    s = "ProcessID | Arrival Time | Burst Time \n\n";
    for (int i = 0; i < size; i++)
        s = s + "          P" + to_string(arr[i].pid) + "             |               " + to_string(arr[i].arival_time) + "           |        " + to_string(arr[i].brust_time) + "\n";
    s = s + "\n\n";
    MinHeap<Process_t> Queue(size) ;
    vector<int> waiting_time(size,0) ;
    vector<int> completion_time(size,0) ;
    vector<int> turn_time(size,0) ;
    vector<int> seq;
    for(int i = 0 ; i < size ; i++)
        Queue.insertKey(arr[i].arival_time, arr[i]) ;
    
    MinHeap<Process_t> Queue_temp(size) ;
    Process_t f = Queue.extractMin() , end;
    bool inflag = 0 ;
    int time = 0 ;
    Queue_temp.insertKey(-f.brust_time, f);
    while(1)
    {
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() == f.arival_time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(-temp.brust_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }
        if(Queue_temp.isEmpty())
        {
            if(Queue.isEmpty())
                break;
            else
            {
                inflag = 0 ;
                if(Queue.isEmpty() != 1)
                {
                    while(inflag == 0)
                    {
                        if(Queue.isEmpty() != 1)
                        {
                            if(Queue.getMinA() >= end.arival_time)
                            {
                                Process_t temp = Queue.extractMin();
                                Queue_temp.insertKey(-temp.brust_time, temp);
                            }
                            else
                                inflag = 1 ;
                        }
                        else
                            inflag = 1 ;
                    }
                }
                time = Queue_temp.getMinA();
            }
        }
        end = Queue_temp.extractMin() ;
        time = time +  end.brust_time ;
        completion_time[end.pid] = time  ;
        turn_time[end.pid] = time - end.arival_time ;
        waiting_time[end.pid] = turn_time[end.pid] - end.brust_time ;

        seq.push_back(end.pid);
        inflag = 0 ;
        if(Queue.isEmpty() != 1)
        {
            while(inflag == 0)
            {
                if(Queue.isEmpty() != 1)
                {
                    if(Queue.getMinA() <= time)
                    {
                        Process_t temp = Queue.extractMin();
                        Queue_temp.insertKey(-temp.brust_time, temp);
                    }
                    else
                        inflag = 1 ;
                }
                else
                    inflag = 1 ;
            }
        }
    }
    s = s + "ProcessID | Waiting Time | TurnAround Time | Completion Time \n\n";
    for(int i = 0 ; i < seq.size() ; i++)
    {
        s = s + to_string(seq[i]) + "    |    " + to_string(waiting_time[seq[i]]) + "    |    " + to_string(turn_time[seq[i]]) + "    |    " + to_string(completion_time[seq[i]]) + "\n";
        cout<<"pid : "<<seq[i]<<" | "<< waiting_time[seq[i]]<<" | "<<turn_time[seq[i]]<<" | "<<completion_time[seq[i]]<<endl;
    }
    return s;
}

 


//main
//
//Process_t arr[5] ;
//Process_t a(0,0,20,30,1);
//Process_t b(1,5,10,20,2);
//Process_t c(2,7,20,40,3);
//Process_t d(3,20,20,60,2);
//Process_t e(4,25,20,20,3);
//arr[0] = a ;
//arr[1] = b ;
//arr[2] = c ;
//arr[3] = d ;
//arr[4] = e ;
//
//Multi_Level_Queue(arr, 5 , 5);




#endif /* CPU_h */
