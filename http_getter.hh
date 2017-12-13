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
    string request(const string url);
};

#endif // HTTP_GETTER_HH
