//
// Created by daily on 1/31/24.
//
#ifndef EDITOR_FILEMANAGERCOMPONENT_HPP
#define EDITOR_FILEMANAGERCOMPONENT_HPP
#include <wx/wx.h>
class FileManagerComponent
{
public:
    FileManagerComponent(wxWindow* parent);
    wxString LoadLastFilePath();
    void SaveLastFilePath(const wxString& path);
    ~FileManagerComponent();
private:
    wxWindow* m_parent;
    wxString m_lastFilePath;
};
#endif //EDITOR_FILEMANAGERCOMPONENT_HPP
