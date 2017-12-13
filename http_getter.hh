#ifndef HTTP_GETTER_HH
#define HTTP_GETTER_HH

#include <string>

using std::string;

class HttpGetter {
public:
    virtual string request(const string url) = 0;
};

class QtHttpGetter : public HttpGetter {
public:
    QtHttpGetter(string token) : token(token) { }
    string request(const string url);

private:
    string token;
};

#endif // HTTP_GETTER_HH
