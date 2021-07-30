//
// Created by Joseph Alai on 7/30/21.
//
#include "Colors.h"
#include <iostream>
#include "glm/glm.hpp"
    const glm::vec3 Colors::Aliceblue            = glm::vec3(0xf0/255.0f, 0xf8/255.0f, 0xff/255.0f); // rgb(240, 248, 255.0f)
    const glm::vec3 Colors::Antiquewhite         = glm::vec3(0xfa/255.0f, 0xeb/255.0f, 0xd7/255.0f); // rgb(250, 235, 215)
    const glm::vec3 Colors::Aqua                 = glm::vec3(0x00/255.0f, 0xff/255.0f, 0xff/255.0f); // rgb(0, 255.0f, 255.0f)
    const glm::vec3 Colors::Aquamarine           = glm::vec3(0x7f/255.0f, 0xff/255.0f, 0xd4/255.0f); // rgb(127, 255.0f, 212)
    const glm::vec3 Colors::Azure                = glm::vec3(0xf0/255.0f, 0xff/255.0f, 0xff/255.0f); // rgb(240, 255.0f, 255.0f)
    const glm::vec3 Colors::Beige                = glm::vec3(0xf5/255.0f, 0xf5/255.0f, 0xdc/255.0f); // rgb(245, 245, 220)
    const glm::vec3 Colors::Bisque               = glm::vec3(0xff/255.0f, 0xe4/255.0f, 0xc4/255.0f); // rgb(255.0f, 228, 196)
    const glm::vec3 Colors::Black                = glm::vec3(0x00/255.0f, 0x00/255.0f, 0x00/255.0f); // rgb(0, 0, 0)
    const glm::vec3 Colors::Blanchedalmond       = glm::vec3(0xff/255.0f, 0xeb/255.0f, 0xcd/255.0f); // rgb(255.0f, 235, 205)
    const glm::vec3 Colors::Blue                 = glm::vec3(0x00/255.0f, 0x00/255.0f, 0xff/255.0f); // rgb(0, 0, 255.0f)
    const glm::vec3 Colors::Blueviolet           = glm::vec3(0x8a/255.0f, 0x2b/255.0f, 0xe2/255.0f); // rgb(138, 43, 226)
    const glm::vec3 Colors::Brown                = glm::vec3(0xa5/255.0f, 0x2a/255.0f, 0x2a/255.0f); // rgb(165, 42, 42)
    const glm::vec3 Colors::Burlywood            = glm::vec3(0xde/255.0f, 0xb8/255.0f, 0x87/255.0f); // rgb(222, 184, 135)
    const glm::vec3 Colors::Cadetblue            = glm::vec3(0x5f/255.0f, 0x9e/255.0f, 0xa0/255.0f); // rgb(95, 158, 160)
    const glm::vec3 Colors::Chartreuse           = glm::vec3(0x7f/255.0f, 0xff/255.0f, 0x00/255.0f); // rgb(127, 255.0f, 0)
    const glm::vec3 Colors::Chocolate            = glm::vec3(0xd2/255.0f, 0x69/255.0f, 0x1e/255.0f); // rgb(210, 105, 30)
    const glm::vec3 Colors::Coral                = glm::vec3(0xff/255.0f, 0x7f/255.0f, 0x50/255.0f); // rgb(255.0f, 127, 80)
    const glm::vec3 Colors::Cornflowerblue       = glm::vec3(0x64/255.0f, 0x95/255.0f, 0xed/255.0f); // rgb(100, 149, 237)
    const glm::vec3 Colors::Cornsilk             = glm::vec3(0xff/255.0f, 0xf8/255.0f, 0xdc/255.0f); // rgb(255.0f, 248, 220)
    const glm::vec3 Colors::Crimson              = glm::vec3(0xdc/255.0f, 0x14/255.0f, 0x3c/255.0f); // rgb(220, 20, 60)
    const glm::vec3 Colors::Cyan                 = glm::vec3(0x00/255.0f, 0xff/255.0f, 0xff/255.0f); // rgb(0, 255.0f, 255.0f)
    const glm::vec3 Colors::Darkblue             = glm::vec3(0x00/255.0f, 0x00/255.0f, 0x8b/255.0f); // rgb(0, 0, 139)
    const glm::vec3 Colors::Darkcyan             = glm::vec3(0x00/255.0f, 0x8b/255.0f, 0x8b/255.0f); // rgb(0, 139, 139)
    const glm::vec3 Colors::Darkgoldenrod        = glm::vec3(0xb8/255.0f, 0x86/255.0f, 0x0b/255.0f); // rgb(184, 134, 11)
    const glm::vec3 Colors::Darkgray             = glm::vec3(0xa9/255.0f, 0xa9/255.0f, 0xa9/255.0f); // rgb(169, 169, 169)
    const glm::vec3 Colors::Darkgreen            = glm::vec3(0x00/255.0f, 0x64/255.0f, 0x00/255.0f); // rgb(0, 100, 0)
    const glm::vec3 Colors::Darkgrey             = glm::vec3(0xa9/255.0f, 0xa9/255.0f, 0xa9/255.0f); // rgb(169, 169, 169)
    const glm::vec3 Colors::Darkkhaki            = glm::vec3(0xbd/255.0f, 0xb7/255.0f, 0x6b/255.0f); // rgb(189, 183, 107)
    const glm::vec3 Colors::Darkmagenta          = glm::vec3(0x8b/255.0f, 0x00/255.0f, 0x8b/255.0f); // rgb(139, 0, 139)
    const glm::vec3 Colors::Darkolivegreen       = glm::vec3(0x55/255.0f, 0x6b/255.0f, 0x2f/255.0f); // rgb(85, 107, 47)
    const glm::vec3 Colors::Darkorange           = glm::vec3(0xff/255.0f, 0x8c/255.0f, 0x00/255.0f); // rgb(255.0f, 140, 0)
    const glm::vec3 Colors::Darkorchid           = glm::vec3(0x99/255.0f, 0x32/255.0f, 0xcc/255.0f); // rgb(153, 50, 204)
    const glm::vec3 Colors::Darkred              = glm::vec3(0x8b/255.0f, 0x00/255.0f, 0x00/255.0f); // rgb(139, 0, 0)
    const glm::vec3 Colors::Darksalmon           = glm::vec3(0xe9/255.0f, 0x96/255.0f, 0x7a/255.0f); // rgb(233, 150, 122)
    const glm::vec3 Colors::Darkseagreen         = glm::vec3(0x8f/255.0f, 0xbc/255.0f, 0x8f/255.0f); // rgb(143, 188, 143)
    const glm::vec3 Colors::Darkslateblue        = glm::vec3(0x48/255.0f, 0x3d/255.0f, 0x8b/255.0f); // rgb(72, 61, 139)
    const glm::vec3 Colors::Darkslategray        = glm::vec3(0x2f/255.0f, 0x4f/255.0f, 0x4f/255.0f); // rgb(47, 79, 79)
    const glm::vec3 Colors::Darkslategrey        = glm::vec3(0x2f/255.0f, 0x4f/255.0f, 0x4f/255.0f); // rgb(47, 79, 79)
    const glm::vec3 Colors::Darkturquoise        = glm::vec3(0x00/255.0f, 0xce/255.0f, 0xd1/255.0f); // rgb(0, 206, 209)
    const glm::vec3 Colors::Darkviolet           = glm::vec3(0x94/255.0f, 0x00/255.0f, 0xd3/255.0f); // rgb(148, 0, 211)
    const glm::vec3 Colors::Deeppink             = glm::vec3(0xff/255.0f, 0x14/255.0f, 0x93/255.0f); // rgb(255.0f, 20, 147)
    const glm::vec3 Colors::Deepskyblue          = glm::vec3(0x00/255.0f, 0xbf/255.0f, 0xff/255.0f); // rgb(0, 191, 255.0f)
    const glm::vec3 Colors::Dimgray              = glm::vec3(0x69/255.0f, 0x69/255.0f, 0x69/255.0f); // rgb(105, 105, 105)
    const glm::vec3 Colors::Dimgrey              = glm::vec3(0x69/255.0f, 0x69/255.0f, 0x69/255.0f); // rgb(105, 105, 105)
    const glm::vec3 Colors::Dodgerblue           = glm::vec3(0x1e/255.0f, 0x90/255.0f, 0xff/255.0f); // rgb(30, 144, 255.0f)
    const glm::vec3 Colors::Firebrick            = glm::vec3(0xb2/255.0f, 0x22/255.0f, 0x22/255.0f); // rgb(178, 34, 34)
    const glm::vec3 Colors::Floralwhite          = glm::vec3(0xff/255.0f, 0xfa/255.0f, 0xf0/255.0f); // rgb(255.0f, 250, 240)
    const glm::vec3 Colors::Forestgreen          = glm::vec3(0x22/255.0f, 0x8b/255.0f, 0x22/255.0f); // rgb(34, 139, 34)
    const glm::vec3 Colors::Fuchsia              = glm::vec3(0xff/255.0f, 0x00/255.0f, 0xff/255.0f); // rgb(255.0f, 0, 255.0f)
    const glm::vec3 Colors::Gainsboro            = glm::vec3(0xdc/255.0f, 0xdc/255.0f, 0xdc/255.0f); // rgb(220, 220, 220)
    const glm::vec3 Colors::Ghostwhite           = glm::vec3(0xf8/255.0f, 0xf8/255.0f, 0xff/255.0f); // rgb(248, 248, 255.0f)
    const glm::vec3 Colors::Gold                 = glm::vec3(0xff/255.0f, 0xd7/255.0f, 0x00/255.0f); // rgb(255.0f, 215, 0)
    const glm::vec3 Colors::Goldenrod            = glm::vec3(0xda/255.0f, 0xa5/255.0f, 0x20/255.0f); // rgb(218, 165, 32)
    const glm::vec3 Colors::Gray                 = glm::vec3(0x80/255.0f, 0x80/255.0f, 0x80/255.0f); // rgb(128, 128, 128)
    const glm::vec3 Colors::Green                = glm::vec3(0x00/255.0f, 0x80/255.0f, 0x00/255.0f); // rgb(0, 128, 0)
    const glm::vec3 Colors::Greenyellow          = glm::vec3(0xad/255.0f, 0xff/255.0f, 0x2f/255.0f); // rgb(173, 255.0f, 47)
    const glm::vec3 Colors::Grey                 = glm::vec3(0x80/255.0f, 0x80/255.0f, 0x80/255.0f); // rgb(128, 128, 128)
    const glm::vec3 Colors::Honeydew             = glm::vec3(0xf0/255.0f, 0xff/255.0f, 0xf0/255.0f); // rgb(240, 255.0f, 240)
    const glm::vec3 Colors::Hotpink              = glm::vec3(0xff/255.0f, 0x69/255.0f, 0xb4/255.0f); // rgb(255.0f, 105, 180)
    const glm::vec3 Colors::Indianred            = glm::vec3(0xcd/255.0f, 0x5c/255.0f, 0x5c/255.0f); // rgb(205, 92, 92)
    const glm::vec3 Colors::Indigo               = glm::vec3(0x4b/255.0f, 0x00/255.0f, 0x82/255.0f); // rgb(75, 0, 130)
    const glm::vec3 Colors::Ivory                = glm::vec3(0xff/255.0f, 0xff/255.0f, 0xf0/255.0f); // rgb(255.0f, 255.0f, 240)
    const glm::vec3 Colors::Khaki                = glm::vec3(0xf0/255.0f, 0xe6/255.0f, 0x8c/255.0f); // rgb(240, 230, 140)
    const glm::vec3 Colors::Lavender             = glm::vec3(0xe6/255.0f, 0xe6/255.0f, 0xfa/255.0f); // rgb(230, 230, 250)
    const glm::vec3 Colors::Lavenderblush        = glm::vec3(0xff/255.0f, 0xf0/255.0f, 0xf5/255.0f); // rgb(255.0f, 240, 245)
    const glm::vec3 Colors::Lawngreen            = glm::vec3(0x7c/255.0f, 0xfc/255.0f, 0x00/255.0f); // rgb(124, 252, 0)
    const glm::vec3 Colors::Lemonchiffon         = glm::vec3(0xff/255.0f, 0xfa/255.0f, 0xcd/255.0f); // rgb(255.0f, 250, 205)
    const glm::vec3 Colors::Lightblue            = glm::vec3(0xad/255.0f, 0xd8/255.0f, 0xe6/255.0f); // rgb(173, 216, 230)
    const glm::vec3 Colors::Lightcoral           = glm::vec3(0xf0/255.0f, 0x80/255.0f, 0x80/255.0f); // rgb(240, 128, 128)
    const glm::vec3 Colors::Lightcyan            = glm::vec3(0xe0/255.0f, 0xff/255.0f, 0xff/255.0f); // rgb(224, 255.0f, 255.0f)
    const glm::vec3 Colors::Lightgoldenrodyellow = glm::vec3(0xfa/255.0f, 0xfa/255.0f, 0xd2/255.0f); // rgb(250, 250, 210)
    const glm::vec3 Colors::Lightgray            = glm::vec3(0xd3/255.0f, 0xd3/255.0f, 0xd3/255.0f); // rgb(211, 211, 211)
    const glm::vec3 Colors::Lightgreen           = glm::vec3(0x90/255.0f, 0xee/255.0f, 0x90/255.0f); // rgb(144, 238, 144)
    const glm::vec3 Colors::Lightgrey            = glm::vec3(0xd3/255.0f, 0xd3/255.0f, 0xd3/255.0f); // rgb(211, 211, 211)
    const glm::vec3 Colors::Lightpink            = glm::vec3(0xff/255.0f, 0xb6/255.0f, 0xc1/255.0f); // rgb(255.0f, 182, 193)
    const glm::vec3 Colors::Lightsalmon          = glm::vec3(0xff/255.0f, 0xa0/255.0f, 0x7a/255.0f); // rgb(255.0f, 160, 122)
    const glm::vec3 Colors::Lightseagreen        = glm::vec3(0x20/255.0f, 0xb2/255.0f, 0xaa/255.0f); // rgb(32, 178, 170)
    const glm::vec3 Colors::Lightskyblue         = glm::vec3(0x87/255.0f, 0xce/255.0f, 0xfa/255.0f); // rgb(135, 206, 250)
    const glm::vec3 Colors::Lightslategray       = glm::vec3(0x77/255.0f, 0x88/255.0f, 0x99/255.0f); // rgb(119, 136, 153)
    const glm::vec3 Colors::Lightslategrey       = glm::vec3(0x77/255.0f, 0x88/255.0f, 0x99/255.0f); // rgb(119, 136, 153)
    const glm::vec3 Colors::Lightsteelblue       = glm::vec3(0xb0/255.0f, 0xc4/255.0f, 0xde/255.0f); // rgb(176, 196, 222)
    const glm::vec3 Colors::Lightyellow          = glm::vec3(0xff/255.0f, 0xff/255.0f, 0xe0/255.0f); // rgb(255.0f, 255.0f, 224)
    const glm::vec3 Colors::Lime                 = glm::vec3(0x00/255.0f, 0xff/255.0f, 0x00/255.0f); // rgb(0, 255.0f, 0)
    const glm::vec3 Colors::Limegreen            = glm::vec3(0x32/255.0f, 0xcd/255.0f, 0x32/255.0f); // rgb(50, 205, 50)
    const glm::vec3 Colors::Linen                = glm::vec3(0xfa/255.0f, 0xf0/255.0f, 0xe6/255.0f); // rgb(250, 240, 230)
    const glm::vec3 Colors::Magenta              = glm::vec3(0xff/255.0f, 0x00/255.0f, 0xff/255.0f); // rgb(255.0f, 0, 255.0f)
    const glm::vec3 Colors::Maroon               = glm::vec3(0x80/255.0f, 0x00/255.0f, 0x00/255.0f); // rgb(128, 0, 0)
    const glm::vec3 Colors::Mediumaquamarine     = glm::vec3(0x66/255.0f, 0xcd/255.0f, 0xaa/255.0f); // rgb(102, 205, 170)
    const glm::vec3 Colors::Mediumblue           = glm::vec3(0x00/255.0f, 0x00/255.0f, 0xcd/255.0f); // rgb(0, 0, 205)
    const glm::vec3 Colors::Mediumorchid         = glm::vec3(0xba/255.0f, 0x55/255.0f, 0xd3/255.0f); // rgb(186, 85, 211)
    const glm::vec3 Colors::Mediumpurple         = glm::vec3(0x93/255.0f, 0x70/255.0f, 0xdb/255.0f); // rgb(147, 112, 219)
    const glm::vec3 Colors::Mediumseagreen       = glm::vec3(0x3c/255.0f, 0xb3/255.0f, 0x71/255.0f); // rgb(60, 179, 113)
    const glm::vec3 Colors::Mediumslateblue      = glm::vec3(0x7b/255.0f, 0x68/255.0f, 0xee/255.0f); // rgb(123, 104, 238)
    const glm::vec3 Colors::Mediumspringgreen    = glm::vec3(0x00/255.0f, 0xfa/255.0f, 0x9a/255.0f); // rgb(0, 250, 154)
    const glm::vec3 Colors::Mediumturquoise      = glm::vec3(0x48/255.0f, 0xd1/255.0f, 0xcc/255.0f); // rgb(72, 209, 204)
    const glm::vec3 Colors::Mediumvioletred      = glm::vec3(0xc7/255.0f, 0x15/255.0f, 0x85/255.0f); // rgb(199, 21, 133)
    const glm::vec3 Colors::Midnightblue         = glm::vec3(0x19/255.0f, 0x19/255.0f, 0x70/255.0f); // rgb(25, 25, 112)
    const glm::vec3 Colors::Mintcream            = glm::vec3(0xf5/255.0f, 0xff/255.0f, 0xfa/255.0f); // rgb(245, 255.0f, 250)
    const glm::vec3 Colors::Mistyrose            = glm::vec3(0xff/255.0f, 0xe4/255.0f, 0xe1/255.0f); // rgb(255.0f, 228, 225)
    const glm::vec3 Colors::Moccasin             = glm::vec3(0xff/255.0f, 0xe4/255.0f, 0xb5/255.0f); // rgb(255.0f, 228, 181)
    const glm::vec3 Colors::Navajowhite          = glm::vec3(0xff/255.0f, 0xde/255.0f, 0xad/255.0f); // rgb(255.0f, 222, 173)
    const glm::vec3 Colors::Navy                 = glm::vec3(0x00/255.0f, 0x00/255.0f, 0x80/255.0f); // rgb(0, 0, 128)
    const glm::vec3 Colors::Oldlace              = glm::vec3(0xfd/255.0f, 0xf5/255.0f, 0xe6/255.0f); // rgb(253, 245, 230)
    const glm::vec3 Colors::Olive                = glm::vec3(0x80/255.0f, 0x80/255.0f, 0x00/255.0f); // rgb(128, 128, 0)
    const glm::vec3 Colors::Olivedrab            = glm::vec3(0x6b/255.0f, 0x8e/255.0f, 0x23/255.0f); // rgb(107, 142, 35)
    const glm::vec3 Colors::Orange               = glm::vec3(0xff/255.0f, 0xa5/255.0f, 0x00/255.0f); // rgb(255.0f, 165, 0)
    const glm::vec3 Colors::Orangered            = glm::vec3(0xff/255.0f, 0x45/255.0f, 0x00/255.0f); // rgb(255.0f, 69, 0)
    const glm::vec3 Colors::Orchid               = glm::vec3(0xda/255.0f, 0x70/255.0f, 0xd6/255.0f); // rgb(218, 112, 214)
    const glm::vec3 Colors::Palegoldenrod        = glm::vec3(0xee/255.0f, 0xe8/255.0f, 0xaa/255.0f); // rgb(238, 232, 170)
    const glm::vec3 Colors::Palegreen            = glm::vec3(0x98/255.0f, 0xfb/255.0f, 0x98/255.0f); // rgb(152, 251, 152)
    const glm::vec3 Colors::Paleturquoise        = glm::vec3(0xaf/255.0f, 0xee/255.0f, 0xee/255.0f); // rgb(175, 238, 238)
    const glm::vec3 Colors::Palevioletred        = glm::vec3(0xdb/255.0f, 0x70/255.0f, 0x93/255.0f); // rgb(219, 112, 147)
    const glm::vec3 Colors::Papayawhip           = glm::vec3(0xff/255.0f, 0xef/255.0f, 0xd5/255.0f); // rgb(255.0f, 239, 213)
    const glm::vec3 Colors::Peachpuff            = glm::vec3(0xff/255.0f, 0xda/255.0f, 0xb9/255.0f); // rgb(255.0f, 218, 185)
    const glm::vec3 Colors::Peru                 = glm::vec3(0xcd/255.0f, 0x85/255.0f, 0x3f/255.0f); // rgb(205, 133, 63)
    const glm::vec3 Colors::Pink                 = glm::vec3(0xff/255.0f, 0xc0/255.0f, 0xcb/255.0f); // rgb(255.0f, 192, 203)
    const glm::vec3 Colors::Plum                 = glm::vec3(0xdd/255.0f, 0xa0/255.0f, 0xdd/255.0f); // rgb(221, 160, 221)
    const glm::vec3 Colors::Powderblue           = glm::vec3(0xb0/255.0f, 0xe0/255.0f, 0xe6/255.0f); // rgb(176, 224, 230)
    const glm::vec3 Colors::Purple               = glm::vec3(0x80/255.0f, 0x00/255.0f, 0x80/255.0f); // rgb(128, 0, 128)
    const glm::vec3 Colors::Red                  = glm::vec3(0xff/255.0f, 0x00/255.0f, 0x00/255.0f); // rgb(255.0f, 0, 0)
    const glm::vec3 Colors::Rosybrown            = glm::vec3(0xbc/255.0f, 0x8f/255.0f, 0x8f/255.0f); // rgb(188, 143, 143)
    const glm::vec3 Colors::Royalblue            = glm::vec3(0x41/255.0f, 0x69/255.0f, 0xe1/255.0f); // rgb(65, 105, 225)
    const glm::vec3 Colors::Saddlebrown          = glm::vec3(0x8b/255.0f, 0x45/255.0f, 0x13/255.0f); // rgb(139, 69, 19)
    const glm::vec3 Colors::Salmon               = glm::vec3(0xfa/255.0f, 0x80/255.0f, 0x72/255.0f); // rgb(250, 128, 114)
    const glm::vec3 Colors::Sandybrown           = glm::vec3(0xf4/255.0f, 0xa4/255.0f, 0x60/255.0f); // rgb(244, 164, 96)
    const glm::vec3 Colors::Seagreen             = glm::vec3(0x2e/255.0f, 0x8b/255.0f, 0x57/255.0f); // rgb(46, 139, 87)
    const glm::vec3 Colors::Seashell             = glm::vec3(0xff/255.0f, 0xf5/255.0f, 0xee/255.0f); // rgb(255.0f, 245, 238)
    const glm::vec3 Colors::Sienna               = glm::vec3(0xa0/255.0f, 0x52/255.0f, 0x2d/255.0f); // rgb(160, 82, 45)
    const glm::vec3 Colors::Silver               = glm::vec3(0xc0/255.0f, 0xc0/255.0f, 0xc0/255.0f); // rgb(192, 192, 192)
    const glm::vec3 Colors::Skyblue              = glm::vec3(0x87/255.0f, 0xce/255.0f, 0xeb/255.0f); // rgb(135, 206, 235)
    const glm::vec3 Colors::Slateblue            = glm::vec3(0x6a/255.0f, 0x5a/255.0f, 0xcd/255.0f); // rgb(106, 90, 205)
    const glm::vec3 Colors::Slategray            = glm::vec3(0x70/255.0f, 0x80/255.0f, 0x90/255.0f); // rgb(112, 128, 144)
    const glm::vec3 Colors::Slategrey            = glm::vec3(0x70/255.0f, 0x80/255.0f, 0x90/255.0f); // rgb(112, 128, 144)
    const glm::vec3 Colors::Snow                 = glm::vec3(0xff/255.0f, 0xfa/255.0f, 0xfa/255.0f); // rgb(255.0f, 250, 250)
    const glm::vec3 Colors::Springgreen          = glm::vec3(0x00/255.0f, 0xff/255.0f, 0x7f/255.0f); // rgb(0, 255.0f, 127)
    const glm::vec3 Colors::Steelblue            = glm::vec3(0x46/255.0f, 0x82/255.0f, 0xb4/255.0f); // rgb(70, 130, 180)
    const glm::vec3 Colors::Tan                  = glm::vec3(0xd2/255.0f, 0xb4/255.0f, 0x8c/255.0f); // rgb(210, 180, 140)
    const glm::vec3 Colors::Teal                 = glm::vec3(0x00/255.0f, 0x80/255.0f, 0x80/255.0f); // rgb(0, 128, 128)
    const glm::vec3 Colors::Thistle              = glm::vec3(0xd8/255.0f, 0xbf/255.0f, 0xd8/255.0f); // rgb(216, 191, 216)
    const glm::vec3 Colors::Tomato               = glm::vec3(0xff/255.0f, 0x63/255.0f, 0x47/255.0f); // rgb(255.0f, 99, 71)
    const glm::vec3 Colors::Turquoise            = glm::vec3(0x40/255.0f, 0xe0/255.0f, 0xd0/255.0f); // rgb(64, 224, 208)
    const glm::vec3 Colors::Violet               = glm::vec3(0xee/255.0f, 0x82/255.0f, 0xee/255.0f); // rgb(238, 130, 238)
    const glm::vec3 Colors::Wheat                = glm::vec3(0xf5/255.0f, 0xde/255.0f, 0xb3/255.0f); // rgb(245, 222, 179)
    const glm::vec3 Colors::White                = glm::vec3(0xff/255.0f, 0xff/255.0f, 0xff/255.0f); // rgb(255.0f, 255.0f, 255.0f)
    const glm::vec3 Colors::Whitesmoke           = glm::vec3(0xf5/255.0f, 0xf5/255.0f, 0xf5/255.0f); // rgb(245, 245, 245)
    const glm::vec3 Colors::Yellow               = glm::vec3(0xff/255.0f, 0xff/255.0f, 0x00/255.0f); // rgb(255.0f, 255.0f, 0)
    const glm::vec3 Colors::Yellowgreen          = glm::vec3(0x9a/255.0f, 0xcd/255.0f, 0x32/255.0f); // rgb(154, 205, 50)
    std::string Colors::toString(glm::vec3 color) {
        return std::string("Color: ") +
               std::to_string(color.x) + ", " +
               std::to_string(color.y) + ", " +
               std::to_string(color.z);
    };