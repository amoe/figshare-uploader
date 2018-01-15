#include <string>

class Settings {
public:
    static std::string getTokenOrEmpty();
    static void setToken(std::string newToken);
};



