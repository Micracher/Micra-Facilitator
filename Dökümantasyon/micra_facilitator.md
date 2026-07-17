# 📘 Micra Facilitator – Kullanım Dökümantasyonu

**Sürüm:** V2.0  
**Dil:** C++ (SDL2 tabanlı)  
**Lisans:** MicraPL v1  

---

## 🎯 Amaç

Micra Facilitator, **SDL2'yi sarmalayan**, 2D oyun geliştirmeyi kolaylaştıran **header-only** bir C++ kütüphanesidir.  
Pencere açmaktan, klavye/fare okumaya, çizim yapmaktan texture yönetimine kadar her şeyi basitleştirir.

---

## 📦 Dahil Etme

```cpp
#include "micra_facilitator.hpp"
```

**Bağımlılıklar:**
- SDL2 (geliştirme kütüphanesi)
- (İleride SDL_image, SDL_ttf, SDL_mixer isteğe bağlı)

---

## 🚀 Hızlı Başlangıç

```cpp
#include "micra_facilitator.hpp"

int main() {
    start_sdl2(SDL_INIT_EVERYTHING);

    Screen ekran;
    create_window(ekran, "Oyun Pencerem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    create_renderer(ekran, SDL_RENDERER_ACCELERATED);

    SDL_Color kirmizi = {255, 0, 0, 255};

    LOOP {
        if (quit_press()) break;

        draw_pixel(ekran, 400, 300, kirmizi);
        DELAY(16);
    }

    quit_sdl2(ekran);
    return 0;
}
```

---

## 📂 Yapılar (Structs)

| Struct | Alanlar | Açıklama |
| :--- | :--- | :--- |
| `Key` | Tüm tuşlar (harf, sayı, F1-F12, shift, ctrl, alt, ok tuşları vb.) | Klavye durumunu tutar. |
| `Mouse` | `x, y, dx, dy, butonlar, tekerlek` | Fare durumunu tutar. |
| `Screen` | `SDL_Window* window`, `SDL_Renderer* renderer` | Pencere ve renderer çiftini tutar. |

---

## ⚙️ Başlatma & Kapatma

| Fonksiyon | Açıklama |
| :--- | :--- |
| `start_sdl2(flags)` | SDL2'yi başlatır. `flags` = `SDL_INIT_EVERYTHING` önerilir. |
| `quit_sdl2(screen)` | Pencere, renderer ve SDL2'yi kapatır. |
| `destroy_screen(screen, window, renderer)` | Sadece pencere/renderer'ı kapatır, `SDL_Quit()` çağırmaz. |

---

## 🪟 Pencere & Renderer

| Fonksiyon | Açıklama |
| :--- | :--- |
| `create_window(screen, başlık, x, y, w, h, flags)` | Pencere oluşturur. |
| `create_renderer(screen, flags, index)` | Renderer oluşturur. `index=-1` otomatik seçer. |
| `delay(ms)` | Belirtilen milisaniye bekler. |

---

## ⌨️ Klavye & Fare

| Fonksiyon | Açıklama |
| :--- | :--- |
| `scan_keyboard(key)` | Tüm tuş durumlarını `Key` yapısına doldurur. |
| `scan_mouse(mouse)` | Fare hareket, buton ve tekerlek olaylarını okur. |
| `quit_press()` | Eğer `SDL_QUIT` olayı varsa `true` döner. |

---

## 🎨 Çizim Fonksiyonları

| Fonksiyon | Açıklama |
| :--- | :--- |
| `draw_pixel(screen, x, y, color)` | Bir piksel çizer. |
| `draw_line(screen, x1, y1, x2, y2, color)` | Çizgi çizer. |
| `draw_rect(screen, rect, color)` | Dikdörtgen çerçevesi çizer. |
| `draw_texture(screen, texture, x, y)` | Texture'ı orijinal boyutunda çizer. |

> **Not:** `draw_` fonksiyonları her çağrıda `SDL_RenderPresent` çağırır. Çok sayıda çizim yapıyorsan, döngü sonunda elle `SDL_RenderPresent` çağırmak daha performanslıdır.

---

## 🖼️ Texture İşlemleri

| Fonksiyon | Açıklama |
| :--- | :--- |
| `load_texture(screen, path)` | BMP dosyasını yükler, `SDL_Texture*` döner. |
| `draw_texture(screen, texture, x, y)` | Texture'ı ekrana basar. |

---

## ⏱️ Zaman Yönetimi

| Fonksiyon | Açıklama |
| :--- | :--- |
| `get_delta_time()` | Son çağrıdan bu yana geçen süreyi saniye cinsinden döndürür. |
| `get_fps()` | Son 1 saniyedeki kare sayısını (FPS) döndürür. |

---

## 🧩 Makrolar (Kolaylık)

| Makro | Açıklama |
| :--- | :--- |
| `LOOP` | `while(true)` yerine kullanılır. |
| `DELAY(ms)` | `SDL_Delay(ms)` yerine kullanılır. |

---

## 🧪 Örnek Oyun Döngüsü (Tam)

```cpp
#include "micra_facilitator.hpp"

int main() {
    start_sdl2(SDL_INIT_EVERYTHING);

    Screen screen;
    create_window(screen, "Örnek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    create_renderer(screen, SDL_RENDERER_ACCELERATED);

    Key tus;
    Mouse fare;
    SDL_Color beyaz = {255, 255, 255, 255};

    LOOP {
        if (quit_press()) break;

        scan_keyboard(tus);
        if (tus.escape) break;

        if (tus.space) {
            draw_pixel(screen, 100, 100, beyaz);
        }

        DELAY(16);
    }

    quit_sdl2(screen);
    return 0;
}
```

---

## ⚠️ Hata Yönetimi

Tüm `create_` ve `draw_` fonksiyonları, hata durumunda `std::cerr` ile hata mesajı basar ve `false` veya `nullptr` döner.

---

## 📌 Gelecek Sürümlerde Eklenecekler

- `draw_texture_ex()` → Döndürme + ölçekleme
- Font desteği (`SDL_ttf`)
- Ses desteği (`SDL_mixer`)
- Oyun fiziği yardımcıları

---

## 🧑‍💻 Katkıda Bulunma

Bu projeye yapılan her katkı (pull request, kod ekleme, hata düzeltmesi),  
**MicraPL v1** lisansına tabidir.

Katkıda bulunanlar, yazdıkları kodun mülkiyetinin **Micraçer'e devredildiğini** kabul eder.  
Lisans detayları için: [LICENSE](./LICENSE)

### Nasıl Katkıda Bulunabilirsin?
1. Projeyi forklayın.
2. Değişikliklerinizi yapın.
3. Pull request açın.

**Not:** Katkı sahibi, kodun özgün olduğunu ve üçüncü taraf haklarını ihlal etmediğini beyan eder.

---

## 📄 Lisans

MicraPL v1 – Detaylar için `LICENSE` dosyasına bakın.

---

### ✍️ Yazar

Micraçer (Miraç)

---

**Sürüm Geçmişi:**

| Sürüm | Tarih | Değişiklikler |
| :--- | :--- | :--- |
| V1.0 | 2024 | Temel SDL2 sarmalayıcı |
| V1.5 | 2025 | Texture, FPS, delta time eklendi |
| V2.0 | 2026 | İsim düzenlemeleri, `draw_` öneki, dökümantasyon |
