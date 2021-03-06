/***************************************************************************
*   Copyright (C) 2007 by BOP                                             *
*   polepolek@gmail.com                                                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/
#ifndef SSHEET_H
#define SSHEET_H

static const char *dictStyleSheet =
    "body {\n"
    "color:#666666;\n"
    "background-color: #F0F0F0;\n"
    "margin-left: 0px; margin-right: 0px; "
    "margin-top: 0px; margin-bottom: 0px;\n"
    "}\n"
    "h1 {\n"
    "background-color: #C0C0E0;\n"
    "font-weight: bold;\n"
    "font-size: x-large;\n"
    "margin-left: 0px; margin-right: 0px; "
    "margin-top: 0px; margin-bottom: 3px;\n"
    "}\n"
    "h2 {\n"
    "background-color: #E0E0E0;\n"
    "font-size: large;\n"
    "margin-left: 0px; margin-right: 0px; "
    "margin-top: 0px; margin-bottom: 0px;\n"
    "}\n"
    "pre {\n"
    "background-color: #F0F0F0;\n"
    "margin-left: 5px; margin-right: 0px; "
    "margin-top: 7px; margin-bottom: 7px;\n"
    "white-space: pre-wrap;\n"
    "text-indent: 15px; \n"
    "font-size:  medium;\n"
    "}\n"
    "i {}\n"
    "b {\n"
    "color: #393939;\n"
    "}\n"
    "em.err {\n"
    "color: #DD0000;\n"
    "font-weight: bold;\n"
    "font-stye: italic;\n"
    "}\n"
    "span.sel {\n"
    "color: #551111;\n"
    "}\n"
    "span.img {\n"
    "font-size: small;\n"
    "font-stye: italic;\n"
    "}\n"
    "img {\n"
    "vertical-alignment: super;\n"
    "font-size: small;\n"
    "}\n"
    "sup {\n"
    "color: #550000;\n"
    "}\n"
    "sub {\n"
    "color: #005500;\n"
    "}\n"
    "a {\n"
    "color: #0000FF;\n"
    "}\n"
    "a.ref {}\n"
    "a.cnd {\n"
    "color: #0000AA;\n"
    "}\n"
    "a.img {}\n"
    "a.snd {}\n"
    "a.mpg {}\n"
    "p {}\n";

static const char *bookStyleSheet =
    "body {\n"
    "color:#666666;\n"
    "background-color: #F5F5F5;\n"
    "margin-left: 0px; margin-right: 0px; \n"
    "margin-top: 20px; margin-bottom: 0px;\n"
    "}\n"
    "h1 {\n"
    "font-weight: bold;\n"
    "font-size: x-large;\n"
    "margin-left: 5px; margin-right: 0px;\n"
    "margin-top: 10px; margin-bottom: 10px;\n"
    "}\n"
    "h2 {\n"
    "font-size: large;\n"
    "margin-left: 30px; margin-right: 0px;\n"
    "margin-top: 10px; margin-bottom: 10px;\n"
    "}\n"
    "h3 {\n"
    "font-size: medium;\n"
    "margin-left: 45; margin-right: 0px;\n"
    "margin-top: 10px; margin-bottom: 10px;\n"
    "}\n"
    "h4 {\n"
    "font-size: medium;\n"
    "margin-left: 60px; margin-right: 0px;\n"
    "margin-top: 10px; margin-bottom: 10px;\n"
    "}\n"
    "h5 {\n"
    "font-size: medium;\n"
    "margin-left: 75; margin-right: 0px;\n"
    "margin-top: 10px; margin-bottom: 10px;\n"
    "}\n"
    "h6 {\n"
    "font-size: medium;\n"
    "margin-left: 90; margin-right: 0px;\n"
    "margin-top: 10px; margin-bottom: 10px;\n"
    "}\n"
    "pre {\n"
    "margin-left: 25px; margin-right: 10px;\n"
    "margin-top: 7px; margin-bottom: 7px;\n"
    "white-space: pre-wrap;\n"
    "text-indent: 0; \n"
    "font-size:  medium;\n"
    "}\n"
    "i {}\n"
    "em.err {\n"
    "color: #DD0000;\n"
    "font-weight: bold;\n"
    "font-stye: italic;\n"
    "}\n"
    "span.sel {\n"
    "color: #551111;\n"
    "}\n"
    "span.img {\n"
    "font-size: small;\n"
    "font-stye: italic;\n"
    "}\n"
    "img {\n"
    "vertical-alignment: super;\n"
    "font-size: small;\n"
    "}\n"
    "b {\n"
    "color: #393939;\n"
    "}\n"
    "sup {\n"
    "color: #550000;\n"
    "}\n"
    "sub {\n"
    "color: #005500;\n"
    "}\n"
    "a {\n"
    "color: #0000FF;\n"
    "}\n"
    "a.ref {}\n"
    "a.cnd {\n"
    "color: #0000AA;\n"
    "}\n"
    "a.img {}\n"
    "a.snd {}\n"
    "a.mpg {}\n"
    "p {}\n";

static const char *statusBarStyleSheet =
    "QPushButton { padding: 0px; margin: 0px; font-weight:bold; }\n"
    "QPushButton:hover  { padding: 0px; margin: 0px; font-weight:bold; background-color: #DDDDDD;  border-width: 2px; border-style: solid; border-radius: 3px; }\n"
    "QPushButton:pressed  {padding: 0px; margin: 0px; font-weight:bold;  background-color: #BBBB77; }\n"
    "QPushButton#direction { color: #752020; min-width: 57px; }\n"
    "QPushButton#logic { color: #556b2f; min-width: 21px; }\n"
    "QPushButton#limit-book { color: #008b8b; }\n"
    "QPushButton#limit-total { color: #483d70; }\n"
    "QPushButton#search { color: #9900d3; min-width: 21px;  }\n"
    "QPushButton#selection { color: #006400; } \n"
    "QLabel { padding: 0px; margin: 0px; font-weight:bold; }\n"
    "QLabel#process { color: #555555; }\n";

#endif

