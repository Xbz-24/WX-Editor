/**
 * @file LayoutComponent.cpp
 * @brief This class is responsible for setting up the layout of the editor.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato German Chavez Chicoma
 */
#include "LayoutComponent.hpp"

LayoutComponent::LayoutComponent(wxWindow *parent, EditorComponent * editorComponent, const std::vector<wxButton *> &buttons)
:   m_parent(parent),
    m_editorComponent(editorComponent),
    m_buttons(buttons)
{
    setButtons(buttons);
    //TODO: Validate the editorComponent and button parameters to avoid null pointers before setting up the layout.
}
void LayoutComponent::SetupLayout()
{
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    auto* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);

    //FIXME: Add a null check for m_buttons to ensure that it is not null before iterating over it.
    for(auto* button : m_buttons)
    {
        if(button == nullptr)
        {
            //FIXME: Implement better error handling strategy than throwing a runtime error.
            throw std::runtime_error("Button is null, LayoutComponent.cpp");
        }
        toolbarSizer->Add(button,0,wxALL,5);
        //TODO: Implement a flexible toolbar layout that adapts to window resizing.
    }


    mainSizer->Add(toolbarSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    auto* editorSizer = new wxBoxSizer(wxHORIZONTAL);
    auto* fileSelectionCtrl = new wxGenericDirCtrl(m_parent, wxID_ANY);
    editorSizer->Add(fileSelectionCtrl, 1, wxEXPAND | wxALL, 0);
    //TODO: implement a more advanced directory control that allows for file selection and browsing, maybe a custom implementation.

    if(m_editorComponent->GetEditor() == nullptr)
    {
        //FIXME: implement a more graceful way to handle a null editor component, possibly with user feedback or a default editor.
        throw std::runtime_error("Editor is null");
    }
    editorSizer->Add(m_editorComponent->GetEditor(), 7,wxEXPAND,0);
    mainSizer->Add(editorSizer, 5, wxEXPAND, 0);
    //TODO: make the terminalCtrl a separate component
    //TODO: make terminalCtrl be a entire shell/terminal emulator
    auto* terminalCtrl = new wxTextCtrl(m_parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    mainSizer->Add(terminalCtrl, 1, wxEXPAND | wxALL, 0);
    //TODO: Research and integrate a more advanced terminal emulator library for terminalCtrl
    m_parent->SetSizer(mainSizer);
    m_parent->Layout();
    //TODO: Add code to save the layout state on application close and restore it on application start.
}
void LayoutComponent::setButtons(const std::vector<wxButton *> &buttons)
{
    //TODO: Implement a check to validate the button objects in the buttons array.
    m_buttons = buttons;
}
LayoutComponent::~LayoutComponent()
{
    //TODO: Ensure proper cleanup of dynamically allocated resources if any.
}