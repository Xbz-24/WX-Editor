//
// Created by daily on 1/30/24.
//

#include "FileOperations.hpp"

void FileOperations::SaveLastFilePath(const wxString& path)
{
    // ... save last file path logic ...
}

wxString FileOperations::LoadLastFilePath()
{
    // ... load last file path logic ...
}

void FileOperations::OnSave(wxCommandEvent& event, wxStyledTextCtrl* editor)
{
    // ... save file logic ...
}

void FileOperations::OnOpen(wxCommandEvent& event, wxStyledTextCtrl* editor)
{
    // ... open file logic ...
}

void FileOperations::OnNewFile(wxCommandEvent& event, wxStyledTextCtrl* editor)
{
    // ... new file logic ...
}
