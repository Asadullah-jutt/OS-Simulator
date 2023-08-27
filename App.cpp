#include <wx/wx.h>
#include <vector>
#include "Page_Replacement.h"
#include "ResourceAllocation.h"
#include "CPU.h" 
#include "Paging.h"

vector<int> ref_page{ 1,2,3,4,5,2,3,1,2,3 };
int page = 3;
vector<string> B1;
int a = 0;
int ps = 5;
Process_t arr[6]; 
Process_t aa(0, 0, 30, 30, 1);
Process_t b(1, 1, 30, 20, 1);
Process_t c(2, 5, 30, 40, 1);
Process_t d(3, 7, 30, 60, 3);
Process_t e(4, 9, 20, 20, 2);
Process_t f(5, 15, 10, 20, 1);

string ccppuu;

string rr;

Resourses arrr[5];
int rs = 5;

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

class MyFrame : public wxFrame
{
    wxStaticText* text;
    wxButton* nextButton;
    wxFrame* frame;
    wxGauge* gauge;
public:
    MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
    {
        // Create a vertical sizer to hold the text and buttons
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Add some text to the frame

        wxStaticText* text = new wxStaticText(this, wxID_ANY, "OPERATING SYSTEM PROJECT");
        mainSizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

        // Create five buttons and add them to the sizer
        for (int i = 1; i <= 4; i++)
        {
            wxString buttonText;
            if (i == 1)
                buttonText = wxString::Format("Page Replacement");
            else if(i==2)
                buttonText = wxString::Format("Resource Allocation");
            else if(i == 3)
                buttonText = wxString::Format("Memory Management");
            else if(i == 4)
                buttonText = wxString::Format("CPU Scheduling");
            wxButton* button = new wxButton(this, wxID_ANY, buttonText);
            mainSizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

            // Connect each button to its own event handler
            switch (i) {
            case 1:
                button->Bind(wxEVT_BUTTON, &MyFrame::OnButton1Clicked, this);
                break;
            case 2:
                button->Bind(wxEVT_BUTTON, &MyFrame::OnButton2Clicked, this);
                break;
            case 3:
                button->Bind(wxEVT_BUTTON, &MyFrame::OnButton3Clicked, this);
                break;
            case 4:
                button->Bind(wxEVT_BUTTON, &MyFrame::OnButton4Clicked, this);
                break;
            default:
                break;
            }
        }

        // Set the sizer for the frame
        SetSizerAndFit(mainSizer);
    }

    void OnButton1Clicked(wxCommandEvent& event)
    {
        a = 0;
        // Create a new frame with a button and text
        frame = new wxFrame(NULL, wxID_ANY, "Page Replacement", wxDefaultPosition, wxSize(700, 700));
        gauge = new wxGauge(frame, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
        gauge->SetValue(0);
        B1 = Page_Replacement_with_Second_Chance(page, ref_page);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        string s;
        s = "REF STRING : ";
        for (int i = 0; i < ref_page.size(); i++)
            s = s + " " + to_string( ref_page[i]);
        s = s + "\n Frame Size = " + to_string (page) +"\nhand Pointer : < \n"  + "\n\n\n\n\n\n\n";
        

        text = new wxStaticText(frame, wxID_ANY, s);
        nextButton = new wxButton(frame, wxID_ANY, "Next");

       // sizer->AddStretchSpacer();
        sizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
        sizer->Add(nextButton, 0, wxALIGN_CENTER_HORIZONTAL);
        sizer->Add(gauge, 0, wxALIGN_CENTER | wxALL, 5);
        frame->SetSizer(sizer);
        frame->Centre();


        //frame->SetSizerAndFit(sizer);
        frame->Show();

        // Connect the next button to a new event handler
        nextButton->Bind(wxEVT_BUTTON, &MyFrame::OnNextButtonClicked, this);
  
            //frame->Show();
    }

    void OnNextButtonClicked(wxCommandEvent& event)
    { 
        if (a <= ref_page.size())
        {
            float g = (float)a / (float)ref_page.size();
            float d = (float)g * 100;
            gauge->SetValue(d);
            text->SetLabel(B1[a]);
            if(a == ref_page.size())
                nextButton->SetLabel("Finished");
            a++;

        }
        else
        {
            
            frame->Close();
        }

        // Change the text of the button
        
    }




    void OnButton2Clicked(wxCommandEvent& event)
    {
        frame = new wxFrame(NULL, wxID_ANY, "Resourse Allocation ", wxDefaultPosition, wxSize(700, 700));

       // wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
 
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        wxButton* button21 = new wxButton(frame, wxID_ANY, "Resource Request");
        wxButton* button22 = new wxButton(frame, wxID_ANY, "Safe State");

        sizer->Add(button21, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        sizer->Add(button22, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        vector<int> max[5] = { {7,5,3} , {3,2,2} ,{9,0,2} , {2,2,2} ,{4,3,3} };
        vector<int> allo[5] = { {0,1,0} ,{2,0,0} ,{3,0,2},{2,1,1},{0,0,2} };
        rr = "P |  MAX  | ALLOCATED \n";
        for (int i = 0; i < rs; i++)
        {
            for (int j = 0; j < max[i].size(); j++)
                rr = rr + to_string(max[i][j]) + " ";
            rr = rr + " | ";
            for (int j = 0; j < allo[i].size(); j++)
                rr = rr + to_string(allo[i][j]) + " ";
            rr = rr + "\n";
        }
    arrr[0].Set_Max_Allocated(max[0],allo[0]);
    arrr[1].Set_Max_Allocated(max[1], allo[1]);
    arrr[2].Set_Max_Allocated(max[2], allo[2]);
    arrr[3].Set_Max_Allocated(max[3], allo[3]);
    arrr[4].Set_Max_Allocated(max[4], allo[4]);

        frame->SetSizerAndFit(sizer);
        frame->Show();

        button21->Bind(wxEVT_BUTTON, &MyFrame::OnButton21Clicked, this);
        button22->Bind(wxEVT_BUTTON, &MyFrame::OnButton22Clicked, this);
        

    }
    void OnButton21Clicked(wxCommandEvent& event)
    {
        frame->Close();
        vector<int> available = { 3,3,2 };
            vector<int> seq ;
            vector<string> dd;
            Resourses_req(dd, arrr, rs, 0, { 0,2,0 }, available, seq);
            for (int i = 0; i < dd.size(); i++)
            {
                wxMessageBox(dd[i]);
            }
    }

    void OnButton22Clicked(wxCommandEvent& event)
    {
        // Code to handle button 2 click
        frame->Close();
        vector<int> available = { 3,3,2 };
        vector<int> seq;
        string yy;
        yy = " P  |   MAX   | ALLOCATED |  NEED  | \n";

        for (int i = 0; i < rs ; i++)
            yy = yy + "P" + to_string(i) + "  |  " + arrr[i].display();
        rr = rr + yy;
        Safe_State(rr, arrr, rs, available, seq);
        wxMessageBox(rr);
    }


    void OnButton3Clicked(wxCommandEvent& event)
    {
         frame = new wxFrame(NULL, wxID_ANY, "Memory Management ", wxDefaultPosition, wxSize(700, 700));

       // wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
 
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        wxButton* button31 = new wxButton(frame, wxID_ANY, "Two Level Paging");
        wxButton* button32 = new wxButton(frame, wxID_ANY, "Hashed Page Table with TLB");

        sizer->Add(button31, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        sizer->Add(button32, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        frame->SetSizerAndFit(sizer);
        frame->Show();

        button31->Bind(wxEVT_BUTTON, &MyFrame::OnButton31Clicked, this);
        button32->Bind(wxEVT_BUTTON, &MyFrame::OnButton32Clicked, this);
    }

    void OnButton31Clicked(wxCommandEvent& event)
    {
        frame->Close();
        string ss = Two_Level_Paging(256, 'm', 1, 'k', 4, 'm');
        wxMessageBox(ss);

    }

    void OnButton32Clicked(wxCommandEvent& event)
    {
        // Code to handle button 2 click
        frame->Close();
        B1 = Hashed_Page_Table_with_TLP(256, 'm', 1, 'k', 4, 'm');
        for (int i = 0; i < B1.size(); i++)
        {
            wxMessageBox(B1[i]);
        }
    }

    void OnButton4Clicked(wxCommandEvent& event)
    {
        frame = new wxFrame(NULL, wxID_ANY, "CPU Scheduling", wxDefaultPosition, wxSize(440, 440));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        wxButton* button41 = new wxButton(frame, wxID_ANY, "LJF");
        wxButton* button42 = new wxButton(frame, wxID_ANY, "LFRNS");
        wxButton* button43 = new wxButton(frame, wxID_ANY, "MLQ");
        wxButton* button44 = new wxButton(frame, wxID_ANY, "MLFQ");
        sizer->Add(button41, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
        sizer->Add(button42, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
        sizer->Add(button43, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
        sizer->Add(button44, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
        frame->SetSizerAndFit(sizer);
        frame->Show();
        //
        arr[0] = aa;
        arr[1] = b;
        arr[2] = c;
        arr[3] = d;
        arr[4] = e;
        arr[5] = f;




       //  Connect the buttons to their respective event handlers
        button41->Bind(wxEVT_BUTTON, &MyFrame::OnButton41Clicked, this);
        button42->Bind(wxEVT_BUTTON, &MyFrame::OnButton42Clicked, this);
        button43->Bind(wxEVT_BUTTON, &MyFrame::OnButton43Clicked, this);
        button44->Bind(wxEVT_BUTTON, &MyFrame::OnButton44Clicked, this);
    }
    void OnButton41Clicked(wxCommandEvent& event)
    {
        ccppuu = Longest_Job_First(arr, ps);
        wxMessageBox(ccppuu);
        ccppuu.clear();
    }

    void OnButton42Clicked(wxCommandEvent& event)
    {
        ccppuu = Lowest_Feedback_Ratio_Next_Scheduling(arr, ps);
        wxMessageBox(ccppuu);
        ccppuu.clear();
    }

    void OnButton43Clicked(wxCommandEvent& event)
    {
        ccppuu = Multi_Level_Queue(arr, ps,5);
        wxMessageBox(ccppuu);
        ccppuu.clear();
    }

    void OnButton44Clicked(wxCommandEvent& event)
    {
        ccppuu = Multi_Level_Feedback_Queue(arr, 6, 5);
        wxMessageBox(ccppuu);
        ccppuu.clear();
    }
   

private:
    void OnButtonClicked(wxCommandEvent& event)
    {
        // Get the button that was clicked
        wxButton* button = static_cast<wxButton*>(event.GetEventObject());

        // Get the text of the button
        wxString buttonText = button->GetLabel();

        // Create a new frame with the text of the button as the title
        wxFrame* frame = new wxFrame(NULL, wxID_ANY, buttonText, wxDefaultPosition, wxSize(250, 150));

        // Create a new static text widget and add it to the frame
        wxStaticText* text = new wxStaticText(frame, wxID_ANY, "Hello, world!", wxPoint(50, 50));

        // Show the frame
        frame->Show();
    }

};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame("OS PROJECT");
        
        frame->SetClientSize(600, 800);
        frame->Center();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
