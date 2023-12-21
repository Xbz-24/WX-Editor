#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stc/stc.h>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
private:
    wxStyledTextCtrl* codeEditor;

public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    auto *frame = new MyFrame("Text Editor WxWidgets", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    codeEditor = new wxStyledTextCtrl(this, wxID_ANY);

    // Set up the editor to a basic C++ lexer for syntax highlighting
    codeEditor->SetLexer(wxSTC_LEX_CPP);
    codeEditor->StyleSetForeground(wxSTC_C_STRING, wxColour(150, 0, 0));
    codeEditor->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColour(165, 105, 0));
    codeEditor->StyleSetForeground(wxSTC_C_IDENTIFIER, wxColour(40, 0, 60));
    codeEditor->StyleSetForeground(wxSTC_C_NUMBER, wxColour(0, 150, 0));
    codeEditor->StyleSetForeground(wxSTC_C_CHARACTER, wxColour(150, 0, 0));
    codeEditor->StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 150));
    codeEditor->StyleSetForeground(wxSTC_C_WORD2, wxColour(0, 150, 0));
    codeEditor->StyleSetForeground(wxSTC_C_COMMENT, wxColour(150, 150, 150));
    codeEditor->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(150, 150, 150));
    codeEditor->StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(150, 150, 150));
    codeEditor->StyleSetBold(wxSTC_C_WORD, true);
    codeEditor->StyleSetBold(wxSTC_C_WORD2, true);
    codeEditor->StyleSetBold(wxSTC_C_COMMENTDOC, true);

    // Set common keywords for C++ - you can add more as needed
    codeEditor->SetKeyWords(0, "return int float double char");
}
