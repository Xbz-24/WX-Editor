/**
 * @file EditorComponent.hpp
 * @brief This file contains the declaration of the EditorComponent class
 * @version 0.1
 * @date 2024-01-30
 * @author Renato Chavez Chicoma German
 */
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