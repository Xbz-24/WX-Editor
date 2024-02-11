/**
 * @file constants.hpp
 * @brief This file contains the constants used in the application
 * @version 0.1
 * @date 2021-12-23
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
    // Lexer
    const int LEXER_CPP = wxSTC_LEX_CPP;
    // Color constants
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
    // Editor keywords
    const wxString EDITOR_KEYWORDS = "return int float double char if else while for break continue switch case default";
    const wxString AUTO_COMP_KEYWORDS = "int char float double";
    // Style constants
    const bool STYLE_BOLD = true;
    // Margin and marker constants
    const int MARGIN_NUMBER_TYPE = wxSTC_MARGIN_NUMBER;
    const int MARGIN_SYMBOL_TYPE = wxSTC_MARGIN_SYMBOL;
    const int MARGIN_WIDTH = 16;
    const int MARKER_FOLDER = wxSTC_MARKNUM_FOLDER;
    const int MARKER_FOLDER_OPEN = wxSTC_MARKNUM_FOLDEROPEN;
    // Button constants
    const wxPoint SAVE_BUTTON_POSITION(10,300);
    const wxPoint OPEN_BUTTON_POSITION(100,300);
    const wxString SAVE_BUTTON_LABEL = "Save";
    const wxString OPEN_BUTTON_LABEL = "Open";
    const int ZOOM_LEVEL = 100;
    const int EDITOR_MARGIN_WIDTH_PIXELS = 150;
    const int MINIMUM_WIDTH_MARGIN_DRAGGING = 12;
    const int C_STRING_STYLE = wxSTC_C_STRING;

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