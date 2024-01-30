//
// Created by daily on 1/30/24.
//

#include "EditorComponent.hpp"


EditorComponent::EditorComponent(wxWindow *parent) : m_editor(new wxStyledTextCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0L, wxEmptyString))
{

}

void EditorComponent::ApplyStyles(bool isDarkMode)
{

}

void EditorComponent::OnEditorUpdate(wxStyledTextEvent &event)
{

}

wxStyledTextCtrl *EditorComponent::GetEditor() const
{
    return m_editor;
}
