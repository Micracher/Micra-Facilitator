/*
 * SPDX-License-Identifier: MicraPL-2.1
 *
 * Bu dosya, Micra Facilitator (MicraP) projesinin bir parçasıdır.
 * Detaylı lisans koşulları için:
 * https://github.com/Micracher/Micra-Facilitator/blob/main/LICENSE.md
 *
 * ÖZET:
 * - Bireysel, eğitim ve araştırma kullanımı ÜCRETSİZDİR.
 * - Ticari, kurumsal veya gelir getirici her türlü kullanım
 *   için YAZILI İZİN ve LİSANS ANAHTARI gereklidir.
 * - İzinsiz ticari kullanım LİSANS İHLALİDİR ve yaptırıma tabidir.
 *
 * Telif Hakkı © 2026 - Micraçer / Miraç
 */

#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <string>

typedef struct Screen {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Screen;

typedef struct Birimler {
    double angles = 0;
    double radians = 0;
} Birimler;

typedef struct Nokta {
    float x, y;
    SDL_Color color;
} Nokta;

/**SONRA GELECEK!**/
/*typedef struct Model {
    std::string img_path;
    std::vector<SDL_Point> points;
    float cx, cy;
    float scale;
} Model;*/

inline void setColor(const Nokta& noktalar, Screen screen) { SDL_SetRenderDrawColor(screen.renderer, noktalar.color.r, noktalar.color.g, noktalar.color.b, noktalar.color.a); }

inline void convert_to_radian(Birimler& birimler) {
    birimler.radians = birimler.angles * 3.14159265359 / 180.0;
}

inline void convert_to_angle(Birimler& birimler) {
    birimler.angles = birimler.radians / 3.14159265359 * 180.0;
}

inline void rotate_point(Nokta& noktalar, float cx, float cy, const Birimler& birimler) {
    float dx = noktalar.x - cx;
    float dy = noktalar.y - cy;
    float cos_a = cos(birimler.radians);
    float sin_a = sin(birimler.radians);
    noktalar.x = cx + dx * cos_a - dy * sin_a;
    noktalar.y = cy + dx * sin_a + dy * cos_a;
}

inline void rotate_point_all(std::vector<Nokta>& noktalar, float cx, float cy, const Birimler& birimler) {
    float cos_a = cos(birimler.radians);
    float sin_a = sin(birimler.radians);
    for (size_t i = 0; i < noktalar.size(); i++) {
        float dx = noktalar[i].x - cx;
        float dy = noktalar[i].y - cy;
        noktalar[i].x = cx + dx * cos_a - dy * sin_a;
        noktalar[i].y = cy + dx * sin_a + dy * cos_a;
    }
}

inline void rotate_point_all(std::vector<Nokta>& noktalar, float cx, float cy, const std::vector<Birimler>& birimler) {
    if (noktalar.size() != birimler.size()) return;
    for (size_t i = 0; i < noktalar.size(); i++) {
        float dx = noktalar[i].x - cx;
        float dy = noktalar[i].y - cy;
        float cos_a = cos(birimler[i].radians);
        float sin_a = sin(birimler[i].radians);
        noktalar[i].x = cx + dx * cos_a - dy * sin_a;
        noktalar[i].y = cy + dx * sin_a + dy * cos_a;
    }
}

inline void scale_point(Nokta& noktalar, float cx, float cy, float scale_x, float scale_y) {
    noktalar.x = cx + (noktalar.x - cx) * scale_x;
    noktalar.y = cy + (noktalar.y - cy) * scale_y;
}

inline void scale_points_all(std::vector<Nokta>& noktalar, float cx, float cy, float scale_x, float scale_y) {
    for (size_t i = 0; i < noktalar.size(); i++) {
        scale_point(noktalar[i], cx, cy, scale_x, scale_y);
    }
}

inline void scale_points_all(std::vector<Nokta>& noktalar, float cx, float cy, const std::vector<float>& scale_x, const std::vector<float>& scale_y) {
    if (noktalar.size() != scale_x.size() || noktalar.size() != scale_y.size()) return;
    for (size_t i = 0; i < noktalar.size(); i++) {
        scale_point(noktalar[i], cx, cy, scale_x[i], scale_y[i]);
    }
}

inline void translate_point(Nokta& noktalar, float dx, float dy) {
    noktalar.x += dx;
    noktalar.y += dy;
}

inline void translate_points_all(std::vector<Nokta>& noktalar, float dx, float dy) {
    for (auto& n : noktalar) {
        translate_point(n, dx, dy);
    }
}

inline void transform_point(Nokta& noktalar, float cx, float cy, float scale_x, float scale_y, float angle_rad, float dx, float dy) {
    noktalar.x = cx + (noktalar.x - cx) * scale_x;
    noktalar.y = cy + (noktalar.y - cy) * scale_y;

    float dx_n = noktalar.x - cx;
    float dy_n = noktalar.y - cy;
    float cos_a = cos(angle_rad);
    float sin_a = sin(angle_rad);
    noktalar.x = cx + dx_n * cos_a - dy_n * sin_a;
    noktalar.y = cy + dx_n * sin_a + dy_n * cos_a;

    noktalar.x += dx;
    noktalar.y += dy;
}

inline void transform_points_all(std::vector<Nokta>& noktalar, float cx, float cy, float scale_x, float scale_y, float angle_rad, float dx, float dy) {
    for (auto& n : noktalar) {
        transform_point(n, cx, cy, scale_x, scale_y, angle_rad, dx, dy);
    }
}

/**SONRA GELECEK!**/
/*inline Model create_model(std::vector<Nokta> noktalar, float cx, float cy, float scale) {
    Model model;

    model.cx = cx;
    model.cy = cy;
    model.scale = scale;

    for (size_t i = 0; i < noktalar.size(); i++) {
        model.points[i].x = noktalar[i].x;
        model.points[i].y = noktalar[i].y;
    }

    return model;
}

inline bool draw_model(Model model) {
}*/
