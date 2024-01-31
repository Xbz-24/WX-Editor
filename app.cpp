//
// Created by daily on 1/30/24.
//

#include "app.hpp"
#include "MainEditorFrame.hpp"

bool app::OnInit()
{
    wxFrame *frame = new MainEditorFrame("wx-editor", wxPoint(50, 50), wxSize(450, 340));
    frame->Maximize();
    frame->Show(true);
    return true;
}
wxIMPLEMENT_APP(app);
