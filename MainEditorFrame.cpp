/**
 * @file MainEditorFrame.cpp
 * @brief This class is responsible for initializing the main frame of the application.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato German Chavez Chicoma
 */

//TODO: Evaluate and refactor to adhere to MVC/MVVM patterns for better separation of concerns.
#include "MainEditorFrame.hpp"

//TODO: Refactor MainEditorFrame to adhere to the SINGLE RESPONSABILITY PRINCIPLE
//TODO: Implement auto-save functionality
//TODO: Review and update code to meet C++17 standards
MainEditorFrame::MainEditorFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:   wxFrame(nullptr, wxID_ANY, title, pos, size),
    m_timer(this),
    m_editorComponent(new EditorComponent(this, this)),
    m_toolbarComponent(new ToolbarComponent(this)),
    m_fileOperations(new FileOperations(m_editorComponent->GetEditor(), this)),
    m_layoutComponent(new LayoutComponent(this, m_editorComponent, m_toolbarComponent->GetButtons())),
    m_statusBarComponent(new StatusBarComponent(this))
{
    //TODO: Refactor this constructor to adhere to SRP by breaking down into smaller methods
    //TODO: break down constructor into smaller methods
    //TODO: Update class and method documentation to reflect recent changes
    //TODO: divide this exception into smaller exceptions
    if (!m_editorComponent || !m_toolbarComponent || !m_fileOperations || !m_layoutComponent || !m_statusBarComponent) {
        //TODO: refactor error handling to avoid throwing raw exceptions
        throw std::runtime_error("Component initialization failed");
    }
    //TODO: Evaluate and improve accessibility features (e.g., screen reader compatibility)
    //FIXME: Implement more robust and fail-safe Initialization for editor, toolbar, file operations, layout, and status bar components.
    InitializeFrame();
    InitializeEditor();
    SetupLayout();
    BindButtonEvents();
    BindEditorEvents();
    LoadLastFile();
    //TODO: modify to not use static path, but instead use relative path or resource path
    std::cout << "working dir: " << std::filesystem::current_path() << std::endl;
    wxImage::AddHandler(new wxPNGHandler);
    SetIcon(wxIcon("../assets/icons/logo_hx.png" , wxBITMAP_TYPE_PNG));
    //TODO: Improve accesibility features (e.g., screen reader compatibility).
}
//TODO: Use constant for the status bar fields number
void MainEditorFrame::InitializeFrame()
{
    //TODO: use constant for the status bar, NUMBER is the n of fields
    CreateStatusBar(3);
    SetDefaultStatusText();
    //TODO: Use a constant for the timer interval instead of a hard-coded value.
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
//TODO: Refactor to use lambda functions instead of function callbacks
void MainEditorFrame::BindButtonEvents()
{
    //FIXME: consider the use of constants for the callbacks indices or button IDs.
    //TODO: simplify this callbacks by the use of a lambda
    std::vector<std::function<void(wxCommandEvent&)>> callbacks =
    {
        //TODO: Consolidate similar event handling methods into a single method to reduce redundancy and improve maintainability.
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
    //TODO: use constant for the status bar index
    //TODO: use constant for the default status text
    SetStatusText("Ready", 0);
    //TODO: use constant for the status bar index
    //TODO: use constant for the default status text
    SetStatusText("Line: 1, Col: 1", 1);
}
//FIXME: Implement a more comprehensive error handling if the file operations component is uninitialized.
void MainEditorFrame::OnSave(wxCommandEvent &event)
{
    if (!m_fileOperations)
    {
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
//TODO: Refactor this method to adhere to SRP by splitting into smaller methods
void MainEditorFrame::ApplyEditorStyles(bool isDarkMode)
{
    Constants::ThemeSettings theme = Constants::GetThemeSettings(isDarkMode);
    //TODO: apply single responsibility principle
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
    //TODO: Improve user interaction with find/replace dialogs, possibly adding more features like regex search, case sensitivity, etc.
    auto* findDialog = new FindDialog(this, editor);
    findDialog->Show(true);
}
void MainEditorFrame::OnReplace(wxCommandEvent& event)
{
    wxString findTerm = wxGetTextFromUser(_("Enter text to find:"), _("Replace"));
    wxString replaceTerm = wxGetTextFromUser(_("Enter replacement text:"), _("Replace With"));
    //TODO: Improve user interaction with find/replace dialogs, possibly adding more features like regex search, case sensitivity, etc.
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
//TODO: Evaluate if this method is necessary or if the functionality can be handled within the EditorComponent class.
void MainEditorFrame::OnEditorUpdate(wxCommandEvent& event)
{
    //TODO: Remove unused code
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
//TODO: Remove unused code
void MainEditorFrame::SaveLastFilePath(const wxString &path)
{
    //TODO: Modify file path handling to use relative paths or resource paths instead of static paths.
    wxFile file("last_file_path.txt", wxFile::write);
    file.Write(path);
    file.Close();
}
wxString MainEditorFrame::LoadLastFilePath()
{
    wxString lastPath;
    //TODO: Modify file path handling to use relative paths or resource paths instead of static paths.
    wxFile file("last_file_path.txt", wxFile::read);
    if(file.IsOpened())
    {
        file.ReadAll(&lastPath);
    }
    file.Close();
    //TODO: Implement error handling for scenarios where the last file path does not exist or cannot be read/opened.
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
//TODO: Review event bindings to ensure that all necessary events are covered and properly handled.
wxBEGIN_EVENT_TABLE(MainEditorFrame, wxFrame)
                EVT_TIMER(wxID_ANY, MainEditorFrame::OnTimer)
                EVT_LEFT_DOWN(MainEditorFrame::OnMarginLeftDown)
                EVT_LEFT_UP(MainEditorFrame::OnMarginLeftUp)
                EVT_MOTION(MainEditorFrame::OnMarginMotion)
wxEND_EVENT_TABLE()