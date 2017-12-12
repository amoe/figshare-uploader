#ifndef HTTP_POSTER_HH
#define HTTP_POSTER_HH

#include <string>

using std::string;

class HttpPoster {
public:
    virtual string request(const string url, const string payload) = 0;
};

class QtHttpPoster : public HttpPoster {
public:
    QtHttpPoster(string token) : token(token) { }
    string request(const string url, const string payload);

private:
    string token;
};

#endif // HTTP_POSTER_HH 
