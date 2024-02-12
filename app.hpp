/**
 * @file app.hpp
 * @brief This class is responsible for initializing the application.
 * @version 0.1
 * @date 2024-01-30
 * @Author Renato Chavez Chicoma German
 */
#ifndef EDITOR_APP_HPP
#define EDITOR_APP_HPP
#include <wx/wx.h>
//TODO: Implement Singleton Design Pattern for the app class
class app : public wxApp
{
public:
    //FIXME: proper memory management (smart pointers or destructor)
    //TODO: Implement error handling in OnInit, logging errors or showing error messages to the user if initialization fails
    bool OnInit() override;
};
#endif //EDITOR_APP_HPP