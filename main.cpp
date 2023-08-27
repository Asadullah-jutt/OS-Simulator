#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        // Create and show the main window
        wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "MyApp");
        frame->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);

