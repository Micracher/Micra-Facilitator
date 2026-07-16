/*
 * Şimdilik lisanssızdır. Herkes kullanabilir, kopyalayabilir, 
 * dağıtabilir ve ticari olarak satabilir!
 * 
 * Ancak ileride MicraPL v1 ile lisanslanacaktır.
 * Ayrıca MicraPL v1 ile lisanslanınca, oyun yapmayı 
 * kolaylaştıran fonksiyonlar eklenecektir.
 * 
 * Hazır olun! =D
 */ 

#ifndef LOAD_H
#define LOAD_H

struct Part {
    int x, y, w, h, argb;
};

struct Player {
    double speed = 0.25;
    double run = 1;
    int hp = 100;
};

struct Team {
    const char* name;
    const char* description;
    int color;
};

#endif
