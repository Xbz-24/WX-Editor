/**
 * @file EventBindingComponent.hpp
 * @brief This class is responsible for binding events to the editor component.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato Chavez Chicoma German
 */
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