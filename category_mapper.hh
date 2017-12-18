#ifndef CATEGORY_MAPPER_HH
#define CATEGORY_MAPPER_HH

#include <map>
#include <string>

using std::map;
using std::string;

class CategoryMapper {
public:
    CategoryMapper(string jsonInput);
    CategoryMapper();
    int mapTitle(string title);
    void setFromJson(string jsonInput);
    
private:
    map<string, int> lookup;
};

#endif // CATEGORY_MAPPER_HH
