//
//  Paging.h
//  OS Project
//
//  Created by MAC on 26/04/2023.
//

#ifndef Paging_h
#define Paging_h


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <queue>
#include <cmath>
#include "HashMap.h"

using namespace std;

//Hashed_Page_Table_with_TLP(256, 'm', 1, 'k',4,'m');


int appendDigit(int base, int append) {
   std::string sBase = std::to_string(base);
   std::string sAppend = std::to_string(append);
   std::string result = sBase + sAppend;
   return std::stoi(result);

}

int count_digit(int number) {
   int count = 0;
   while(number != 0) {
      number = number / 10;
      count++;
   }
   return count;
}


int KMGT(char a)
{
    if(a == 'K' || a == 'k')
        return 10 ;
    else if(a == 'M' || a == 'm')
        return 20 ;
    else if(a == 'G' || a == 'g')
        return 30 ;
    else if(a == 'T' || a == 't')
        return 40 ;
    
    return -1 ;
}

int getPageOffset(int address , int PAGE_SIZE ) {
    return address % PAGE_SIZE;
}




class PageTable {
public:
    int* entries; // Page table entries
};


//char fetchData(int virtualAddress, PageTable* pageTables[]) {
//    // Translate the virtual address to a physical address
//    int physicalAddress = translateAddress(virtualAddress, pageTables);
//
//    // Access the data in physical memory
//    char data = memory[physicalAddress];
//
//    return data;
//}

int translateAddress(int virtualAddress,int PAGE_OFFSET_BITS ,int PAGE_TABLE_ENTRIES,int PHYSICAL_ADDRESS_BITS, PageTable* pageTables[]) {
    // Split the virtual address into page number and offset
    // Calculate the indices for the two-level page table
    int page_size  = pow(2,PAGE_OFFSET_BITS);
    int pageIndex1 = virtualAddress / (PAGE_TABLE_ENTRIES *page_size);
    int pageIndex2 = ((virtualAddress / page_size) % PAGE_TABLE_ENTRIES);

    // Check if the page table entry is present in the second-level page table
    // Check if the first-level page table exists
      if (!pageTables[pageIndex1]) {
          // Page fault: allocate a new second-level page table and update the first-level page table
          pageTables[pageIndex1] = new PageTable;
          pageTables[pageIndex1]->entries = new int[PAGE_TABLE_ENTRIES];
          for (int i = 0; i < PAGE_TABLE_ENTRIES; i++) {
              pageTables[pageIndex1]->entries[i] = -1; // Mark all entries as invalid
          }
      }

      // Check if the second-level page table exists
      int frameNumber;
      if (pageTables[pageIndex1]->entries[pageIndex2] != -1) {
          // The page is in memory: get the frame number from the page table
          frameNumber = pageTables[pageIndex1]->entries[pageIndex2];
      }
      else
          return -1 ;
        
      // Combine the frame number and offset to get the physical address
    int physicalAddress = (frameNumber * page_size) + (virtualAddress % page_size);
    return physicalAddress;
    
}

string Two_Level_Paging(int main_memory_size , char m_KMGT_B , int page_size , char p_KMGT_B , int process_size , char pro_KMGT_B)
{
    string ss; 
    ss = "Main Memory Size : " + to_string(main_memory_size) + m_KMGT_B + "b | ";
    ss = ss + "Page Size : " + to_string(page_size) + p_KMGT_B + "b | ";
    ss = ss + "Process Size : " + to_string(process_size) + pro_KMGT_B + "b\n";
    int physical_address_bits = KMGT(m_KMGT_B);
    if(physical_address_bits == -1)
    {
        cout<<"Wrong Input "<<endl;

    }
    physical_address_bits = physical_address_bits + log2(main_memory_size) ;
    
    int page_bits = KMGT(p_KMGT_B);
    if(page_bits == -1)
    {
        cout<<"Wrong Input "<<endl;
    }
    page_bits = page_bits + log2(page_size) ;
    int MEMORY_SIZE = pow(2, (physical_address_bits - page_bits));
    short* memory = new short[MEMORY_SIZE] ;
    for(int i = 0 ; i < MEMORY_SIZE ; i++)
    {
        memory[i] = rand()%10000;
    }
    
    int PAGE_TABLE_ENTRIES = pow(2, page_bits) ;
    PageTable** pageTables = new PageTable*[PAGE_TABLE_ENTRIES];
        for (int i = 0; i < PAGE_TABLE_ENTRIES; i++) {
            pageTables[i] = NULL; // Initialize all entries to NULL
        }

    


    int frame_bits = physical_address_bits - page_bits ;
    ss = ss + '\n';
    ss = ss + "Physical Address Bits = " + to_string(physical_address_bits) + "B\n";
    ss = ss + "Page Bits = " + to_string(page_bits) + "B\n";
    ss = ss + "Frame Bits = " + to_string(frame_bits) + "B\n";

    cout<<"Physical Address Bits = "<< physical_address_bits<<" B"<<endl;
    cout<<"Page Bits = "<<page_bits<<" B"<<endl;
    cout<<"Frame Bits = "<<frame_bits<<" B"<<endl;
    
    int logical_address = KMGT(pro_KMGT_B) ;
    if(logical_address == -1)
    {
        cout<<"Wrong Input "<<endl;
  
    }
    logical_address = logical_address + log2(process_size) ;
    cout<<"Logical Address = "<<logical_address<<" b"<<endl;
    ss = ss + "Logical Address Bits = " + to_string(logical_address) + "B\n";
    int l_p_entry_bit = logical_address - page_bits ;
    
    cout<<"Logical Adress page Size = "<<page_bits<<" b"<<endl;
    ss = ss + "Logical Address page Bit = " + to_string(page_bits) + "B\n";
    int *page_bit = new int ;
    *page_bit = l_p_entry_bit ;
    if(l_p_entry_bit >= page_bits)
    {
        ss = ss + "Logical Address page Bit = " + to_string(page_bits) + "B\n";
     
        cout<<"As this Page table can't be stored in this page size so we have to reduce its size "<<endl;
        delete page_bit ;
        page_bit = new int[2] ;
        page_bit[0] = l_p_entry_bit - page_bits ;
        page_bit[1] = l_p_entry_bit - page_bit[0] ;
        ss = ss + "Outer page Bit = " + to_string(page_bit[0]) + "B\n";
        ss = ss + "Inner page Bit = " + to_string(page_bit[1]) + "B\n\n";
        cout<<"Outer Page bits = "<<page_bit[0]<<" b"<<endl;
        cout<<"Inner Page bits = "<<page_bit[1]<<" b"<<endl;
        
        
        int a = pow(2,logical_address);

        int virtualAddress = rand() % a ;
        ss = ss + "Virtual Address Ramdomly Genrated : " + to_string(virtualAddress) +  "\n";
            // Fetch data from memory
        cout << "Inner Page bits = " << page_bit[1] << " b" << endl;
        cout<<"Virtual Address Ramdomly Genrated : "<<virtualAddress<<endl;
////        cout<<"fff = "<<pageNumber2<<endl;
        int physicalAddress = translateAddress(virtualAddress, page_bits, PAGE_TABLE_ENTRIES, physical_address_bits, pageTables);
        if(physicalAddress == -1)
        {
            cout<<"No data at this Virtual Address = "<<virtualAddress<<":-)"<<endl;
            ss = ss + "No data at this Virtual Address :-)\n";
        }
        else
        {
            short data = memory[physicalAddress];
            ss = ss + "Virtual Address : " + to_string(virtualAddress) + " gave a Physical Address = " + to_string(physicalAddress) + "and the Data at this Address = " + to_string(data) + "\n";
            cout << "Virtual Address = " << virtualAddress << " gave a Physical Address = " << physicalAddress << " and Data at this Address = " << data << endl;
        }
    }
    else
    {
        ss = ss + "No Need of Two Level Paging\n";
        cout<<endl<<"No Need of 2 Level Paging "<<endl;
        cout<<"Page Bits : "<<*page_bit<<endl;
    }
    return ss;
   
    
//    int inner_page_table_diamentions = logical_address + log2(frame_bits/8);
//    cout<<"inner page table diamentions = "<<inner_page_table_diamentions<<endl;
//
//    int no_of_pages_in_inner_page_table = inner_page_table_diamentions - page_bits ;
//    cout<<"Pages in Inner Page Table = "<<no_of_pages_in_inner_page_table<<endl;
////    Number of Page Table Entries on One Inner Page Table Page:
//    int no_of_entries_inner_page = page_bits - log2(frame_bits/8); ;
//    cout<<"    Number of Page Table Entries on One Inner Page Table Page: "<<no_of_entries_inner_page<<endl;
}

vector<string> Hashed_Page_Table_with_TLP(int main_memory_size , char m_KMGT_B , int page_size , char p_KMGT_B , int process_size , char pro_KMGT_B)
{
    string ss;
    ss = "Main Memory Size : " + to_string(main_memory_size) + m_KMGT_B + "b | ";
    ss = ss + "Page Size : " + to_string(page_size) + p_KMGT_B + "b | ";
    ss = ss + "Process Size : " + to_string(process_size) + pro_KMGT_B + "b\n";
    int physical_address_bits = KMGT(m_KMGT_B);
    if(physical_address_bits == -1)
    {
        cout<<"Wrong Input "<<endl;
        
    }
    physical_address_bits = physical_address_bits + log2(main_memory_size) ;
    
    int page_bits = KMGT(p_KMGT_B);
    if(page_bits == -1)
    {
        cout<<"Wrong Input "<<endl;
        
    }

    page_bits = page_bits + log2(page_size) ;
    int MEMORY_SIZE = pow(2, (physical_address_bits - page_bits));
    short* memory = new short[MEMORY_SIZE] ;
    for(int i = 0 ; i < MEMORY_SIZE ; i++)
    {
        memory[i] = rand()%10000;
    }
    
 


    int frame_bits = physical_address_bits - page_bits ;
    cout<<" Physical Address Bits = "<< physical_address_bits<<" B"<<endl;
    cout<<" Page Bits = "<<page_bits<<" B"<<endl;
    cout<<" Frame Bits = "<<frame_bits<<" B"<<endl;
    ss = ss + '\n';
    ss = ss + "Physical Address Bits = " + to_string(physical_address_bits) + "B\n";
    ss = ss + "Page Bits = " + to_string(page_bits) + "B\n";
    ss = ss + "Frame Bits = " + to_string(frame_bits) + "B\n";

    int logical_address = KMGT(pro_KMGT_B) ;
    if(logical_address == -1)
    {
        cout<<"Wrong Input "<<endl;
        
    }
    logical_address = logical_address + log2(process_size) ;
    cout<<"Logical Address = "<<logical_address<<" b"<<endl;
    
    int l_p_entry_bit = logical_address - page_bits ;
    
    cout<<"Logical Adress page Size = "<<page_bits<<" b"<<endl;
    
    int no_of_pages = pow(2,logical_address-page_bits);
    ss = ss + "Logical Address Bits = " + to_string(logical_address) + "B\n";
    ss = ss + "Logical Address page Bit = " + to_string(page_bits) + "B\n";
    vector<string> sss;
    sss.push_back(ss);
    ss.clear();
    HashMap<LinkedList<int>> Hashed_Page_table(1);
    for(int i = 0 ; i < no_of_pages ; i++ )
    {
        int pp = pow(2,l_p_entry_bit) ;
        int dd = pow(2,frame_bits) ;
        int p = rand() % pp ;
        int d = rand() % dd ;
        Hashed_Page_table.insert(p, d);
    }
    LinkedList<int> TLB ;
    int ppp[20] , ddd[20] ;
    cout<<"Virtual Address Randomly Genrated "<<endl;
    for(int i = 0 ; i < 20 ; i++)
    {
        int a = pow(2,l_p_entry_bit);
        int p = rand() % a ;
        int dd = pow(2,page_bits) ;
        int d = rand() % dd ;
        ppp[i] = p ;
        ddd[i] = d ;
        int virtualaddress = p ;
        appendDigit(virtualaddress, d);
        int phy_address = 0 ;
        int f , c = 0;
        ss = to_string(i + 1) + "Virtaul Address : " + to_string(virtualaddress) + "\n";
        cout<<i+1<<" Virtaul Address : "<<virtualaddress<<endl;
        if(TLB.search(p,f,c))
        {
            ss = ss + "Frame No. found in TLB at Virtual Address "  + to_string(virtualaddress) + "\n";
            cout<<"Frame No. found in TLB at Virtual Address "<<virtualaddress<<endl;
            phy_address = f ;
            appendDigit(phy_address, d);
            ss = ss + "Returned a Physical Address :" + to_string(phy_address) + "\n";

            cout<<"Returned a Physical Address : "<<phy_address<<endl;
            ss = ss + "Value : " + to_string(memory[phy_address]) + "\n";
            cout<<"Value "<<memory[phy_address]<<endl;
            sss.push_back(ss);
            ss.clear();
        }
        else
        {
            
            if(Hashed_Page_table.Search(p, f))
            {
                ss = ss + "Frame No. found in Hashed Page Table at Virtual Address " + to_string(virtualaddress) + "\n";
                cout<<"Frame No. found in Hashed Page Table at Virtual Address "<<virtualaddress<<endl;
                phy_address = f ;
                appendDigit(phy_address, d);
                cout<<"Returned a Physical Address : "<<phy_address<<endl;
                cout<<"Value "<<memory[phy_address]<<endl;
                ss = ss + "Returned a Physical Address :" + to_string(phy_address) + "\n";

                ss = ss + "Value : " + to_string(memory[phy_address]) + "\n";
                ss = ss + "inserted in TLB";
                cout<<"Inserted in TLB "<<endl;
                TLB.insert(p, f);

            }
            else
            {
                cout << "Wrong Virtual Address : " << virtualaddress << endl;
                ss = ss + "Wrong Physical Address : " + to_string(virtualaddress) + "\n";
            }
            sss.push_back(ss);
            ss.clear();
        }
        cout<<endl<<endl;
              

    }
    
    ss = " Translation lookaside buffer Values \n";
    cout << "Translation lookaside buffer Values " << endl << endl;
    ss = ss + TLB.Print();
    sss.push_back(ss);
    return sss;

}



#endif /* Paging_h */
