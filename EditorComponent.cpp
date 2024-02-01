//
// Created by daily on 1/30/24.
//

#include "EditorComponent.hpp"
#include "constants.hpp"

EditorComponent::EditorComponent(wxWindow *parent, wxFrame* frame)
: m_editor(new wxStyledTextCtrl(parent, wxID_ANY)),
    m_frame(frame)
{

}

void EditorComponent::SetupEditorStyles()
{
    m_editor->SetLexer(Constants::LEXER_CPP);
    m_editor->StyleSetForeground(wxSTC_C_STRING, Constants::COLOR_STRING);
    m_editor->StyleSetForeground(wxSTC_C_PREPROCESSOR, Constants::COLOR_PREPROCESSOR);
    m_editor->StyleSetForeground(wxSTC_C_IDENTIFIER, Constants::COLOR_IDENTIFIER);
    m_editor->StyleSetForeground(wxSTC_C_NUMBER, Constants::COLOR_NUMBER);
    m_editor->StyleSetForeground(wxSTC_C_CHARACTER, Constants::COLOR_CHARACTER);
    m_editor->StyleSetForeground(wxSTC_C_WORD, Constants::COLOR_WORD);
    m_editor->StyleSetForeground(wxSTC_C_WORD2, Constants::COLOR_WORD2);
    m_editor->StyleSetForeground(wxSTC_C_COMMENT, Constants::COLOR_COMMENT);
    m_editor->StyleSetForeground(wxSTC_C_COMMENTLINE, Constants::COLOR_COMMENT_LINE);
    m_editor->StyleSetForeground(wxSTC_C_COMMENTDOC, Constants::COLOR_COMMENT_DOC);
    m_editor->StyleSetForeground(wxSTC_C_OPERATOR, Constants::COLOR_OPERATOR);
    m_editor->StyleSetBold(wxSTC_C_WORD, Constants::STYLE_BOLD);
    m_editor->StyleSetBold(wxSTC_C_WORD2, Constants::STYLE_BOLD);
    m_editor->StyleSetBold(wxSTC_C_COMMENTDOC, Constants::STYLE_BOLD);
    m_editor->SetKeyWords(0,Constants::EDITOR_KEYWORDS);
}
void EditorComponent::SetupEditorMargins() {
    m_editor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_editor->SetMarginWidth(0, 150);
    m_editor->SetMarginSensitive(1, true);
    m_editor->SetMarginType(1, Constants::MARGIN_SYMBOL_TYPE);
    m_editor->SetMarginWidth(1, Constants::MARGIN_WIDTH);
    m_editor->SetMarginSensitive(1, true);
    m_editor->MarkerDefine(Constants::MARKER_FOLDER, wxSTC_MARK_BOXPLUS);
    m_editor->MarkerDefine(Constants::MARKER_FOLDER_OPEN, wxSTC_MARK_BOXMINUS);
    m_editor->SetProperty("fold", "1");
    m_editor->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

}
void EditorComponent::SetupEditorAutoCompletion()
{
    m_editor->AutoCompSetSeparator(' ');
    m_editor->AutoCompSetIgnoreCase(true);
    m_editor->AutoCompSetAutoHide(false);
    m_editor->AutoCompSetDropRestOfWord(true);
    m_editor->AutoCompShow(0, Constants::AUTO_COMP_KEYWORDS);
}
void EditorComponent::InitializeEditor()
{
    m_editor->SetZoom(100);
    SetupEditorStyles();
    SetupEditorMargins();
    SetupEditorAutoCompletion();
}
void EditorComponent::BindEditorEvents()
{
    m_editor->Bind(wxEVT_STC_UPDATEUI, &EditorComponent::OnEditorUpdate, this);
    m_editor->Bind(wxEVT_LEFT_DOWN, &EditorComponent::OnMarginLeftDown, this);
    m_editor->Bind(wxEVT_LEFT_UP, &EditorComponent::OnMarginLeftUp, this);
    m_editor->Bind(wxEVT_MOTION, &EditorComponent::OnMarginMotion, this);
}
void EditorComponent::ApplyStyles(bool isDarkMode)
{

}
void EditorComponent::OnEditorUpdate(wxCommandEvent &event)
{
    int line = m_editor->GetCurrentLine() + 1;
    int col = m_editor->GetColumn(m_editor->GetCurrentPos() + 1);
    wxString status;
    status << "Line: " << line << ", Col: " << col;
    m_frame->SetStatusText(status, 1);
}
void EditorComponent::OnMarginLeftDown(wxMouseEvent& event)
{
    int x = event.GetX();
    int marginWidth = m_editor->GetMarginWidth(0);
    if (!m_draggingMargin && x >= marginWidth - 12 && x <= marginWidth + 12)
    {
        m_draggingMargin = true;
        if (wxWindow::GetCapture() != m_editor)
        {
            m_editor->CaptureMouse();
        }
        m_editor->SetCursor(wxCursor(wxCURSOR_SIZEWE));
    }
    event.Skip();
}
void EditorComponent::OnMarginMotion(wxMouseEvent& event)
{
    int x = event.GetX();
    int marginWidth = m_editor->GetMarginWidth(0);
    if (x >= marginWidth - 12 && x <= marginWidth + 12)
    {
        m_editor->SetCursor(wxCursor(wxCURSOR_SIZEWE));
    }
    else
    {
        m_editor->SetCursor(wxNullCursor);
    }
    if (m_draggingMargin && event.Dragging())
    {
        int newWidth = std::max(0, x);
        m_editor->SetMarginWidth(0, newWidth);
    }
    event.Skip();
}
void EditorComponent::OnMarginLeftUp(wxMouseEvent& event)
{
    if(m_draggingMargin){
        m_draggingMargin = false;
        if(m_editor->HasCapture())
        {
            m_editor->ReleaseMouse();
        }
        m_editor->SetCursor(wxNullCursor);
    }
    event.Skip();
}
wxStyledTextCtrl *EditorComponent::GetEditor() const
{
    return m_editor;
}