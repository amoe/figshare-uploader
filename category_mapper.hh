#include <map>
#include <string>

using std::map;
using std::string;

class CategoryMapper {
public:
    CategoryMapper(string jsonInput);
    int mapTitle(string title);
    
private:
    map<string, int> lookup;
};
