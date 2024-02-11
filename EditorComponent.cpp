/**
 * @file EditorComponent.cpp
 * @brief This file contains the implementation of the EditorComponent class
 * @version 0.1
 * @date 2024-01-30
 * @author Renato Chavez Chicoma German
 */
#include "EditorComponent.hpp"
#include "Constants.hpp"

EditorComponent::EditorComponent(wxWindow *parent, wxFrame* frame)
: m_editor(new wxStyledTextCtrl(parent, wxID_ANY)),
    m_frame(frame)
{
}
void EditorComponent::SetupEditorStyles()
{
    m_editor->SetLexer(Constants::LEXER_CPP);
    m_editor->StyleSetForeground(Constants::C_STRING_STYLE, Constants::COLOR_STRING);
    m_editor->StyleSetForeground(Constants::C_PREPROCESSOR_STYLE, Constants::COLOR_PREPROCESSOR);
    m_editor->StyleSetForeground(Constants::C_IDENTIFIER_STYLE, Constants::COLOR_IDENTIFIER);
    m_editor->StyleSetForeground(Constants::C_NUMBER_STYLE, Constants::COLOR_NUMBER);
    m_editor->StyleSetForeground(Constants::C_CHARACTER_STYLE, Constants::COLOR_CHARACTER);
    m_editor->StyleSetForeground(Constants::C_KEYWORD_STYLE, Constants::COLOR_WORD);
    m_editor->StyleSetForeground(Constants::C_EXTRA_KEYWORD_STYLE, Constants::COLOR_WORD2);
    m_editor->StyleSetForeground(Constants::C_MULTI_LINED_COMMENT_STYLE, Constants::COLOR_COMMENT);
    m_editor->StyleSetForeground(Constants::C_SINGLE_LINE_COMMENT_STYLE, Constants::COLOR_COMMENT_LINE);
    m_editor->StyleSetForeground(Constants::C_COMMENT_DOCUMENTATION_STYLE, Constants::COLOR_COMMENT_DOC);
    m_editor->StyleSetForeground(Constants::C_OPERATOR_STYLE, Constants::COLOR_OPERATOR);
    m_editor->StyleSetBold(Constants::C_KEYWORD_STYLE, Constants::STYLE_BOLD);
    m_editor->StyleSetBold(Constants::C_EXTRA_KEYWORD_STYLE, Constants::STYLE_BOLD);
    m_editor->StyleSetBold(Constants::C_COMMENT_DOCUMENTATION_STYLE, Constants::STYLE_BOLD);
    m_editor->SetKeyWords(0,Constants::EDITOR_KEYWORDS);
}
void EditorComponent::SetupEditorMargins()
{
    m_editor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_editor->SetMarginWidth(0, Constants::EDITOR_MARGIN_WIDTH_PIXELS);
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
    m_editor->SetZoom(Constants::ZOOM_LEVEL);
    m_editor->StyleSetFont
    (wxSTC_STYLE_DEFAULT,
     wxFont
         (
         Constants::DEFAULT_EDITOR_FONT_SIZE,
         Constants::DEFAULT_EDITOR_FONT_FAMILY,
         Constants::DEFAULT_EDITOR_FONT_STYLE,
         wxFONTWEIGHT_NORMAL
         )
    );
    SetupEditorStyles();
    SetupEditorMargins();
    SetupEditorAutoCompletion();
}
void EditorComponent::BindEditorEvents()
{
    m_editor->Bind(Constants::EVT_UPDATE_UI, &EditorComponent::OnEditorUpdate, this);
    m_editor->Bind(Constants::EVT_LEFT_DOWN, &EditorComponent::OnMarginLeftDown, this);
    m_editor->Bind(Constants::EVT_LEFT_UP, &EditorComponent::OnMarginLeftUp, this);
    m_editor->Bind(Constants::EVT_MOTION, &EditorComponent::OnMarginMotion, this);
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
    m_frame->SetStatusText(status, Constants::STATUS_BAR_INDEX);
}
void EditorComponent::OnMarginLeftDown(wxMouseEvent& event)
{
    int x = event.GetX();
    int marginWidth = m_editor->GetMarginWidth(0);
    if (!m_draggingMargin && x >= marginWidth - Constants::MARGIN_ADJUSTMENT_RANGE && x <= marginWidth + Constants::MARGIN_ADJUSTMENT_RANGE)
    {
        m_draggingMargin = true;
        if (wxWindow::GetCapture() != m_editor)
        {
            m_editor->CaptureMouse();
        }
        m_editor->SetCursor(Constants::CURSOR_RESIZE);
    }
    event.Skip();
}
void EditorComponent::OnMarginMotion(wxMouseEvent& event)
{
    int x = event.GetX();
    int marginWidth = m_editor->GetMarginWidth(0);
    if (x >= marginWidth - Constants::MARGIN_ADJUSTMENT_RANGE && x <= marginWidth + Constants::MARGIN_ADJUSTMENT_RANGE)
    {
        m_editor->SetCursor(Constants::CURSOR_RESIZE);
    }
    else
    {
        m_editor->SetCursor(Constants::CURSOR_DEFAULT);
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
        m_editor->SetCursor(Constants::CURSOR_DEFAULT);
    }
    event.Skip();
}
wxStyledTextCtrl *EditorComponent::GetEditor() const
{
    return m_editor;
}