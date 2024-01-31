//
// Created by daily on 1/30/24.
//

#include <wx/filename.h>
#include "FileOperations.hpp"
#include <wx/filename.h>
#include <wx/wfstream.h>


FileOperations::FileOperations(wxStyledTextCtrl* editor, wxFrame* frame)
    : m_editor(editor), m_frame(frame)
{

}


void FileOperations::SaveLastFilePath(const wxString& path)
{
    // ... save last file path logic ...
}

wxString FileOperations::LoadLastFilePath()
{
    return "path";
}

void FileOperations::OnSave(wxCommandEvent& event, wxStyledTextCtrl* editor)
{
    wxFileDialog saveFileDialog
            (
                    m_frame, _("Save File"), "", "",
                    "Text Files (*.txt)|*.txt|All files (*.*)|*.*",
                    wxFD_SAVE | wxFD_OVERWRITE_PROMPT
            );

    if(saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    if(!editor->SaveFile(saveFileDialog.GetPath()))
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
    }

    wxFileName fileName(saveFileDialog.GetPath());
    m_frame->SetStatusText(fileName.GetFullName(), 0);
    SaveLastFilePath(saveFileDialog.GetPath());
}

void FileOperations::OnOpen(wxCommandEvent& event, wxStyledTextCtrl* editor)
{
    wxFileDialog openFileDialog
            (
                    m_frame, _("Open file"), "", "",
                    "Text Files (*.txt)|*.txt|All files (*.*)|*.*",
                    wxFD_OPEN|wxFD_FILE_MUST_EXIST
            );

    if(openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxFileInputStream input_stream(openFileDialog.GetPath());
    if(!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }
    editor->LoadFile(openFileDialog.GetPath());
    wxFileName fileName(openFileDialog.GetPath());
    m_frame->SetStatusText(fileName.GetFullName(), 0);
    SaveLastFilePath(openFileDialog.GetPath());}

void FileOperations::OnNewFile(wxCommandEvent& event, wxStyledTextCtrl* editor)
{
    // ... new file logic ...
}
