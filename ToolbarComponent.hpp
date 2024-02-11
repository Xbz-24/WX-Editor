/**
 * @file ToolbarComponent.hpp
 * @brief This class is responsible for managing the toolbar of the editor.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato German Chavez Chicoma
 */
#ifndef EDITOR_TOOLBARCOMPONENT_HPP
#define EDITOR_TOOLBARCOMPONENT_HPP
#include <wx/window.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <functional>
#include <vector>

class ToolbarComponent
{
public:
    ToolbarComponent(wxWindow* parent);
    void InitializeButtons();
    ~ToolbarComponent();
private:
    wxWindow* m_parent;
    wxButton *saveButton, *openButton, *newFileButton, *toggleDarkModeButton;
    wxButton *findButton, *replaceButton, *zoomInButton, *zoomOutButton;
public:
    std::vector<wxButton *> GetButtons();
    void BindButtonEvents(const std::vector<std::function<void(wxCommandEvent&)>>& callbacks);
};
#endif //EDITOR_TOOLBARCOMPONENT_HPP