#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stc/stc.h>
#include <wx/button.h>
#include "constants.hpp"

class app : public wxApp
{
public:
    bool OnInit() override;
};

class main_editor_frame : public wxFrame
{
private:
    wxStyledTextCtrl* editor;
    wxButton* saveButton;
    wxButton* openButton;

public:
    main_editor_frame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnSave(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
};

wxIMPLEMENT_APP(app);

bool app::OnInit()
{
    auto *frame = new main_editor_frame("text-editor_wx-widgets", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

main_editor_frame::main_editor_frame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    editor = new wxStyledTextCtrl(this, wxID_ANY);
    editor->SetLexer(wxSTC_LEX_CPP);
    editor->StyleSetForeground(wxSTC_C_STRING, wxColour(150, 0, 0));
    editor->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColour(165, 105, 0));
    editor->StyleSetForeground(wxSTC_C_IDENTIFIER, wxColour(40, 0, 60));
    editor->StyleSetForeground(wxSTC_C_NUMBER, wxColour(0, 150, 0));
    editor->StyleSetForeground(wxSTC_C_CHARACTER, wxColour(150, 0, 0));
    editor->StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 150));
    editor->StyleSetForeground(wxSTC_C_WORD2, wxColour(0, 150, 0));
    editor->StyleSetForeground(wxSTC_C_COMMENT, wxColour(150, 150, 150));
    editor->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(150, 150, 150));
    editor->StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(150, 150, 150));
    editor->StyleSetForeground(wxSTC_C_OPERATOR, wxColour(0,0,200));
    editor->StyleSetBold(wxSTC_C_WORD, true);
    editor->StyleSetBold(wxSTC_C_WORD2, true);
    editor->StyleSetBold(wxSTC_C_COMMENTDOC, true);
    editor->SetKeyWords(0,Constants::editorKeywords);
    editor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    editor->SetMarginWidth(0, editor->TextWidth(wxSTC_STYLE_LINENUMBER, "_99999"));
    editor->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
    editor->SetMarginType(1, wxSTC_MASK_FOLDERS);
    editor->SetMarginWidth(1,16);
    editor->SetMarginSensitive(1,true);
    editor->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS);
    editor->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS);
    editor->SetProperty("fold", "1");
    editor->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
    editor->AutoCompSetSeparator(' ');
    editor->AutoCompSetIgnoreCase(true);
    editor->AutoCompSetAutoHide(false);
    editor->AutoCompSetDropRestOfWord(true);
    editor->AutoCompShow(0, "int char float double");
    saveButton = new wxButton(this, wxID_ANY, wxT("Save"), wxPoint(10, 300), wxDefaultSize);
    openButton = new wxButton(this, wxID_ANY, wxT("Open"), wxPoint(100, 300), wxDefaultSize);
    saveButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnSave, this);
    openButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnOpen, this);
}

void main_editor_frame::OnSave(wxCommandEvent &event)
{

}

void main_editor_frame::OnOpen(wxCommandEvent &event)
{

}
