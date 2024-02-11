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
}
void LayoutComponent::SetupLayout()
{
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    auto* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);

    for(auto* button : m_buttons)
    {
        if(button == nullptr)
        {
            throw std::runtime_error("Button is null, LayoutComponent.cpp");
        }
        toolbarSizer->Add(button,0,wxALL,5);
    }


    mainSizer->Add(toolbarSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    auto* editorSizer = new wxBoxSizer(wxHORIZONTAL);
    auto* fileSelectionCtrl = new wxGenericDirCtrl(m_parent, wxID_ANY);

    editorSizer->Add(fileSelectionCtrl, 1, wxEXPAND | wxALL, 0);

    if(m_editorComponent->GetEditor() == nullptr)
    {
         throw std::runtime_error("Editor is null");
    }
    editorSizer->Add(m_editorComponent->GetEditor(), 3,wxEXPAND,0);
    mainSizer->Add(editorSizer, 2, wxEXPAND, 0);
    //TODO: make the terminalCtrl a separate component
    //TODO: make terminalCtrl be a entire shell/terminal emulator
    auto* terminalCtrl = new wxTextCtrl(m_parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    mainSizer->Add(terminalCtrl, 1, wxEXPAND | wxALL, 0);
    m_parent->SetSizer(mainSizer);
    m_parent->Layout();
}
void LayoutComponent::setButtons(const std::vector<wxButton *> &buttons)
{
    m_buttons = buttons;
}
LayoutComponent::~LayoutComponent()
{
}