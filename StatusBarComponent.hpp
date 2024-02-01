//
// Created by daily on 1/31/24.
//
#ifndef EDITOR_STATUSBARCOMPONENT_HPP
#define EDITOR_STATUSBARCOMPONENT_HPP

#include <wx/wx.h>

class StatusBarComponent
{
public:
    StatusBarComponent(wxWindow* parent);
    void UpdateStatusText(const wxString& text, int field);
    ~StatusBarComponent();
private:
    wxWindow* m_parent;
};
#endif //EDITOR_STATUSBARCOMPONENT_HPP