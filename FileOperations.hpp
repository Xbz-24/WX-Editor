/**
 * @file fileOperations.hpp
 * @brief This class is responsible for managing the file system.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato German Chavez Chicoma
 */
#ifndef EDITOR_FILEOPERATIONS_HPP
#define EDITOR_FILEOPERATIONS_HPP

#include <wx/wx.h>
#include <wx/stc/stc.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "ToolbarComponent.hpp"

class FileOperations
{
private:
    const wxString LAST_FILE_PATH = wxFileName(wxStandardPaths::Get().GetUserLocalDataDir()).GetFullPath() + "/last_file_path.txt";
public:
    FileOperations(wxStyledTextCtrl* editor, wxFrame* frame);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnNewFile(wxCommandEvent& event);
    void SaveLastFilePath(const wxString& path);
    wxString LoadLastFilePath();
private:
    wxStyledTextCtrl* m_editor;
    wxFrame* m_frame;
};
#endif //EDITOR_FILEOPERATIONS_HPP