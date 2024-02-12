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
    m_timer(this)
{
    //TODO: Refactor this constructor to adhere to SRP by breaking down into smaller methods
    //TODO: break down constructor into smaller methods
    //TODO: Update class and method documentation to reflect recent changes
    //TODO: divide this exception into smaller exceptions
    try
    {
        InitializeComponents();
        InitializeUI();
    }
    catch(const std::exception& e)
    {
        wxMessageBox("Initialization error" + wxString(e.what()), "Error", wxICON_ERROR);
    }
    if (!m_editorComponent || !m_toolbarComponent || !m_fileOperations || !m_layoutComponent || !m_statusBarComponent) {
        //TODO: refactor error handling to avoid throwing raw exceptions
        throw std::runtime_error("Component initialization failed");
    }
    //TODO: Evaluate and improve accessibility features (e.g., screen reader compatibility)
    //FIXME: Implement more robust and fail-safe Initialization for editor, toolbar, file operations, layout, and status bar components.
}
void MainEditorFrame::InitializeComponents()
{
    m_editorComponent = std::make_unique<EditorComponent>(this, this);
    m_toolbarComponent = std::make_unique<ToolbarComponent>(this);
    m_fileOperations = std::make_unique<FileOperations>(m_editorComponent->GetEditor(), this);
    m_layoutComponent = std::make_unique<LayoutComponent>(this, m_editorComponent.get(), m_toolbarComponent->GetButtons());
    m_statusBarComponent = std::make_unique<StatusBarComponent>(this);
}
void MainEditorFrame::InitializeUI()
{
    InitializeFrame();
    InitializeEditor();
    SetupLayout();
    BindButtonEvents();
    BindEditorEvents();
    wxInitAllImageHandlers();
    SetIcon(wxIcon(Constants::MAIN_APP_LOGO_PATH , Constants::MAIN_APP_LOGO_TYPE));
    //TODO: Improve accesibility features (e.g., screen reader compatibility).
}
void MainEditorFrame::SetDefaultStatusText()
{
    SetStatusText(Constants::DEFAULT_STATUS_BAR_READY_FIELD_TEXT, Constants::DEFAULT_STATUS_BAR_READY_FIELD_INDEX);
    SetStatusText(Constants::DEFAULT_STATUS_BAR_LINE_COL_FIELD_TEXT, Constants::DEFAULT_STATUS_BAR_LINE_COL_FIELD_INDEX);
}
void MainEditorFrame::InitializeFrame()
{
    CreateStatusBar(Constants::STATUS_BAR_NUMBER_OF_FIELDS);
    SetDefaultStatusText();
    m_timer.Start(Constants::TIMER_INTERVAL_STATUS_BAR);
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

    if (!m_fileOperations)
    {
        throw std::runtime_error("File operations component is uninitialized");
    }
    std::vector<std::function<void(wxCommandEvent&)>> callbacks =
    {
        //TODO: Consolidate similar event handling methods into a single method to reduce redundancy and improve maintainability.
        [this](wxCommandEvent& event){ m_fileOperations->OnSave(event); },
        [this](wxCommandEvent& event){ m_fileOperations->OnOpen(event); },
        [this](wxCommandEvent& event){ m_fileOperations->OnNewFile(event); },
        [this](wxCommandEvent& event){ this->OnToggleDarkMode(event); },
        [this](wxCommandEvent& event){ this->OnFind(event); },
        [this](wxCommandEvent& event){ this->OnReplace(event); },
        [this](wxCommandEvent& event){ this->OnZoomIn(event); },
        [this](wxCommandEvent& event){ this->OnZoomOut(event); }
    };
    m_toolbarComponent->BindButtonEvents(callbacks);
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
    editor->StyleSetForeground(Constants::C_STRING_STYLE, theme.colorString);
    editor->StyleSetForeground(Constants::C_PREPROCESSOR_STYLE, theme.colorPreprocessor);
    editor->StyleSetForeground(Constants::C_IDENTIFIER_STYLE, theme.colorIdentifier);
    editor->StyleSetForeground(Constants::C_NUMBER_STYLE, theme.colorNumber);
    editor->StyleSetForeground(Constants::C_CHARACTER_STYLE, theme.colorCharacter);
    editor->StyleSetForeground(Constants::C_KEYWORD_STYLE, theme.colorWord);
    editor->StyleSetForeground(Constants::C_EXTRA_KEYWORD_STYLE, theme.colorWord2);
    editor->StyleSetForeground(Constants::C_MULTI_LINED_COMMENT_STYLE, theme.colorComment);
    editor->StyleSetForeground(Constants::C_SINGLE_LINE_COMMENT_STYLE, theme.colorCommentLine);
    editor->StyleSetForeground(Constants::C_COMMENT_DOCUMENTATION_STYLE, theme.colorCommentDoc);
    editor->StyleSetForeground(Constants::C_OPERATOR_STYLE, theme.colorOperator);
    if (Constants::STYLE_BOLD)
    {
        editor->StyleSetBold(Constants::C_KEYWORD_STYLE, true);
        editor->StyleSetBold(Constants::C_EXTRA_KEYWORD_STYLE, true);
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
    m_fileOperations->SaveLastFilePath(path);
}
wxString MainEditorFrame::LoadLastFilePath()
{
    return m_fileOperations->LoadLastFilePath();
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
//TODO: Review event bindings to ensure that all necessary events are covered and properly handled.
wxBEGIN_EVENT_TABLE(MainEditorFrame, wxFrame)
                EVT_TIMER(wxID_ANY, MainEditorFrame::OnTimer)
                EVT_LEFT_DOWN(MainEditorFrame::OnMarginLeftDown)
                EVT_LEFT_UP(MainEditorFrame::OnMarginLeftUp)
                EVT_MOTION(MainEditorFrame::OnMarginMotion)
wxEND_EVENT_TABLE()