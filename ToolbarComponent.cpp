//
// Created by daily on 1/30/24.
//
#include "ToolbarComponent.hpp"
#include "constants.hpp"
ToolbarComponent::ToolbarComponent(wxWindow *parent)
    : m_parent(parent)
{
    InitializeButtons();
}
void ToolbarComponent::InitializeButtons()
{
    openButton = new wxButton(m_parent, wxID_ANY, Constants::OPEN_BUTTON_LABEL, Constants::OPEN_BUTTON_POSITION, wxDefaultSize);
    newFileButton = new wxButton(m_parent, wxID_ANY, "New File");
    replaceButton = new wxButton(m_parent, wxID_ANY, "Replace");
    zoomInButton = new wxButton(m_parent, wxID_ANY, "+");
    zoomOutButton = new wxButton(m_parent, wxID_ANY, "-");
    saveButton = new wxButton(m_parent, wxID_ANY, Constants::SAVE_BUTTON_LABEL, Constants::SAVE_BUTTON_POSITION, wxDefaultSize);
    if(saveButton == nullptr)
    {
        throw std::runtime_error("Save button is null");
    }
    findButton = new wxButton(m_parent, wxID_ANY, "Find");
    if(findButton == nullptr)
    {
        throw std::runtime_error("Find button is null");
    }
    toggleDarkModeButton = new wxButton(m_parent, wxID_ANY, "Toggle Dark Mode");
    if(toggleDarkModeButton == nullptr)
    {
        throw std::runtime_error("Toggle dark mode button is null");
    }
}
std::vector<wxButton*> ToolbarComponent::GetButtons()
{
    return std::vector<wxButton*>
    {
        saveButton, openButton, newFileButton, toggleDarkModeButton, findButton, replaceButton, zoomInButton, zoomOutButton
    };
}
void ToolbarComponent::BindButtonEvents(const std::vector<std::function<void(wxCommandEvent&)>>& callbacks)
{
    saveButton->Bind(wxEVT_BUTTON, callbacks[0]);
    openButton->Bind(wxEVT_BUTTON, callbacks[1]);
    newFileButton->Bind(wxEVT_BUTTON, callbacks[2]);
    toggleDarkModeButton->Bind(wxEVT_BUTTON, callbacks[3]);
    findButton->Bind(wxEVT_BUTTON, callbacks[4]);
    replaceButton->Bind(wxEVT_BUTTON, callbacks[5]);
    zoomInButton->Bind(wxEVT_BUTTON, callbacks[6]);
    zoomOutButton->Bind(wxEVT_BUTTON, callbacks[7]);
}
ToolbarComponent::~ToolbarComponent()
{
}