#ifndef TOKEN_STORE_HH
#define TOKEN_STORE_HH

#include <string>
#include "optional.hpp"

using std::string;
using nonstd::optional;
using nonstd::nullopt;

class TokenStore {
public:
    virtual string getToken() const = 0;
    virtual void setToken(string token) = 0;
};

class TokenStoreImpl: public TokenStore {
public:
    TokenStoreImpl(string token) : token(token) { }
    TokenStoreImpl() {
        this->token = nullopt;
    }

    string getToken() const override;
    void setToken(string token) override;

private:
    optional<string> token;
};


#endif // TOKEN_STORE_HH
