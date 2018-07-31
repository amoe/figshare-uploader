#ifndef HTTP_GETTER_HH
#define HTTP_GETTER_HH

#include <string>
#include <gmock/gmock.h>
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

class MockHttpGetter : public HttpGetter {
public:
    MOCK_METHOD1(request, string(string url));
};


#endif // HTTP_GETTER_HH
