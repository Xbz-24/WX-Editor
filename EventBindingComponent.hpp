//
// Created by daily on 1/31/24.
//

#ifndef EDITOR_EVENTBINDINGCOMPONENT_HPP
#define EDITOR_EVENTBINDINGCOMPONENT_HPP

#include <wx/wx.h>
#include "EditorComponent.hpp"

class EventBindingComponent
{
public:
    EventBindingComponent(EditorComponent* editorComponent, wxWindow* parent);
    void BindEditorEvents();
    ~EventBindingComponent();
private:
    EditorComponent* m_editorComponent;
    wxWindow* m_parent;
};


#endif //EDITOR_EVENTBINDINGCOMPONENT_HPP
