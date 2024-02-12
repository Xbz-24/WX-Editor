/**
 * @file EditorComponent.hpp
 * @brief This file contains the declaration of the EditorComponent class
 *
 * The EditorComponent class is responsible for managing the text editing functionality
 * within the application. It encapsulates all aspects related to the text editor, including
 * styling, event handling, and initialization of editor settings.
 *
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
    /**
     * Constructor for EditorComponent.
     * @param parent The parent window which will contain this component.
     * @param frame The main application frame, used for handling events and updates.
     */
    EditorComponent(wxWindow *parent, wxFrame* frame);
    /**
     * Apply styles to the editor based on the dark mode preference.
     *
     * @param isDarkMode Boolean indicating whether dark mode is enabled.
     */
    void ApplyStyles(bool isDarkMode);
    /**
     * Handles updates to the editor, such as cursor position changes or text modifications.
     *
     * @param event The event object containing information about the editor update.
     */
    void OnEditorUpdate(wxCommandEvent &event);
    /**
     * Provides access to the internal wxStyledTextCtrl instance for direct manipulation or retrieval of information.
     *
     * @return A pointer to the wxStyledTextCtrl instance used by this component.
     */
    [[nodiscard]] wxStyledTextCtrl *GetEditor() const;
    /**
     * Bind events related to the editor, such as text changes, cursor movement, etc.
     */
    void BindEditorEvents();
    /**
     * Handle motion events on the editor margin, typically used for visual feedback or drag operations.
     *
     * @param event The mouse event associated with the margin motion.
     */
    void OnMarginMotion(wxMouseEvent &event);
    /**
     * Handle mouse button up events on the editor margin, usually for completing drag and drop operations.
     *
     * @param event The mouse event associated with the margin button up action.
     */
    void OnMarginLeftUp(wxMouseEvent &event);
    /**
     * Handle mouse button down events on the editor margin, typically for initiating drag and drop operations.
     *
     * @param event The mouse event associated with the margin button down action.
     */
    void OnMarginLeftDown(wxMouseEvent &event);
private:
    //TODO: Evaluate whether additional private methods are needed for better code organization and readability.
    wxStyledTextCtrl *m_editor;
    bool m_draggingMargin = false;
    wxFrame* m_frame;
public:
    /**
     * Initializes the editor with default settings and configurations.
     */
    void InitializeEditor();
    /**
     * Set up the visual styles of the editor, such as font and color settings.
     */
    void SetupEditorStyles();
    /**
     * Configure the editor's margins, including line numbers and markers.
     */
    void SetupEditorMargins();
    /**
     * Initialize and configure the auto-completion feature of the editor.
     */
    void SetupEditorAutoCompletion();
};
#endif //EDITOR_EDITORCOMPONENT_HPP