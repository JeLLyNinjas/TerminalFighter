#pragma once

#include <map>

class JN_TTF {
    public: 
        JN_TTF();
        ~JN_TTF();
        int open_font(std::string path, int font_size);

    private:
        sdt::map<std::string, TTF_Font*> font_map_;
};
