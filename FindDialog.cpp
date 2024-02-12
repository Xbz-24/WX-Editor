/**
 * @file FindDialog.cpp
 * @brief This class is responsible for finding text in the editor.
 * @version 0.1
 * @date 2023-12-23
 * @Author Renato German Chavez Chicoma
 */
#include "FindDialog.hpp"
FindDialog::FindDialog(wxWindow* parent, wxStyledTextCtrl* editor):
    wxDialog(parent, wxID_ANY, "Find", wxDefaultPosition, wxDefaultSize),
    m_editor(editor)
{
    //TODO: Implement input validation for editor parameter in the constructor, to avoid null pointer exceptions.
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    //TODO: Implement option for customization of dialog title and position
    m_findTextCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(m_findTextCtrl, 0, wxEXPAND | wxALL, 5);
    //FIXME: Review layout and alignment of buttons, consider using a grid sizer for better alignment.
    auto* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    m_prevButton = new wxButton(this, wxID_ANY, "Previous");
    m_nextButton = new wxButton(this, wxID_ANY, "Next");
    m_closeButton = new wxButton(this, wxID_CANCEL, "Close");
    buttonSizer->Add(m_prevButton, 0, wxALL, 5);
    buttonSizer->Add(m_nextButton, 0, wxALL, 5);
    buttonSizer->Add(m_closeButton,0,wxALL,5);
    m_prevButton->Bind(wxEVT_BUTTON, &FindDialog::OnFindPrevious, this);
    m_nextButton->Bind(wxEVT_BUTTON, &FindDialog::OnFindNext, this);
    m_closeButton->Bind(wxEVT_BUTTON, &FindDialog::OnClose, this);
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    this->SetSizer(sizer);
    sizer->Fit(this);
}
void FindDialog::OnFindNext(wxCommandEvent& event)
{
    //FIXME: Handle case sensitivity and whole word matching options in search functionality
    wxString findTerm = m_findTextCtrl->GetValue();
    if(findTerm != m_lastFindTerm)
    {
        m_lastFindTerm = findTerm;
        m_lastFindPos = 0;
    }
    if(!findTerm.IsEmpty())
    {
        //TODO: Add functionality to wrap the search to the beginning of the file when the end is reached.
        m_editor->SetTargetStart(m_lastFindPos);
        m_editor->SetTargetEnd(m_editor->GetLength());
        m_editor->SetSearchFlags(wxSTC_FIND_MATCHCASE);
        int position = m_editor->SearchInTarget(findTerm);
        if(position != -1)
        {
            m_editor->SetSelection(m_editor->GetTargetStart(), m_editor->GetTargetEnd());
            m_editor->EnsureCaretVisible();
            m_lastFindPos = m_editor->GetTargetEnd();
        }
        else
        {
            //TODO: Improve the user feedback for when the search term is not found, disabling buttons or changing focus, etc.
            wxMessageBox(_("Specified text not found."), _("Find"), wxOK | wxICON_INFORMATION);
        }
    }
}
void FindDialog::OnFindPrevious(wxCommandEvent& event)
{
    wxString findTerm = m_findTextCtrl->GetValue();
    //FIXME: Implement reverse search logic to correctly find the previous occurrence of the search term.
    if(findTerm != m_lastFindTerm)
    {
        m_lastFindTerm = findTerm;
        m_lastFindPos = m_editor->GetLength();
        //TODO: Include options for regular expression search and case sensitivity aswell as pattern matching in search criteria.
    }
    if(!findTerm.IsEmpty())
    {
        m_editor->SetTargetStart(0);
        m_editor->SetTargetEnd(m_lastFindPos);
        m_editor->SetSearchFlags(wxSTC_FIND_MATCHCASE);

        int position = m_editor->SearchInTarget(findTerm);

        //FIXME: Optimize search performance for large files, consider using a more efficient search algorithm.
        if(position != -1)
        {
            m_editor->SetSelection(m_editor->GetTargetStart(), m_editor->GetTargetEnd());
            m_editor->EnsureCaretVisible();
            m_lastFindPos = m_editor->GetTargetStart();
        }
        else
        {
            wxMessageBox(_("Specified text not found."),_("Find"), wxOK | wxICON_INFORMATION);
        }
    }
}
void FindDialog::OnClose(wxCommandEvent& event)
{
    //TODO: Ensure that unsaved changes or states are handled properly before closing the dialog.
    this->Destroy();
}