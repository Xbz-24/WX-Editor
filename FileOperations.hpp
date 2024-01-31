//
// Created by daily on 1/30/24.
//

#ifndef EDITOR_FILEOPERATIONS_HPP
#define EDITOR_FILEOPERATIONS_HPP


#include <wx/wx.h>
#include <wx/stc/stc.h>
class FileOperations
{
public:
    FileOperations(wxStyledTextCtrl* editor, wxFrame* frame);

    void OnOpen(wxCommandEvent& event, wxStyledTextCtrl* editor);
    void OnSave(wxCommandEvent& event, wxStyledTextCtrl* editor);
    void OnNewFile(wxCommandEvent& event, wxStyledTextCtrl* editor);
    void SaveLastFilePath(const wxString& path);
    wxString LoadLastFilePath();
private:
    wxStyledTextCtrl* m_editor;
    wxFrame* m_frame;
};
#endif //EDITOR_FILEOPERATIONS_HPP