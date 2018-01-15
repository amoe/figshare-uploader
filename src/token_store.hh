#ifndef TOKEN_STORE_HH
#define TOKEN_STORE_HH

#include <string>
#include "optional.hpp"

using std::string;
using nonstd::optional;
using nonstd::nullopt;

class TokenStore {
public:
    TokenStore(string token) : token(token) { }
    TokenStore() {
        this->token = nullopt;
    }

    string getToken();
    void setToken(string token);

private:
    optional<string> token;
};


#endif // TOKEN_STORE_HH
