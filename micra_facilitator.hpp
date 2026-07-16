/*
 * Bu lisans, özetle; bireysel ve eğitim kullanımına ücretsizdir. 
 * Ticari ve kurumsal kullanım için yazılı izin ve lisans anahtarı gereklidir.
 * Detaylar ve tam metin için: https://github.com/Micracher/Micra-Facilitator/blob/main/LICENSE.md
 */

#pragma once

#ifndef MICRA_FACILITATOR
#define MICRA_FACILITATOR

#include <SDL2/SDL.h>
#include <iostream>

typedef struct Key {
    bool n0, n1, n2, n3, n4, n5, n6, n7, n8, n9;
    bool a, b, c, d, e, f, g, h, i, j, k, l, m;
    bool n, o, p, q, r, s, t, u, v, w, x, y, z;
    bool up, down, left, right;
    bool space, shift, ctrl, alt;
    bool f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
    bool escape, enter, tab, backspace;
    bool capslock, numlock, lctrl, rctrl, lshift, rshift, lalt, ralt;
    bool quit;
} Key;

typedef struct Screen {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Screen;

inline bool start_sdl2(const Uint32 flags) {
    if (SDL_Init(flags) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline void destroy_screen(Screen screen, bool window = true, bool renderer = true) {
    if (renderer) SDL_DestroyRenderer(screen.renderer);
    if (window) SDL_DestroyWindow(screen.window);
}

inline void quit_sdl2(Screen screen) {
    if (screen.renderer) SDL_DestroyRenderer(screen.renderer);
    if (screen.window) SDL_DestroyWindow(screen.window);
    SDL_Quit();
}

inline bool quit_press() {
    SDL_Event e;
    if (SDL_PollEvent(&e) && e.type == SDL_QUIT) {
        return false;
    }
    return true;
}

inline bool create_window(Screen& screen, const char* title, int x, int y, int w, int h, Uint32 flags) {
    SDL_Window* win = SDL_CreateWindow(title, x, y, w, h, flags);

    if (!win) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        screen.window = nullptr;
        return false;
    }

    screen.window = win;
    return true;
}

inline bool create_renderer(Screen& screen, Uint32 flags, int index = -1) {
    SDL_Renderer* renderer = SDL_CreateRenderer(screen.window, index, flags);

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        screen.renderer = nullptr;
        return false;
    }

    screen.renderer = renderer;
    return true;
}

inline void scan_keyboard(Key& key) {
    const uint8_t* state = SDL_GetKeyboardState(nullptr);

    key.n0 = state[SDL_SCANCODE_0];
    key.n1 = state[SDL_SCANCODE_1];
    key.n2 = state[SDL_SCANCODE_2];
    key.n3 = state[SDL_SCANCODE_3];
    key.n4 = state[SDL_SCANCODE_4];
    key.n5 = state[SDL_SCANCODE_5];
    key.n6 = state[SDL_SCANCODE_6];
    key.n7 = state[SDL_SCANCODE_7];
    key.n8 = state[SDL_SCANCODE_8];
    key.n9 = state[SDL_SCANCODE_9];

    key.a = state[SDL_SCANCODE_A];
    key.b = state[SDL_SCANCODE_B];
    key.c = state[SDL_SCANCODE_C];
    key.d = state[SDL_SCANCODE_D];
    key.e = state[SDL_SCANCODE_E];
    key.f = state[SDL_SCANCODE_F];
    key.g = state[SDL_SCANCODE_G];
    key.h = state[SDL_SCANCODE_H];
    key.i = state[SDL_SCANCODE_I];
    key.j = state[SDL_SCANCODE_J];
    key.k = state[SDL_SCANCODE_K];
    key.l = state[SDL_SCANCODE_L];
    key.m = state[SDL_SCANCODE_M];
    key.n = state[SDL_SCANCODE_N];
    key.o = state[SDL_SCANCODE_O];
    key.p = state[SDL_SCANCODE_P];
    key.q = state[SDL_SCANCODE_Q];
    key.r = state[SDL_SCANCODE_R];
    key.s = state[SDL_SCANCODE_S];
    key.t = state[SDL_SCANCODE_T];
    key.u = state[SDL_SCANCODE_U];
    key.v = state[SDL_SCANCODE_V];
    key.w = state[SDL_SCANCODE_W];
    key.x = state[SDL_SCANCODE_X];
    key.y = state[SDL_SCANCODE_Y];
    key.z = state[SDL_SCANCODE_Z];

    key.up = state[SDL_SCANCODE_UP];
    key.down = state[SDL_SCANCODE_DOWN];
    key.left = state[SDL_SCANCODE_LEFT];
    key.right = state[SDL_SCANCODE_RIGHT];

    key.space = state[SDL_SCANCODE_SPACE];

    key.lshift = state[SDL_SCANCODE_LSHIFT];
    key.rshift = state[SDL_SCANCODE_RSHIFT];
    key.shift = key.lshift || key.rshift;

    key.lctrl = state[SDL_SCANCODE_LCTRL];
    key.rctrl = state[SDL_SCANCODE_RCTRL];
    key.ctrl = key.lctrl || key.rctrl;

    key.lalt = state[SDL_SCANCODE_LALT];
    key.ralt = state[SDL_SCANCODE_RALT];
    key.alt = key.lalt || key.ralt;

    key.f1 = state[SDL_SCANCODE_F1];
    key.f2 = state[SDL_SCANCODE_F2];
    key.f3 = state[SDL_SCANCODE_F3];
    key.f4 = state[SDL_SCANCODE_F4];
    key.f5 = state[SDL_SCANCODE_F5];
    key.f6 = state[SDL_SCANCODE_F6];
    key.f7 = state[SDL_SCANCODE_F7];
    key.f8 = state[SDL_SCANCODE_F8];
    key.f9 = state[SDL_SCANCODE_F9];
    key.f10 = state[SDL_SCANCODE_F10];
    key.f11 = state[SDL_SCANCODE_F11];
    key.f12 = state[SDL_SCANCODE_F12];

    key.escape = state[SDL_SCANCODE_ESCAPE];
    key.enter = state[SDL_SCANCODE_KP_ENTER] || state[SDL_SCANCODE_RETURN];
    key.tab = state[SDL_SCANCODE_TAB];
    key.backspace = state[SDL_SCANCODE_BACKSPACE];
    key.capslock = state[SDL_SCANCODE_CAPSLOCK];
    key.numlock = state[SDL_SCANCODE_NUMLOCKCLEAR];
}

inline bool render_draw_pixel(Screen screen, int x, int y, SDL_Color c) {
    SDL_SetRenderDrawColor(screen.renderer, c.r, c.g, c.b, c.a);
    int error = SDL_RenderDrawPoint(screen.renderer, x, y);

    if (error != 0) {
        std::cerr << "SDL_RenderDrawPoint Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_RenderPresent(screen.renderer);
    return true;
}

inline bool render_draw_line(Screen screen, int x1, int y1, int x2, int y2, SDL_Color c) {
    SDL_SetRenderDrawColor(screen.renderer, c.r, c.g, c.b, c.a);
    int error = SDL_RenderDrawLine(screen.renderer, x1, y1, x2, y2);

    if (error != 0) {
        std::cerr << "SDL_RenderDrawLine Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_RenderPresent(screen.renderer);
    return true;
}

inline bool render_draw_rect(Screen screen, SDL_Rect rect, SDL_Color c) {
    SDL_SetRenderDrawColor(screen.renderer, c.r, c.g, c.b, c.a);
    int error = SDL_RenderDrawRect(screen.renderer, &rect);

    if (error != 0) {
        std::cerr << "SDL_RenderDrawRect Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_RenderPresent(screen.renderer);
    return true;
}

inline bool render_draw_image(Screen screen, SDL_Surface* image, SDL_Rect* dest) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(screen.renderer, image);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_RenderCopy(screen.renderer, texture, NULL, dest);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(screen.renderer);
    return true;
}

#endif
