//
// Created by daily on 1/30/24.
//
#ifndef EDITOR_EDITORCOMPONENT_HPP
#define EDITOR_EDITORCOMPONENT_HPP
#include <wx/stc/stc.h>

class EditorComponent
{
public:
    EditorComponent(wxWindow* parent);
    void ApplyStyles(bool isDarkMode);
    void OnEditorUpdate(wxStyledTextEvent& event);
    wxStyledTextCtrl* GetEditor() const;

private:
    wxStyledTextCtrl* m_editor{};
};
#endif //EDITOR_EDITORCOMPONENT_HPP
