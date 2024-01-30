//
// Created by daily on 1/30/24.
//

#ifndef EDITOR_TOOLBARCOMPONENT_HPP
#define EDITOR_TOOLBARCOMPONENT_HPP


#include <wx/window.h>
#include <wx/button.h>

class ToolbarComponent
{
public:
    ToolbarComponent(wxWindow* parent);
    void createButtons(wxWindow* parent);
    ~ToolbarComponent();

private:
    wxButton *saveButton, *openButton, *newFileButton, *toggleDarkModeButton;
};


#endif //EDITOR_TOOLBARCOMPONENT_HPP
