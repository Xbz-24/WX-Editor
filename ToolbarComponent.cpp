/**
 * @file ToolbarComponent.hpp
 * @brief This class is responsible for managing the toolbar of the editor.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato German Chavez Chicoma
 */

#include "ToolbarComponent.hpp"
#include "Constants.hpp"

ToolbarComponent::ToolbarComponent(wxWindow *parent)
    : m_parent(parent)
{
    InitializeButtons();
    //TODO: Validate the parent window pointer for null before proceeding.
}
void ToolbarComponent::InitializeButtons()
{
    //TODO: externalize button labels and properties for easy customization and localization.
    //FIXME: Implement more robust error handling for button initialization instead of throwing runtime errors.
    //TODO: Add tooltips to each button for better user accessibility.
    //FIXME: Ensure all buttons are consistently styled and adhere to a unified theme.
    openButton = new wxButton(m_parent, wxID_ANY, Constants::OPEN_BUTTON_LABEL, Constants::OPEN_BUTTON_POSITION, wxDefaultSize);
    //FIXME: Implement more robust error handling for button initialization instead of throwing runtime errors.
    //TODO: Add tooltips to each button for better user accessibility.
    //FIXME: Ensure all buttons are consistently styled and adhere to a unified theme.
    newFileButton = new wxButton(m_parent, wxID_ANY, "New File");
    //FIXME: Implement more robust error handling for button initialization instead of throwing runtime errors.
    //TODO: Add tooltips to each button for better user accessibility.
    //FIXME: Ensure all buttons are consistently styled and adhere to a unified theme.
    replaceButton = new wxButton(m_parent, wxID_ANY, "Replace");
    //FIXME: Implement more robust error handling for button initialization instead of throwing runtime errors.
    //TODO: Add tooltips to each button for better user accessibility.
    //FIXME: Ensure all buttons are consistently styled and adhere to a unified theme.
    zoomInButton = new wxButton(m_parent, wxID_ANY, "+");
    //FIXME: Implement more robust error handling for button initialization instead of throwing runtime errors.
    //TODO: Add tooltips to each button for better user accessibility.
    //FIXME: Ensure all buttons are consistently styled and adhere to a unified theme.
    zoomOutButton = new wxButton(m_parent, wxID_ANY, "-");
    //FIXME: Implement more robust error handling for button initialization instead of throwing runtime errors.
    //TODO: Add tooltips to each button for better user accessibility.
    //FIXME: Ensure all buttons are consistently styled and adhere to a unified theme.
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
    //TODO: Evaluate the layout of buttons to ensure they are responsive and adjust to the toolbar size.
}
std::vector<wxButton*> ToolbarComponent::GetButtons()
{
    //TODO: Review if returning a vector of button pointers is the best approach, consider alternatives for better performance and memory management.
    return std::vector<wxButton*>
    {
        saveButton, openButton, newFileButton, toggleDarkModeButton, findButton, replaceButton, zoomInButton, zoomOutButton
    };
}
void ToolbarComponent::BindButtonEvents(const std::vector<std::function<void(wxCommandEvent&)>>& callbacks)
{
    //TODO: Validate the size of the callbacks vector to ensure it matches the number of buttons.
    //FIXME: Add error handling in case binding of a callback to a button fails.
    saveButton->Bind(wxEVT_BUTTON, callbacks[0]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    openButton->Bind(wxEVT_BUTTON, callbacks[1]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    newFileButton->Bind(wxEVT_BUTTON, callbacks[2]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    toggleDarkModeButton->Bind(wxEVT_BUTTON, callbacks[3]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    findButton->Bind(wxEVT_BUTTON, callbacks[4]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    replaceButton->Bind(wxEVT_BUTTON, callbacks[5]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    zoomInButton->Bind(wxEVT_BUTTON, callbacks[6]);
    //FIXME: Add error handling in case binding of a callback to a button fails.
    zoomOutButton->Bind(wxEVT_BUTTON, callbacks[7]);
    //TODO: Investigate the possibility of dynamically generating button event bindings based on button properties or identifiers.
}
ToolbarComponent::~ToolbarComponent()
{
    //TODO: Ensure proper cleanup and deallocation of button resources if necessary.
}