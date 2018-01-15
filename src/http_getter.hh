#ifndef HTTP_GETTER_HH
#define HTTP_GETTER_HH

#include <string>
#include "token_store.hh"


using std::string;

class HttpGetter {
public:
    virtual string request(const string url) = 0;
};

class QtHttpGetter : public HttpGetter {
public:
    QtHttpGetter(TokenStore* tokenStore) : tokenStore(tokenStore) { }
    string request(const string url);

private:
    TokenStore* tokenStore;
};

#endif // HTTP_GETTER_HH
