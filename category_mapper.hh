#ifndef CATEGORY_MAPPER_HH
#define CATEGORY_MAPPER_HH

#include <map>
#include <string>
#include "http_getter.hh"

// This getter knows how to initialize itself because it may be initialized
// "just in time".

using std::map;
using std::string;

class CategoryMapper {
public:
    CategoryMapper(string jsonInput);
    CategoryMapper();
    CategoryMapper(HttpGetter* getter);
    int mapTitle(string title);
    void setFromJson(string jsonInput);
    
private:
    void initializeLookup();
    map<string, int> lookup;
    HttpGetter* getter;
};

#endif // CATEGORY_MAPPER_HH
