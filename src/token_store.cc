#include "token_store.hh"

string TokenStore::getToken() {
    if (this->token) {
        return this->token.value();
    } else {
        throw std::runtime_error("attempt to read uninitialized token");
    }
}

void TokenStore::setToken(string token) {
    this->token = token;
}
