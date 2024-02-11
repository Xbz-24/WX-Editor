/**
 * @file MainEditorFrame.cpp
 * @brief This class is responsible for initializing the main frame of the application.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato German Chavez Chicoma
 */

#include "MainEditorFrame.hpp"

MainEditorFrame::MainEditorFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:   wxFrame(nullptr, wxID_ANY, title, pos, size),
    m_timer(this),
    m_editorComponent(new EditorComponent(this, this)),
    m_toolbarComponent(new ToolbarComponent(this)),
    m_fileOperations(new FileOperations(m_editorComponent->GetEditor(), this)),
    m_layoutComponent(new LayoutComponent(this, m_editorComponent, m_toolbarComponent->GetButtons())),
    m_statusBarComponent(new StatusBarComponent(this))
{
    if (!m_editorComponent || !m_toolbarComponent || !m_fileOperations || !m_layoutComponent || !m_statusBarComponent) {
        throw std::runtime_error("Component initialization failed");
    }
    InitializeFrame();
    InitializeEditor();
    SetupLayout();
    BindButtonEvents();
    BindEditorEvents();
    LoadLastFile();
    SetIcon(wxIcon("../assets/icons/logo_hx.png" , wxBITMAP_TYPE_PNG));
}
void MainEditorFrame::InitializeFrame()
{
    CreateStatusBar(3);
    SetDefaultStatusText();
    m_timer.Start(1000);
}
void MainEditorFrame::InitializeEditor()
{
    m_editorComponent->InitializeEditor();
}
void MainEditorFrame::SetupLayout()
{
    m_layoutComponent->SetupLayout();
}
void MainEditorFrame::BindButtonEvents()
{
    std::vector<std::function<void(wxCommandEvent&)>> callbacks =
    {
        [this](wxCommandEvent& event){ this->OnSave(event); },
        [this](wxCommandEvent& event){ this->OnOpen(event); },
        [this](wxCommandEvent& event){ this->OnNewFile(event); },
        [this](wxCommandEvent& event){ this->OnToggleDarkMode(event); },
        [this](wxCommandEvent& event){ this->OnFind(event); },
        [this](wxCommandEvent& event){ this->OnReplace(event); },
        [this](wxCommandEvent& event){ this->OnZoomIn(event); },
        [this](wxCommandEvent& event){ this->OnZoomOut(event); }
    };
    m_toolbarComponent->BindButtonEvents(callbacks);
}
void MainEditorFrame::SetDefaultStatusText()
{
    SetStatusText("Ready", 0);
    SetStatusText("Line: 1, Col: 1", 1);
}
void MainEditorFrame::OnSave(wxCommandEvent &event)
{
    if (!m_fileOperations) {
        throw std::runtime_error("File operations component is uninitialized");
    }
    m_fileOperations->OnSave(event);
}
void MainEditorFrame::OnOpen(wxCommandEvent &event)
{
    m_fileOperations->OnOpen(event);
}
void MainEditorFrame::OnNewFile(wxCommandEvent& event)
{
    m_fileOperations->OnNewFile(event);
}
void MainEditorFrame::OnToggleDarkMode(wxCommandEvent& event)
{
    static bool isDarkMode = false;
    ApplyEditorStyles(isDarkMode);
    isDarkMode = !isDarkMode;
}
void MainEditorFrame::ApplyEditorStyles(bool isDarkMode)
{
    Constants::ThemeSettings theme = Constants::GetThemeSettings(isDarkMode);
    auto* editor = m_editorComponent->GetEditor();

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
void MainEditorFrame::OnFind(wxCommandEvent& event)
{
    auto* editor = m_editorComponent->GetEditor();
    auto* findDialog = new FindDialog(this, editor);
    findDialog->Show(true);
}
void MainEditorFrame::OnReplace(wxCommandEvent& event)
{
    wxString findTerm = wxGetTextFromUser(_("Enter text to find:"), _("Replace"));
    wxString replaceTerm = wxGetTextFromUser(_("Enter replacement text:"), _("Replace With"));
    if(!findTerm.IsEmpty() && !replaceTerm.IsEmpty())
    {
        int start = 0;
        auto* editor = m_editorComponent->GetEditor();
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
void MainEditorFrame::OnEditorUpdate(wxCommandEvent& event)
{
    m_editorComponent->OnEditorUpdate(event);
}
void MainEditorFrame::OnTimer(wxTimerEvent& event)
{
    wxDateTime now = wxDateTime::Now();
    wxString timeString = now.Format("%H:%M:%S");
    SetStatusText(timeString, 2);
}
void MainEditorFrame::OnZoomIn(wxCommandEvent& event)
{
    auto* editor = m_editorComponent->GetEditor();
    int currentZoom = editor->GetZoom();
    editor->SetZoom(currentZoom + ZOOM_INCREMENT);
}
void MainEditorFrame::OnZoomOut(wxCommandEvent& event)
{
    auto* editor = m_editorComponent->GetEditor();
    int currentZoom = editor->GetZoom();
    editor->SetZoom(currentZoom - ZOOM_INCREMENT);
}
void MainEditorFrame::SaveLastFilePath(const wxString &path)
{
    wxFile file("last_file_path.txt", wxFile::write);
    file.Write(path);
    file.Close();
}
wxString MainEditorFrame::LoadLastFilePath()
{
    wxString lastPath;
    wxFile file("last_file_path.txt", wxFile::read);
    if(file.IsOpened())
    {
        file.ReadAll(&lastPath);
    }
    file.Close();
    return lastPath;
}
void MainEditorFrame::OnMarginLeftDown(wxMouseEvent& event)
{
    m_editorComponent->OnMarginLeftDown(event);
}
void MainEditorFrame::OnMarginLeftUp(wxMouseEvent& event)
{
    m_editorComponent->OnMarginLeftUp(event);
}
void MainEditorFrame::OnMarginMotion(wxMouseEvent& event)
{
    m_editorComponent->OnMarginMotion(event);
}
void MainEditorFrame::BindEditorEvents()
{
    m_editorComponent->BindEditorEvents();
}
void MainEditorFrame::LoadLastFile()
{
    wxString lastFilePath = LoadLastFilePath();
    auto *editor = m_editorComponent->GetEditor();
    if(wxFileExists(lastFilePath) && editor)
    {
        editor->LoadFile(lastFilePath);
        SetStatusText(wxFileNameFromPath(lastFilePath), 0);
    }
}
wxBEGIN_EVENT_TABLE(MainEditorFrame, wxFrame)
                EVT_TIMER(wxID_ANY, MainEditorFrame::OnTimer)
                EVT_LEFT_DOWN(MainEditorFrame::OnMarginLeftDown)
                EVT_LEFT_UP(MainEditorFrame::OnMarginLeftUp)
                EVT_MOTION(MainEditorFrame::OnMarginMotion)
wxEND_EVENT_TABLE()