# 📘 Micra 2D Facilitator – Kullanım Dökümantasyonu

Sürüm: V1.0
Dil: C++ (SDL2 tabanlı)
Lisans: MicraPL v2.1

## 🎯 Amaç

Micra 2D Facilitator, 2D uzayda noktalar, vektörler ve şekiller üzerinde temel dönüşüm (öteleme, döndürme, ölçekleme) işlemleri yapmak için tasarlanmış, header-only bir C++ yardımcı kütüphanesidir. Özellikle oyun geliştirme, simülasyonlar ve geometrik hesaplamalar sırasında sık kullanılan matematiksel işlemleri basit ve doğrudan fonksiyonlarla sunar. Bu kütüphane, daha büyük olan **Micra Facilitator** projesinin bir parçasıdır ve onunla birlikte veya bağımsız olarak kullanılabilir.

## 📦 Dahil Etme

```cpp
#include "micra_2d_facilitator.hpp"
```

**Bağımlılıklar:**
- SDL2 (geliştirme kütüphanesi) - `SDL_Color` ve `SDL_Point` yapılarını kullanmak için.
- C++ Standart Kütüphanesi (`<vector>`, `<cmath>`, `<string>`)

## 🚀 Hızlı Başlangıç

Bu kütüphane, doğrudan fonksiyon çağrılarıyla çalışır. Bir grup noktayı nasıl döndürebileceğinizi gösteren basit bir örnek:

```cpp
#include "micra_2d_facilitator.hpp"
#include <iostream>

int main() {
    // 1. Bir nokta tanımlayalım (renk bilgisi isteğe bağlıdır)
    Nokta benimNoktam = {10.0f, 5.0f, {255, 0, 0, 255}};

    // 2. Döndürme açısını ayarlayalım (derece cinsinden)
    Birimler aci;
    aci.angles = 45.0; // 45 derece

    // 3. Açıyı radyana çevirelim
    convert_to_radian(aci);

    // 4. Noktayı orijin (0,0) etrafında 45 derece döndürelim
    rotate_point(benimNoktam, 0.0f, 0.0f, aci);

    // 5. Sonucu görelim
    std::cout << "Döndürülmüş Nokta: (" << benimNoktam.x << ", " << benimNoktam.y << ")" << std::endl;

    return 0;
}
```

## 📂 Yapılar (Structs)

Bu kütüphane, verileri düzenli tutmak için birkaç temel yapı tanımlar.

| Struct | Alanlar | Açıklama |
| :--- | :--- | :--- |
| **Screen** | `SDL_Window* window` <br> `SDL_Renderer* renderer` | **Kısmi Kullanım:** Bu yapı, ana kütüphanedeki `draw_` fonksiyonlarıyla birlikte kullanılmak üzere tasarlanmıştır. `setColor` fonksiyonu bu yapıyı kullanır. |
| **Birimler** | `double angles` <br> `double radians` | Bir açının hem derece (`angles`) hem de radyan (`radians`) cinsinden değerlerini tutar. Dönüşüm fonksiyonları bu yapı üzerinde çalışır. |
| **Nokta** | `float x, y` <br> `SDL_Color color` | 2D uzayda bir noktayı (`x`, `y`) ve bu noktayla ilişkili bir rengi (`color`) temsil eder. Renk, `SDL_Color` yapısı kullanılarak tanımlanır. |

> **Not:** `Model` isimli bir yapı ve ilgili fonksiyonlar (`create_model`, `draw_model`) "SONRA GELECEK!" etiketiyle belirtilmiş olup, bu sürümde kullanıma hazır değildir.

## ⚙️ Açı Dönüşüm Fonksiyonları

| Fonksiyon | Açıklama |
| :--- | :--- |
| `convert_to_radian(Birimler& birimler)` | `Birimler` yapısındaki `angles` (derece) değerini kullanarak `radians` alanını hesaplar ve günceller. |
| `convert_to_angle(Birimler& birimler)` | `Birimler` yapısındaki `radians` değerini kullanarak `angles` (derece) alanını hesaplar ve günceller. |

## 🔄 Dönüşüm (Transform) Fonksiyonları

Tüm dönüşüm fonksiyonları, `Nokta` veya `std::vector<Nokta>` üzerinde doğrudan değişiklik yapar (yerinde işlem).

### Döndürme (Rotation)

| Fonksiyon | Açıklama |
| :--- | :--- |
| `rotate_point(Nokta& noktalar, float cx, float cy, const Birimler& birimler)` | Tek bir noktayı, belirtilen merkez (`cx`, `cy`) etrafında, `Birimler` yapısındaki **radyan** açısı kadar döndürür. |
| `rotate_point_all(std::vector<Nokta>& noktalar, float cx, float cy, const Birimler& birimler)` | Bir vektördeki **tüm noktaları**, aynı merkez ve **aynı açı** kullanarak döndürür. |
| `rotate_point_all(std::vector<Nokta>& noktalar, float cx, float cy, const std::vector<Birimler>& birimler)` | Bir vektördeki **her noktayı**, aynı merkez etrafında ancak **kendisine özel açı** kullanarak döndürür. Vektör boyutları eşleşmelidir. |

### Ölçekleme (Scaling)

| Fonksiyon | Açıklama |
| :--- | :--- |
| `scale_point(Nokta& noktalar, float cx, float cy, float scale_x, float scale_y)` | Tek bir noktayı, belirtilen merkeze (`cx`, `cy`) göre `scale_x` ve `scale_y` oranlarında ölçekler. |
| `scale_points_all(std::vector<Nokta>& noktalar, float cx, float cy, float scale_x, float scale_y)` | Bir vektördeki **tüm noktaları**, aynı merkez ve **aynı ölçek** oranlarını kullanarak ölçekler. |
| `scale_points_all(std::vector<Nokta>& noktalar, float cx, float cy, const std::vector<float>& scale_x, const std::vector<float>& scale_y)` | Bir vektördeki **her noktayı**, aynı merkez etrafında ancak **kendisine özel ölçek** oranları kullanarak ölçekler. Vektör boyutları eşleşmelidir. |

### Öteleme (Translation)

| Fonksiyon | Açıklama |
| :--- | :--- |
| `translate_point(Nokta& noktalar, float dx, float dy)` | Tek bir noktayı, `dx` ve `dy` kadar öteler. |
| `translate_points_all(std::vector<Nokta>& noktalar, float dx, float dy)` | Bir vektördeki **tüm noktaları**, `dx` ve `dy` kadar öteler. |

### Bileşik Dönüşüm (Ölçekleme + Döndürme + Öteleme)

| Fonksiyon | Açıklama |
| :--- | :--- |
| `transform_point(Nokta& noktalar, float cx, float cy, float scale_x, float scale_y, float angle_rad, float dx, float dy)` | Tek bir noktaya sırasıyla **Ölçekleme**, **Döndürme** (radyan cinsinden) ve **Öteleme** işlemlerini tek bir çağrıda uygular. |
| `transform_points_all(std::vector<Nokta>& noktalar, float cx, float cy, float scale_x, float scale_y, float angle_rad, float dx, float dy)` | Bir vektördeki **tüm noktalara**, aynı parametrelerle bileşik dönüşümü uygular. |

## 🎨 Çizim Yardımcıları

| Fonksiyon | Açıklama |
| :--- | :--- |
| `setColor(const Nokta& noktalar, Screen screen)` | Verilen `Nokta`'nın `SDL_Color` bilgisini kullanarak, ilgili `Screen`'in renderer'ının çizim rengini ayarlar. Bu fonksiyon, dönüşümü yapılmış noktaları çizmek için ana `micra_facilitator.hpp`'daki `draw_pixel` gibi fonksiyonlarla birlikte kullanılmak üzere tasarlanmıştır. |

## 📌 Gelecek Sürümlerde Eklenecekler

- **Model Yapısı ve İşlevleri:** Bir grup noktayı, bir merkez ve ölçek etrafında bir "model" olarak tanımlamak ve bu modeli çizmek (`create_model`, `draw_model`).
- **Gelişmiş Dönüşümler:** Matris tabanlı dönüşümler veya eğim (shear) desteği.
- **SDL_Point ile Uyumluluk:** Mevcut `Nokta` yapısına ek olarak `SDL_Point` veya `SDL_FPoint` ile çalışabilen fonksiyonlar.

## 🧑💻 Katkıda Bulunma

Projeye katkıda bulunmak, onu daha iyi hale getirmek ve topluluğun bir parçası olmak için harika bir fırsattır. Aşağıdaki kurallar, herkes için adil ve saygılı bir ortam sağlamayı amaçlar.

## Nasıl Katkıda Bulunabilirsin?

- Projeyi forklayın: Kendi hesabınıza bir kopya oluşturun.
- Değişikliklerinizi yapın: Yeni bir özellik ekleyin, bir hatayı düzeltin veya dökümantasyonu iyileştirin.
- Pull request açın: Değişikliklerinizi açıklayan bir PR gönderin.

## 📝 Katkı Koşulları (MicraPL v2.1)

- Lisans Kabulü: Gönderdiğiniz tüm katkılar, projenin genel lisansı olan MicraPL v2.1 koşulları altında değerlendirilir. Bu, katkınızın açık kaynak olarak kalacağı ve bu lisansla dağıtılacağı anlamına gelir.
- Mülkiyet: Katkı sahibi, yazdığı kodun fikri mülkiyet haklarını saklı tutar. Ancak, katkının bu projede kullanılması, çoğaltılması ve dağıtılması için Micraçer'e süresiz, geri alınamaz ve telifsiz bir kullanım lisansı verir.
- Özgünlük: Katkı sahibi, gönderdiği kodun özgün olduğunu ve üçüncü taraf haklarını ihlal etmediğini beyan eder.
- İletişim: Büyük veya yapıcı değişiklikler öncesinde, bir konu (issue) açarak veya Discord üzerinden iletişime geçerek fikir alışverişinde bulunmanız önerilir.

## Katkı Türleri

Her türlü katkı değerlidir:

- Yeni özellik önerileri ve kod eklemeleri
- Hata raporları ve düzeltmeleri
- Dökümantasyon iyileştirmeleri (bu dosya, README, örnekler)
- Örnek projeler ve eğitim içerikleri

Katkılarınız için şimdiden teşekkürler! Birlikte bu projeyi daha iyi bir yere taşıyalım.

### 📄 Lisans

Bu proje MicraPL v2.1 ile lisanslanmıştır. Detaylar için [LICENSE](https://github.com/Micracher/Micra-Facilitator/blob/main/LICENSE.md) dosyasına bakın.

### ✍️ Yazar

Micraçer (Miraç)

---

**Sürüm Geçmişi:**

| Sürüm | Tarih | Değişiklikler |
| :--- | :--- | :--- |
| V1.0 | 2026 | İlk kararlı sürüm. Nokta, açı dönüşümleri ve döndürme/ölçekleme/öteleme fonksiyonları eklendi. |
