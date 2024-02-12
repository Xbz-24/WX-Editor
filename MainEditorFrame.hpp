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
    wxTimer m_timer;
wxDECLARE_EVENT_TABLE();
    static const int ZOOM_INCREMENT = 12;
private:
    std::unique_ptr<EditorComponent> m_editorComponent;
    std::unique_ptr<ToolbarComponent> m_toolbarComponent;
    std::unique_ptr<FileOperations> m_fileOperations;
    std::unique_ptr<LayoutComponent> m_layoutComponent;
    std::unique_ptr<StatusBarComponent> m_statusBarComponent;
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
    void InitializeEditor();
    void SetupLayout();
    void BindButtonEvents();
    void BindEditorEvents();
    void LoadLastFile();
private:
    void InitializeComponents();
    void InitializeUI();
};
#endif //EDITOR_MAINEDITORFRAME_HPP