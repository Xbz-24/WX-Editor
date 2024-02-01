//
// Created by daily on 1/30/24.
//

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
