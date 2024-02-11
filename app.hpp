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

class app : public wxApp
{
public:
    bool OnInit() override;
};
#endif //EDITOR_APP_HPP