/**
 * @file app.cpp
 * @brief This class is responsible for initializing the application.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato German Chavez Chicoma
 */
//TODO: Add detailed comments explaining the logic and flow of file operations, especially for complex parts.
#include "FileOperations.hpp"
//TODO: Add unit tests for new file operation methods
//TODO: Implement more robust error handling in file parsing
//TODO: Validate the handling of edge cases in file operations (e.g. empty files, large files, permissions, non-existent paths, etc.)
//TODO: Evaluate and refactor to adhere to MVC/MVVM patterns for better separation of concerns.
//TODO: Investigate the use of external libraries to enhance file operations (e.g BOOST for file system handling).
 FileOperations::FileOperations(wxStyledTextCtrl* editor, wxFrame* frame)
    : m_editor(editor), m_frame(frame)
{
    //TODO: add null checks and appropriate for constructor parameters
    if (!m_editor || !m_frame)
    {
        throw std::runtime_error("Editor or frame is uninitialized in FileOperations");
    }
    //TODO: Unsaved Changes Prompt, Refine the logic for prompting the user to save unsaved changes, ensuring all scenarios are covered.
}
//TODO: Remove unused code
void FileOperations::BindButtonEvents()
{
    m_toolbarComponent->GetButtons()[0]->Bind(wxEVT_BUTTON, &FileOperations::OnSave, this);
    m_toolbarComponent->GetButtons()[1]->Bind(wxEVT_BUTTON, &FileOperations::OnOpen, this);
    m_toolbarComponent->GetButtons()[2]->Bind(wxEVT_BUTTON, &FileOperations::OnNewFile, this);
}
//TODO: Implement logic to save the last file path
void FileOperations::SaveLastFilePath(const wxString& path)
{
     //FIXME: Implement logic to save the last file path
}
//TODO: Remove unused code
wxString FileOperations::LoadLastFilePath()
{
    return "path";
}
//TODO: Implement functionality to check if the file is already saved and skip the save dialog if no changes were made.
void FileOperations::OnSave(wxCommandEvent& event)
{
    if (!m_editor)
    {
        //TODO: Enhance error handling to cover failed operations and unexpected scenarios
        throw std::runtime_error("Editor is uninitialized");
    }
    //TODO: use constant for file extensions and dialog properties
    wxFileDialog saveFileDialog
    (
    //TODO: Use constant for the title
    m_frame, _("Save File"), "", "",
    //TODO: Use constant for the file types
    "Text Files (*.txt)|*.txt|All files (*.*)|*.*",
    wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );
    if(saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    if(!m_editor->SaveFile(saveFileDialog.GetPath()))
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
    }
    wxFileName fileName(saveFileDialog.GetPath());
    m_frame->SetStatusText(fileName.GetFullName(), 0);
    SaveLastFilePath(saveFileDialog.GetPath());
}
//TODO: Enhance error handling to cover failed operations and unexpected scenarios
void FileOperations::OnOpen(wxCommandEvent& event)
{
    // TODO: Optimize file loading process for larger files
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
    m_editor->LoadFile(openFileDialog.GetPath());
    wxFileName fileName(openFileDialog.GetPath());
    m_frame->SetStatusText(fileName.GetFullName(), 0);
    SaveLastFilePath(openFileDialog.GetPath());
}
//TODO: Ensure the title and status bar are updated correctly when creating a new file.
void FileOperations::OnNewFile(wxCommandEvent& event)
{
    if (m_editor->GetModify())
    {
        wxMessageDialog confirmDialog
        (
            m_frame, _("Do you want to save changes to the current document?")
            ,_("Confirm"), wxYES_NO | wxCANCEL | wxICON_QUESTION
        );
        int response = confirmDialog.ShowModal();

        if (response == wxID_YES) {
            this->OnSave(event);
        } else if (response == wxID_CANCEL) {
            return;
        }
    }
    m_editor->ClearAll();
    m_editor->EmptyUndoBuffer();
    m_frame->SetTitle("wx-editor - New File");
}