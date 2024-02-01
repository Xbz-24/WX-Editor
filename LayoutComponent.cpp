//
// Created by daily on 1/31/24.
//
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
    auto* vbox = new wxBoxSizer(wxVERTICAL);
    auto* hbox = new wxBoxSizer(wxHORIZONTAL);
    vbox->Add(hbox,0,wxEXPAND | wxALL, 5);
    for(auto* button : m_buttons)
    {
        if(button == nullptr)
        {
            throw std::runtime_error("Button is null, LayoutComponent.cpp");
        }
        hbox->Add(button);
    }
    if(m_editorComponent->GetEditor() == nullptr)
    {
         throw std::runtime_error("Editor is null");
    }
    vbox->Add(m_editorComponent->GetEditor(),1, wxEXPAND);
    m_parent->SetSizer(vbox);
    m_parent->Layout();
}
void LayoutComponent::setButtons(const std::vector<wxButton *> &buttons)
{
    m_buttons = buttons;
}
LayoutComponent::~LayoutComponent()
{
}