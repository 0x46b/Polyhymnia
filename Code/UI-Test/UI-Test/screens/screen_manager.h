#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#include "screen_types.h"

class ScreenManager {
    private:
        ScreenType _currentScreenType;
        lv_obj_t* _currentScreen;

    public:
        void switch_to_screen(ScreenType type);
        void 
};

#endif