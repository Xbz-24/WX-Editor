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
    //TODO: Validate application prerequisites before launching the main frame.
    try
    {
        //TODO: Implement a configuration system to customize initial window properties (e.g. size, position, etc.).
        wxFrame *frame = new MainEditorFrame("wx-editor", wxPoint(50, 50), wxSize(450, 340));
        //FIXME: make use of smart pointers for frame management to avoid memory leaks.
        frame->Maximize();
        frame->Show(true);
        //TODO: Add logging or debugging information for successful frame initialization.
        return true;
    }
    catch(const std::exception& e)
    {
        //FIXME: Enhance error handling and logging for initialization failures. Show a user-friendly error message.
        std::cout << e.what() << std::endl;
        return false;
    }
    //TODO: Review the application's lifecycle management to ensure graceful shutdown and resource cleanup.
}
//TODO: Document any application-wide settings or initializations done this macro.
wxIMPLEMENT_APP(app);