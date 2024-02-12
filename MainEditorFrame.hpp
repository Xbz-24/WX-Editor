/**
 * @file MainEditorFrame.hpp
 * @brief This class is responsible for managing the main frame of the application.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato German Chavez Chicoma
 */
#ifndef EDITOR_MAINEDITORFRAME_HPP
#define EDITOR_MAINEDITORFRAME_HPP
#include <wx/wx.h>
#include <wx/stc/stc.h>
#include <wx/button.h>
#include <wx/wfstream.h>
#include "Constants.hpp"
#include "FindDialog.hpp"
#include <wx/filename.h>
#include <wx/timer.h>
#include <algorithm>
#include "app.hpp"
#include "EditorComponent.hpp"
#include "ToolbarComponent.hpp"
#include "FileOperations.hpp"
#include "LayoutComponent.hpp"
#include "StatusBarComponent.hpp"
#include <wx/icon.h>
#include <filesystem>

class MainEditorFrame : public wxFrame
{
private:
    wxButton *saveButton;
    wxButton *openButton;
    wxButton *newFileButton;
    wxButton *toggleDarkModeButton;
    wxButton *findButton;
    wxButton *replaceButton;
    wxTimer m_timer;
wxDECLARE_EVENT_TABLE();
    wxButton *zoomInButton;
    wxButton *zoomOutButton;
    static const int ZOOM_INCREMENT = 12;
    bool m_draggingMargin = false;
private:
    //TODO: use unique_ptr for m_editorComponent
    EditorComponent* m_editorComponent;
    //TODO: use unique_ptr for m_toolbarComponent
    ToolbarComponent* m_toolbarComponent;
    //TODO: use unique_ptr for m_fileOperations
    FileOperations* m_fileOperations;
    //TODO: use unique_ptr for m_layoutComponent
    LayoutComponent* m_layoutComponent;
    //TODO: use unique_ptr for m_statusBarComponent
    StatusBarComponent* m_statusBarComponent;
public:
    MainEditorFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void OnSave(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnNewFile(wxCommandEvent &event);
    void OnToggleDarkMode(wxCommandEvent &event);
    void ApplyEditorStyles(bool isDarkMode);
    void OnFind(wxCommandEvent& event);
    void OnReplace(wxCommandEvent& event);
    void OnEditorUpdate(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnZoomIn(wxCommandEvent& event);
    void OnZoomOut(wxCommandEvent& event);
    static void SaveLastFilePath(const wxString& path);
    static wxString LoadLastFilePath();
    void OnMarginLeftDown(wxMouseEvent& event);
    void OnMarginLeftUp(wxMouseEvent& event);
    void OnMarginMotion(wxMouseEvent& event);
    void SetDefaultStatusText();
    void InitializeFrame();
    void InitializeButtons();
    void InitializeEditor();
    void SetupLayout();
    void SetupEventBindings();
    void BindButtonEvents();
    void BindEditorEvents();
    void LoadLastFile();
    void SetupEditorStyles();
    void SetupEditorMargins();
    void SetupEditorAutoCompletion();
    void CreateButtons();
    wxFrame *GetFrame();
};
#endif //EDITOR_MAINEDITORFRAME_HPP