/*

MIT License

Copyright (c) 2023 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

This file is part of the HAGL graphics library:
https://github.com/tuupola/hagl


SPDX-License-Identifier: MIT

*/

#ifndef _HAGL_BACKEND_H
#define _HAGL_BACKEND_H

#include <stddef.h>

#include <hardware/spi.h>

#include "hagl/bitmap.h"
#include "hagl/window.h"
#include "hagl/color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
    /* Common to all surfaces. */
    int16_t width;
    int16_t height;
    uint8_t depth;
    hagl_window_t clip;
    void (*put_pixel)(void *self, int16_t x0, int16_t y0, hagl_color_t color);
    hagl_color_t (*get_pixel)(void *self, int16_t x0, int16_t y0);
    hagl_color_t (*color)(void *self, uint8_t r, uint8_t g, uint8_t b);
    void (*blit)(void *self, int16_t x0, int16_t y0, hagl_bitmap_t *src);
    void (*scale_blit)(void *self, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, hagl_bitmap_t *src);
    void (*hline)(void *self, int16_t x0, int16_t y0, uint16_t width, hagl_color_t color);
    void (*vline)(void *self, int16_t x0, int16_t y0, uint16_t height, hagl_color_t color);

    /* Specific to backend. */
    size_t (*flush)(void *self);
    void (*close)(void *self);
    uint8_t *buffer;
    uint8_t *buffer2;

    int scl;
    int sda;
    int dc;
    int cs;
    spi_inst_t* spi;
    uint16_t prev_x1, prev_x2, prev_y1, prev_y2;

} hagl_backend_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HAGL_BACKEND_H */