#ifndef HTTP_POSTER_HH
#define HTTP_POSTER_HH

#include <string>
#include "token_store.hh"

using std::string;

class HttpPoster {
public:
    virtual string request(const string url, const string payload) = 0;
};

class QtHttpPoster : public HttpPoster {
public:
    QtHttpPoster(TokenStore* tokenStore) : tokenStore(tokenStore) { }
    string request(const string url, const string payload);

private:
    TokenStore* tokenStore;
};

#endif // HTTP_POSTER_HH 
