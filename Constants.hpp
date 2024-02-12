/**
 * @file constants.hpp
 * @brief This file contains the constants used in the application
 * @version 0.1
 * @date 2023-12-23
 * @author Renato German Chavez Chicoma
 */
#ifndef EDITOR_CONSTANTS_HPP
#define EDITOR_CONSTANTS_HPP
#include <wx/colour.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/stc/stc.h>
namespace Constants
{
    //TODO: Add comments explaining the purpose and usage context of each group of constants.
    constexpr int LEXER_CPP = wxSTC_LEX_CPP;
    //TODO: Define a structured approach or naming convention for color constants.
    //TODO: Add more color constants for extending theme support.
    const wxColour COLOR_STRING(150, 0 ,0);
    const wxColour COLOR_PREPROCESSOR(165,105,0);
    const wxColour COLOR_IDENTIFIER(40,0,60);
    const wxColour COLOR_NUMBER(0,150,0);
    const wxColour COLOR_CHARACTER(150,0,0);
    const wxColour COLOR_WORD(0,0,150);
    const wxColour COLOR_WORD2(0,150,0);
    const wxColour COLOR_COMMENT(150,150,150);
    const wxColour COLOR_COMMENT_LINE(150, 150, 150);
    const wxColour COLOR_COMMENT_DOC(150, 150, 150);
    const wxColour COLOR_OPERATOR(0,0,200);
    const wxString EDITOR_KEYWORDS = "return int float double char if else while for break continue switch case default";
    const wxString AUTO_COMP_KEYWORDS = "int char float double";
    constexpr bool STYLE_BOLD = true;
    constexpr int MARGIN_NUMBER_TYPE = wxSTC_MARGIN_NUMBER;
    constexpr int MARGIN_SYMBOL_TYPE = wxSTC_MARGIN_SYMBOL;
    constexpr int MARGIN_WIDTH = 16;
    constexpr int MARKER_FOLDER = wxSTC_MARKNUM_FOLDER;
    constexpr int MARKER_FOLDER_OPEN = wxSTC_MARKNUM_FOLDEROPEN;
    const wxPoint SAVE_BUTTON_POSITION(10,300);
    const wxPoint OPEN_BUTTON_POSITION(100,300);
    const wxString SAVE_BUTTON_LABEL = "Save";
    const wxString OPEN_BUTTON_LABEL = "Open";
    constexpr int ZOOM_LEVEL = 100;
    constexpr int EDITOR_MARGIN_WIDTH_PIXELS = 150;
    constexpr int MARGIN_ADJUSTMENT_RANGE = 12;
    constexpr int C_STRING_STYLE = wxSTC_C_STRING;
    constexpr int C_PREPROCESSOR_STYLE = wxSTC_C_PREPROCESSOR;
    constexpr int C_IDENTIFIER_STYLE = wxSTC_C_IDENTIFIER;
    constexpr int C_NUMBER_STYLE = wxSTC_C_NUMBER;
    constexpr int C_CHARACTER_STYLE = wxSTC_C_CHARACTER;
    constexpr int C_KEYWORD_STYLE = wxSTC_C_WORD;
    constexpr int C_EXTRA_KEYWORD_STYLE = wxSTC_C_WORD2;
    constexpr int C_MULTI_LINED_COMMENT_STYLE = wxSTC_C_COMMENT;
    constexpr int C_SINGLE_LINE_COMMENT_STYLE = wxSTC_C_COMMENTLINE;
    constexpr int C_COMMENT_DOCUMENTATION_STYLE = wxSTC_C_COMMENTDOC;
    constexpr int C_OPERATOR_STYLE = wxSTC_C_OPERATOR;
    const wxEventTypeTag EVT_UPDATE_UI = wxEVT_STC_UPDATEUI;
    const wxEventTypeTag EVT_LEFT_DOWN = wxEVT_LEFT_DOWN;
    const wxEventTypeTag EVT_LEFT_UP = wxEVT_LEFT_UP;
    const wxEventTypeTag EVT_MOTION = wxEVT_MOTION;
    const wxCursor CURSOR_RESIZE = wxCursor(wxCURSOR_SIZEWE);
    const wxCursor CURSOR_DEFAULT = wxCursor(wxCURSOR_DEFAULT);
    constexpr int STATUS_BAR_INDEX = 1;
    constexpr int DEFAULT_EDITOR_FONT_SIZE = 10;
    constexpr wxFontFamily DEFAULT_EDITOR_FONT_FAMILY = wxFONTFAMILY_MODERN;
    constexpr wxFontStyle DEFAULT_EDITOR_FONT_STYLE = wxFONTSTYLE_NORMAL;
    constexpr wxFontWeight DEFAULT_EDITOR_FONT_WEIGHT = wxFONTWEIGHT_NORMAL;
    constexpr int DEFAULT_EDITOR_FONT_UNDERLINE = 0;
    const wxString DEFAULT_EDITOR_FONT_FACE = wxString("Consolas");
    constexpr int STATUS_BAR_NUMBER_OF_FIELDS = 3;
    constexpr int TIMER_INTERVAL_STATUS_BAR = 1000;
    const std::string DEFAULT_STATUS_BAR_READY_FIELD_TEXT = "Ready";
    constexpr int DEFAULT_STATUS_BAR_READY_FIELD_INDEX = 0;
    const std::string DEFAULT_STATUS_BAR_LINE_COL_FIELD_TEXT = "Line: 1, Col: 1";
    constexpr int DEFAULT_STATUS_BAR_LINE_COL_FIELD_INDEX = 1;
    const std::string MAIN_APP_LOGO_PATH = "../assets/icons/logo_hx.png";
    const wxBitmapType MAIN_APP_LOGO_TYPE = wxBITMAP_TYPE_PNG;
    //TODO: Investigate and implement the possibility of making theme settings dynamic and customizable with the use of a configuration file or settings dialog.
    namespace LightTheme
    {
        const wxColour COLOR_STRING(150, 0, 0);
        const wxColour COLOR_PREPROCESSOR(165, 105, 0);
        const wxColour COLOR_IDENTIFIER(40, 0, 60);
        const wxColour COLOR_NUMBER(0, 150, 0);
        const wxColour COLOR_CHARACTER(150, 0, 0);
        const wxColour COLOR_WORD(0, 0, 150);
        const wxColour COLOR_WORD2(0, 150, 0);
        const wxColour COLOR_COMMENT(150, 150, 150);
        const wxColour COLOR_COMMENT_LINE(150, 150, 150);
        const wxColour COLOR_COMMENT_DOC(150, 150, 150);
        const wxColour COLOR_OPERATOR(0, 0, 200);
        const wxColour BACKGROUND(255, 255, 255); // white
        const wxColour FOREGROUND(0, 0, 0); // black
    }
    //TODO: Investigate and implement the possibility of making theme settings dynamic and customizable with the use of a configuration file or settings dialog.
    namespace DarkTheme
    {
        const wxColour COLOR_STRING(139, 233, 253);
        const wxColour COLOR_PREPROCESSOR(80, 250, 123);
        const wxColour COLOR_IDENTIFIER(248, 248, 242);
        const wxColour COLOR_NUMBER(189, 147, 249);
        const wxColour COLOR_CHARACTER(255, 184, 108);
        const wxColour COLOR_WORD(139, 233, 253);
        const wxColour COLOR_WORD2(80, 250, 123);
        const wxColour COLOR_COMMENT(98, 114, 164);
        const wxColour COLOR_COMMENT_LINE(98, 114, 164);
        const wxColour COLOR_COMMENT_DOC(98, 114, 164);
        const wxColour COLOR_OPERATOR(248, 248, 242);
        const wxColour BACKGROUND(40, 42, 54); // dark
        const wxColour FOREGROUND(248, 248, 242); //white
    }
    //TODO: Document the ThemeSettings struct detailing the role of each color component in the application's UI.
    struct ThemeSettings
    {
        wxColour colorString;
        wxColour colorPreprocessor;
        wxColour colorIdentifier;
        wxColour colorNumber;
        wxColour colorCharacter;
        wxColour colorWord;
        wxColour colorWord2;
        wxColour colorComment;
        wxColour colorCommentLine;
        wxColour colorCommentDoc;
        wxColour colorOperator;
        wxColour background;
        wxColour foreground;
    };
    //TODO: Refactor this function to handle more themes or make it more flexible to handle custom themes.
    inline ThemeSettings GetThemeSettings(bool isDarkMode)
    {
        if(!isDarkMode)
        {
            return ThemeSettings
            {
                    DarkTheme::COLOR_STRING,
                    DarkTheme::COLOR_PREPROCESSOR,
                    DarkTheme::COLOR_IDENTIFIER,
                    DarkTheme::COLOR_NUMBER,
                    DarkTheme::COLOR_CHARACTER,
                    DarkTheme::COLOR_WORD,
                    DarkTheme::COLOR_WORD2,
                    DarkTheme::COLOR_COMMENT,
                    DarkTheme::COLOR_COMMENT_LINE,
                    DarkTheme::COLOR_COMMENT_DOC,
                    DarkTheme::COLOR_OPERATOR,
                    DarkTheme::BACKGROUND,
                    DarkTheme::FOREGROUND
            };
        }
        else
        {
            return ThemeSettings
            {
                    LightTheme::COLOR_STRING,
                    LightTheme::COLOR_PREPROCESSOR,
                    LightTheme::COLOR_IDENTIFIER,
                    LightTheme::COLOR_NUMBER,
                    LightTheme::COLOR_CHARACTER,
                    LightTheme::COLOR_WORD,
                    LightTheme::COLOR_WORD2,
                    LightTheme::COLOR_COMMENT,
                    LightTheme::COLOR_COMMENT_LINE,
                    LightTheme::COLOR_COMMENT_DOC,
                    LightTheme::COLOR_OPERATOR,
                    LightTheme::BACKGROUND,
                    LightTheme::FOREGROUND
            };
        }
    }
};
#endif //EDITOR_CONSTANTS_HPP