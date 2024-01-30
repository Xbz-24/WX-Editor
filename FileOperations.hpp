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
    static void SaveLastFilePath(const wxString& path);
    static wxString LoadLastFilePath();
    static void OnSave(wxCommandEvent& event, wxStyledTextCtrl* editor);
    static void OnOpen(wxCommandEvent& event, wxStyledTextCtrl* editor);
    static void OnNewFile(wxCommandEvent& event, wxStyledTextCtrl* editor);
};



#endif //EDITOR_FILEOPERATIONS_HPP
