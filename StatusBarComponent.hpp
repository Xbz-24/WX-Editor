/**
 * @file FileManagerComponent.hpp
 * @brief This class is responsible for managing the file system.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato German Chavez Chicoma
 */
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