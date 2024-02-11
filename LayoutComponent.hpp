/**
 * @file LayoutComponent.hpp
 * @brief This class is responsible for setting up the layout of the editor.
 * @version 0.1
 * @date 2024-01-31
 * @Author Renato German Chavez Chicoma
 */
#ifndef EDITOR_LAYOUTCOMPONENT_HPP
#define EDITOR_LAYOUTCOMPONENT_HPP
#include <wx/wx.h>
#include "EditorComponent.hpp"
#include "ToolbarComponent.hpp"
#include "wx/generic/dirctrlg.h"
class LayoutComponent
{
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