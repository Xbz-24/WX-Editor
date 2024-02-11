/**
 * @file app.cpp
 * @brief This class is responsible for initializing the application.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato Chavez Chicoma German
 */
#include "app.hpp"
#include "MainEditorFrame.hpp"

bool app::OnInit()
{
    try{
    wxFrame *frame = new MainEditorFrame("wx-editor", wxPoint(50, 50), wxSize(450, 340));
    frame->Maximize();
    frame->Show(true);
    return true;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}
wxIMPLEMENT_APP(app);
