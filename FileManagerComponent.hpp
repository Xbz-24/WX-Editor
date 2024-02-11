/**
 * @file FileManagerComponent.hpp
 * @brief This class is responsible for managing the file system.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato German Chavez Chicoma
 */
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