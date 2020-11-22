/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_COLORS_HPP_
#define SRC_CLIENT_INCLUDE_COLORS_HPP_

#define SPLITRGBA(color) color.R, color.G, color.B, color.A
#define SPLITRGB(color) color.R, color.G, color.B

typedef struct {
    int R, G, B, A;
} Color;

Color white_color  {0xFF, 0xFF, 0xFF, 0xFF};
Color black_color  {0x00, 0x00, 0x00, 0xFF};
Color red_color    {0xFF, 0x00, 0x00, 0xFF};
Color blue_color   {0x00, 0x00, 0xFF, 0xFF};
Color green_color  {0x00, 0xFF, 0x00, 0xFF};
Color purple_color {0xFF, 0x00, 0xFF, 0xFF};
Color cyan_color   {0x00, 0xFF, 0xFF, 0xFF};

#endif  // SRC_CLIENT_INCLUDE_COLORS_HPP_
