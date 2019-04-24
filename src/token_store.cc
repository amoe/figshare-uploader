#include <stdexcept>
#include "token_store.hh"

string TokenStoreImpl::getToken() const {
    if (this->token) {
        return this->token.value();
    } else {
        throw std::runtime_error("attempt to read uninitialized token");
    }
}

void TokenStoreImpl::setToken(string token) {
    this->token = token;
}
