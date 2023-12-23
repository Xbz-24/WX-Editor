#include <wx/wx.h>
#include <wx/stc/stc.h>
#include <wx/button.h>
#include <wx/wfstream.h>
#include "constants.hpp"
#include "FindDialog.hpp"
#include <wx/filename.h>
#include <wx/timer.h>

class app : public wxApp
{
public:
    bool OnInit() override;
};

class main_editor_frame : public wxFrame
{
private:
    wxStyledTextCtrl *editor;
    wxButton *saveButton;
    wxButton *openButton;
    wxButton *newFileButton;
    wxButton *toggleDarkModeButton;
    wxButton *findButton;
    wxButton *replaceButton;
    wxTimer m_timer;
    wxDECLARE_EVENT_TABLE();
    wxButton *zoomInButton;
    wxButton *zoomOutButton;
    static const int ZOOM_INCREMENT = 3;
public:
    main_editor_frame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void OnSave(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnNewFile(wxCommandEvent &event);
    void OnToggleDarkMode(wxCommandEvent &event);
    void ApplyEditorStyles(bool isDarkMode);
    void OnFind(wxCommandEvent &event);
    void OnReplace(wxCommandEvent &event);
    void OnEditorUpdate(wxStyledTextEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnZoomIn(wxCommandEvent &event);
    void OnZoomOut(wxCommandEvent &event);
};

wxIMPLEMENT_APP(app);

bool app::OnInit()
{
    wxFrame *frame = new main_editor_frame("wx-editor", wxPoint(50, 50), wxSize(450, 340));
    frame->Maximize();
    frame->Show(true);
    return true;
}

main_editor_frame::main_editor_frame(const wxString& title, const wxPoint& pos, const wxSize& size)
        :wxFrame(nullptr, wxID_ANY, title, pos, size), m_timer(this)
{
    CreateStatusBar(3);
    ;SetStatusText("Ready", 0);
    SetStatusText("Line: 1, Col: 1", 1);
    m_timer.Start(1000);

    auto* vbox = new wxBoxSizer(wxVERTICAL);
    saveButton = new wxButton(this, wxID_ANY, Constants::SAVE_BUTTON_LABEL, Constants::SAVE_BUTTON_POSITION, wxDefaultSize);
    openButton = new wxButton(this, wxID_ANY, Constants::OPEN_BUTTON_LABEL, Constants::OPEN_BUTTON_POSITION, wxDefaultSize);
    newFileButton = new wxButton(this, wxID_ANY, "New File");
    toggleDarkModeButton = new wxButton(this, wxID_ANY, "Toggle Dark Mode");
    findButton = new wxButton(this, wxID_ANY, "Find");
    replaceButton = new wxButton(this, wxID_ANY, "Replace");
    zoomInButton = new wxButton(this, wxID_ANY, "+");
    zoomOutButton = new wxButton(this, wxID_ANY, "-");

    saveButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnSave, this);
    openButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnOpen, this);
    newFileButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnNewFile, this);
    toggleDarkModeButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnToggleDarkMode, this);
    findButton-> Bind(wxEVT_BUTTON, &main_editor_frame::OnFind, this);
    replaceButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnReplace, this);
    zoomInButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnZoomIn, this);
    zoomOutButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnZoomOut, this);

    editor = new wxStyledTextCtrl(this, wxID_ANY);
    editor->Bind(wxEVT_STC_UPDATEUI, &main_editor_frame::OnEditorUpdate, this);

    auto* hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(saveButton);
    hbox->Add(openButton);
    hbox->Add(newFileButton);
    hbox->Add(toggleDarkModeButton);
    hbox->Add(findButton);
    hbox->Add(replaceButton);
    hbox->Add(zoomInButton);
    hbox->Add(zoomOutButton);

    vbox->Add(hbox,0,wxEXPAND | wxALL, 5);
    editor->SetLexer(Constants::LEXER_CPP);

    editor->StyleSetForeground(wxSTC_C_STRING       , Constants::COLOR_STRING);
    editor->StyleSetForeground(wxSTC_C_PREPROCESSOR , Constants::COLOR_PREPROCESSOR);
    editor->StyleSetForeground(wxSTC_C_IDENTIFIER   , Constants::COLOR_IDENTIFIER);
    editor->StyleSetForeground(wxSTC_C_NUMBER       , Constants::COLOR_NUMBER);
    editor->StyleSetForeground(wxSTC_C_CHARACTER    , Constants::COLOR_CHARACTER);
    editor->StyleSetForeground(wxSTC_C_WORD         , Constants::COLOR_WORD);
    editor->StyleSetForeground(wxSTC_C_WORD2        , Constants::COLOR_WORD2);
    editor->StyleSetForeground(wxSTC_C_COMMENT      , Constants::COLOR_COMMENT);
    editor->StyleSetForeground(wxSTC_C_COMMENTLINE  , Constants::COLOR_COMMENT_LINE);
    editor->StyleSetForeground(wxSTC_C_COMMENTDOC   , Constants::COLOR_COMMENT_DOC);
    editor->StyleSetForeground(wxSTC_C_OPERATOR     , Constants::COLOR_OPERATOR);

    editor->StyleSetBold(wxSTC_C_WORD               , Constants::STYLE_BOLD);
    editor->StyleSetBold(wxSTC_C_WORD2              , Constants::STYLE_BOLD);
    editor->StyleSetBold(wxSTC_C_COMMENTDOC         , Constants::STYLE_BOLD);

    editor->SetKeyWords(0,Constants::EDITOR_KEYWORDS);
    editor->SetMarginType(0, Constants::MARGIN_NUMBER_TYPE);
    editor->SetMarginWidth(0, editor->TextWidth(wxSTC_STYLE_LINENUMBER, "_99999"));
    editor->SetMarginType(1, Constants::MARGIN_SYMBOL_TYPE);
    editor->SetMarginWidth(1,Constants::MARGIN_WIDTH);
    editor->SetMarginSensitive(1,true);

    editor->MarkerDefine(Constants::MARKER_FOLDER       , wxSTC_MARK_BOXPLUS);
    editor->MarkerDefine(Constants::MARKER_FOLDER_OPEN  , wxSTC_MARK_BOXMINUS);

    editor->SetProperty("fold", "1");
    editor->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

    editor->AutoCompSetSeparator(' ');
    editor->AutoCompSetIgnoreCase(true);
    editor->AutoCompSetAutoHide(false);
    editor->AutoCompSetDropRestOfWord(true);

    editor->AutoCompShow(0, Constants::AUTO_COMP_KEYWORDS);

    vbox->Add(editor,1, wxEXPAND);
    this->SetSizer(vbox);
    this->Layout();
}

void main_editor_frame::OnSave(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog
    (
    this, _("Save File"), "", "",
    "Text Files (*.txt)|*.txt|All files (*.*)|*.*",
    wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    if(saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    if(!editor->SaveFile(saveFileDialog.GetPath()))
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
    }

    wxFileName fileName(saveFileDialog.GetPath());
    SetStatusText(fileName.GetFullName(), 0);
}

void main_editor_frame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog openFileDialog
            (
                    this, _("Open file"), "", "",
                    "Text Files (*.txt)|*.txt|All files (*.*)|*.*",
                    wxFD_OPEN|wxFD_FILE_MUST_EXIST
            );

    if(openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxFileInputStream input_stream(openFileDialog.GetPath());
    if(!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }
    editor->LoadFile(openFileDialog.GetPath());
    wxFileName fileName(openFileDialog.GetPath());
    SetStatusText(fileName.GetFullName(), 0);
}

void main_editor_frame::OnNewFile(wxCommandEvent& event)
{
    if (editor->GetModify()) {
        wxMessageDialog confirmDialog(this, _("Do you want to save changes to the current document?"), _("Confirm"), wxYES_NO | wxCANCEL | wxICON_QUESTION);
        int response = confirmDialog.ShowModal();

        if (response == wxID_YES) {
            OnSave(event);
        } else if (response == wxID_CANCEL) {
            return;
        }
    }

    editor->ClearAll();
    editor->EmptyUndoBuffer();
    SetTitle("wx-editor - New File");

}

void main_editor_frame::OnToggleDarkMode(wxCommandEvent& event)
{
    static bool isDarkMode = false;
    ApplyEditorStyles(isDarkMode);
    isDarkMode = !isDarkMode;
}

void main_editor_frame::ApplyEditorStyles(bool isDarkMode)
{
    Constants::ThemeSettings theme = Constants::GetThemeSettings(isDarkMode);
    editor->StyleClearAll();

    editor->SetLexer(Constants::LEXER_CPP);
    editor->SetKeyWords(0, Constants::EDITOR_KEYWORDS);

    for(int style = 0; style < wxSTC_STYLE_LASTPREDEFINED; style++)
    {
        editor->StyleSetBackground(style, theme.background);
        editor->StyleSetForeground(style, theme.foreground);
    }

    editor->StyleSetForeground(wxSTC_C_STRING, theme.colorString);
    editor->StyleSetForeground(wxSTC_C_PREPROCESSOR, theme.colorPreprocessor);
    editor->StyleSetForeground(wxSTC_C_IDENTIFIER, theme.colorIdentifier);
    editor->StyleSetForeground(wxSTC_C_NUMBER, theme.colorNumber);
    editor->StyleSetForeground(wxSTC_C_CHARACTER, theme.colorCharacter);
    editor->StyleSetForeground(wxSTC_C_WORD, theme.colorWord);
    editor->StyleSetForeground(wxSTC_C_WORD2, theme.colorWord2);
    editor->StyleSetForeground(wxSTC_C_COMMENT, theme.colorComment);
    editor->StyleSetForeground(wxSTC_C_COMMENTLINE, theme.colorCommentLine);
    editor->StyleSetForeground(wxSTC_C_COMMENTDOC, theme.colorCommentDoc);
    editor->StyleSetForeground(wxSTC_C_OPERATOR, theme.colorOperator);

    if (Constants::STYLE_BOLD)
    {
        editor->StyleSetBold(wxSTC_C_WORD, true);
        editor->StyleSetBold(wxSTC_C_WORD2, true);
    }
    editor->Refresh();
    editor->Update();
}

void main_editor_frame::OnFind(wxCommandEvent &event)
{
    auto* findDialog = new FindDialog(this, editor);
    findDialog->Show(true);
}

void main_editor_frame::OnReplace(wxCommandEvent &event)
{
    wxString findTerm = wxGetTextFromUser(_("Enter text to find:"), _("Replace"));
    wxString replaceTerm = wxGetTextFromUser(_("Enter replacement text:"), _("Replace With"));
    if(!findTerm.IsEmpty() && !replaceTerm.IsEmpty())
    {
        int start = 0;
        int end = editor->GetTextLength();
        editor->SetTargetStart(start);
        editor->SetTargetEnd(end);
        while(editor->SearchInTarget(findTerm) != -1)
        {
            editor -> ReplaceTarget(replaceTerm);
            start = editor -> GetTargetEnd();
            if(start >= end) break;
            editor -> SetTargetStart(start);
            editor -> SetTargetEnd(end);
        }
    }
}

void main_editor_frame::OnEditorUpdate(wxStyledTextEvent& event)
{
    int line = editor->GetCurrentLine() + 1;
    int col = editor->GetColumn(editor->GetCurrentPos() + 1);

    wxString status;
    status << "Line: " << line << ", Col: " << col;
    SetStatusText(status, 1);
}

void main_editor_frame::OnTimer(wxTimerEvent& event)
{
    wxDateTime now = wxDateTime::Now();
    wxString timeString = now.Format("%H:%M:%S");
    SetStatusText(timeString, 2);
}

wxBEGIN_EVENT_TABLE(main_editor_frame, wxFrame)
                EVT_TIMER(wxID_ANY, main_editor_frame::OnTimer)
wxEND_EVENT_TABLE()

void main_editor_frame::OnZoomIn(wxCommandEvent &event)
{
    int currentZoom = editor->GetZoom();
    editor->SetZoom(currentZoom + ZOOM_INCREMENT);

}
void main_editor_frame::OnZoomOut(wxCommandEvent &event)
{
    int currentZoom = editor->GetZoom();
    editor->SetZoom(currentZoom - ZOOM_INCREMENT);
}
