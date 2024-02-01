//
// Created by daily on 1/31/24.
//

#ifndef EDITOR_LAYOUTCOMPONENT_HPP
#define EDITOR_LAYOUTCOMPONENT_HPP

#include <wx/wx.h>
#include "EditorComponent.hpp"
#include "ToolbarComponent.hpp"

class LayoutComponent {

public:
    LayoutComponent(wxWindow* parent, EditorComponent* editorComponent, const std::vector<wxButton*>& buttons);
    void SetupLayout();
    void setButtons(const std::vector<wxButton*>& buttons);
    ~LayoutComponent();
private:
    wxWindow* m_parent;
    EditorComponent* m_editorComponent;
    std::vector<wxButton*> m_buttons;
};


#endif //EDITOR_LAYOUTCOMPONENT_HPP
