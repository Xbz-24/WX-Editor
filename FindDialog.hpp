//
// Created by daily on 22-12-23.
//

#ifndef EDITOR_FINDDIALOG_HPP
#define EDITOR_FINDDIALOG_HPP
#include <wx/wx.h>
#include <wx/stc/stc.h>

class FindDialog : public wxDialog {
public:
    FindDialog(wxWindow* parent, wxStyledTextCtrl* editor);

private:
    wxStyledTextCtrl* m_editor;
    wxTextCtrl* m_findTextCtrl;
    wxButton* m_prevButton;
    wxButton* m_nextButton;
    wxButton* m_closeButton;
    wxString m_lastFindTerm;
    int m_lastFindPos{};

    void OnFindNext(wxCommandEvent& event);
    void OnFindPrevious(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
};
#endif //EDITOR_FINDDIALOG_HPP
