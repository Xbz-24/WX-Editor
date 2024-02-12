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

//TODO: Document the overall purpose and functionality of this class.
class EditorComponent
{
public:
    //TODO: Add detailed comments for the constructor parameters explaining their purpose and usage.
    EditorComponent(wxWindow *parent, wxFrame* frame);
    //TODO: Document the purpose of the isDarkMode parameter and how it affects the editor's appearance.
    void ApplyStyles(bool isDarkMode);
    //TODO: Provide details on what the EditorUpdate method is handling, such as cursor position updates, etc.
    void OnEditorUpdate(wxCommandEvent &event);
    //TODO: Elaborate on the use cases for exposing the wxStyledTextCtrl instance.
    [[nodiscard]] wxStyledTextCtrl *GetEditor() const;
    //TODO: Describe the types of events being bound in this method.
    void BindEditorEvents();
    //TODO: Explain the purpose of these event handlers, particularly the editor margin interactions.
    void OnMarginMotion(wxMouseEvent &event);
    //TODO: Explain the purpose of these event handlers, particularly the editor margin interactions.
    void OnMarginLeftUp(wxMouseEvent &event);
    //TODO: Explain the purpose of these event handlers, particularly the editor margin interactions.
    void OnMarginLeftDown(wxMouseEvent &event);
private:
    //TODO: Evaluate whether additional private methods are needed for better code organization and readability.
    wxStyledTextCtrl *m_editor;
    bool m_draggingMargin = false;
    wxFrame* m_frame;
public:
    //TODO: Provide a brief description of each setup method and its impact on the editor component.
    void InitializeEditor();
    void SetupEditorStyles();
    void SetupEditorMargins();
    void SetupEditorAutoCompletion();
};
#endif //EDITOR_EDITORCOMPONENT_HPP