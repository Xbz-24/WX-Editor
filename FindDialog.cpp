//
// Created by daily on 22-12-23.
//
#include "FindDialog.hpp"
FindDialog::FindDialog(wxWindow* parent, wxStyledTextCtrl* editor):
    wxDialog(parent, wxID_ANY, "Find", wxDefaultPosition, wxDefaultSize),
    m_editor(editor)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    m_findTextCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(m_findTextCtrl, 0, wxEXPAND | wxALL, 5);
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
    wxString findTerm = m_findTextCtrl->GetValue();
    if(findTerm != m_lastFindTerm)
    {
        m_lastFindTerm = findTerm;
        m_lastFindPos = 0;
    }
    if(!findTerm.IsEmpty())
    {
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
            wxMessageBox(_("Specified text not found."), _("Find"), wxOK | wxICON_INFORMATION);
        }
    }
}
void FindDialog::OnFindPrevious(wxCommandEvent& event)
{
    wxString findTerm = m_findTextCtrl->GetValue();
    if(findTerm != m_lastFindTerm)
    {
        m_lastFindTerm = findTerm;
        m_lastFindPos = m_editor->GetLength();
    }
    if(!findTerm.IsEmpty())
    {
        m_editor->SetTargetStart(0);
        m_editor->SetTargetEnd(m_lastFindPos);
        m_editor->SetSearchFlags(wxSTC_FIND_MATCHCASE);

        int position = m_editor->SearchInTarget(findTerm);

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
    this->Destroy();
}