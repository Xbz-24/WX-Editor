#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stc/stc.h>
#include <wx/button.h>
#include <wx/wfstream.h>
#include "constants.hpp"

class app : public wxApp
{
    public:
        bool OnInit() override;
};

class main_editor_frame : public wxFrame {
private:
    wxStyledTextCtrl *editor;
    wxButton *saveButton;
    wxButton *openButton;
    wxButton *newFileButton;
    wxButton *toggleDarkModeButton;

public:
    main_editor_frame(const wxString &title, const wxPoint &pos, const wxSize &size);

    void OnSave(wxCommandEvent &event);

    void OnOpen(wxCommandEvent &event);

    void OnNewFile(wxCommandEvent &event);

    void OnToggleDarkMode(wxCommandEvent &event);

    void ApplyEditorStyles(bool isDarkMode);
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
                            :wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    auto* vbox = new wxBoxSizer(wxVERTICAL);

    saveButton = new wxButton(this, wxID_ANY, Constants::SAVE_BUTTON_LABEL, Constants::SAVE_BUTTON_POSITION, wxDefaultSize);
    openButton = new wxButton(this, wxID_ANY, Constants::OPEN_BUTTON_LABEL, Constants::OPEN_BUTTON_POSITION, wxDefaultSize);
    newFileButton = new wxButton(this, wxID_ANY, "New File");
    toggleDarkModeButton = new wxButton(this, wxID_ANY, "Toggle Dark Mode");

    saveButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnSave, this);
    openButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnOpen, this);
    newFileButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnNewFile, this);
    toggleDarkModeButton -> Bind(wxEVT_BUTTON, &main_editor_frame::OnToggleDarkMode, this);

    auto* hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(saveButton);
    hbox->Add(openButton);
    hbox->Add(newFileButton);
    hbox->Add(toggleDarkModeButton);

    vbox->Add(hbox,0,wxEXPAND | wxALL, 5);
    editor = new wxStyledTextCtrl(this, wxID_ANY);

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
}

void main_editor_frame::OnNewFile(wxCommandEvent& event)
{
    editor->ClearAll();
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
