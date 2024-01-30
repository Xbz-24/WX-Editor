//
// Created by daily on 1/30/24.
//

#include "ToolbarComponent.hpp"

ToolbarComponent::ToolbarComponent(wxWindow *parent) : saveButton(new wxButton(parent, wxID_ANY, "Save")),
                                                        openButton(new wxButton(parent, wxID_ANY, "Open")),
                                                        newFileButton(new wxButton(parent, wxID_ANY, "New File")),
                                                        toggleDarkModeButton(new wxButton(parent, wxID_ANY, "Toggle Dark Mode")) {

}

void ToolbarComponent::createButtons(wxWindow *parent) {

}

ToolbarComponent::~ToolbarComponent() {

}
