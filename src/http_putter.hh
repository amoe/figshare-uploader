#ifndef HTTP_PUTTER_HH
#define HTTP_PUTTER_HH

#include <string>
#include "token_store.hh"

using std::string;

class HttpPutter {
public:
    virtual string request(const string url, const string payload) = 0;
};

class QtHttpPutter : public HttpPutter {
public:
    QtHttpPutter(TokenStore* tokenStore) : tokenStore(tokenStore) { }
    string request(const string url, const string payload);

private:
    TokenStore* tokenStore;
};

#endif // HTTP_PUTTER_HH
