//
// Created by daily on 1/30/24.
//
#ifndef EDITOR_EDITORCOMPONENT_HPP
#define EDITOR_EDITORCOMPONENT_HPP
#include <wx/stc/stc.h>
#include <wx/frame.h>
#include <wx/event.h>
class EditorComponent
{
public:
    EditorComponent(wxWindow *parent, wxFrame* frame);
    void ApplyStyles(bool isDarkMode);
    void OnEditorUpdate(wxCommandEvent &event);
    wxStyledTextCtrl *GetEditor() const;
    void BindEditorEvents();
    void OnMarginMotion(wxMouseEvent &event);
    void OnMarginLeftUp(wxMouseEvent &event);
    void OnMarginLeftDown(wxMouseEvent &event);
private:
    wxStyledTextCtrl *m_editor;
    bool m_draggingMargin = false;
    wxFrame* m_frame;
public:
    void InitializeEditor();
    void SetupEditorStyles();
    void SetupEditorMargins();
    void SetupEditorAutoCompletion();
};
#endif //EDITOR_EDITORCOMPONENT_HPP