#pragma once

/* Copyright © 2018-2019 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <skift/runtime.h>

/* --- Colors --------------------------------------------------------------- */

typedef unsigned int color_t;
#define rbg(r, g, b) (color_t)(((r)&0xff) | ((g)&0xff) << 8 | ((b)&0xff) << 16)
#define rbga(r, g, b, a) (color_t)(((r)&0xff) | ((g)&0xff) << 8 | ((b)&0xff) << 16 | ((a)&0xff) << 24)

/* --- Bitmap --------------------------------------------------------------- */

typedef struct
{
    bool shared;

    int width;
    int height;

    uint *buffer;
} bitmap_t;

bitmap_t *bitmap(uint width, uint height);
void bitmap_delete(bitmap_t *bmp);
void bitmap_copy(bitmap_t *src, int sx, int sy, bitmap_t *dest, int dx, int dy, uint w, uint h);

/* --- Drawing -------------------------------------------------------------- */

typedef struct
{
    bitmap_t *surface;
    color_t color;
} drawing_context_t;

void drawing_begin(drawing_context_t *ctx, bitmap_t *surface);
void drawing_end(drawing_context_t *ctx);

void drawing_clear(bitmap_t *bmp, uint color);

void drawing_pixel(bitmap_t *bmp, int x, int y, uint color);
void drawing_line(bitmap_t *bmp, int x0, int y0, int x1, int y1, uint color);
void drawing_fill(bitmap_t *bmp, int x, int y, uint color);

void drawing_rect(bitmap_t *bmp, int x, int y, int w, int h, uint color);
void drawing_fillrect(bitmap_t *bmp, int x, int y, int w, int h, uint color);

void drawing_tri(bitmap_t *bmp, int x0, int y0, int x1, int y1, int x2, int y2, uint color);
void drawing_filltri(bitmap_t *bmp, int x0, int y0, int x1, int y1, int x2, int y2, uint color);

void drawing_char(bitmap_t *bmp, char c, int x, int y, uint color);
void drawing_text(bitmap_t *bmp, const char *str, int x, int y, uint color);