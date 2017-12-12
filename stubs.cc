#include <string>
#include <vector>

#include "http_poster.hh"
#include "responses.hh"
#include "stubs.hh"

using std::string;
using std::vector;

class Category {
public:
    Category(string title) : title(title) { }

private:
    string title;
};

class CategoryLister { 
public:
    virtual vector<Category> listCategories() = 0;
};

class StubCategoryLister : public CategoryLister {
    StubCategoryLister() {
        cannedData.push_back(Category("Maori History"));
    }
    vector<Category> listCategories();
    
private:
    vector<Category> cannedData;
};

vector<Category> StubCategoryLister::listCategories() {
    return this->cannedData;
}


// HTTP stubs

string StubHttpPoster::request(const string url, const string payload) {
    return this->cannedResponse;
}


// {
//     "code": "BadRequest",
//     "message": "funding: None is not of type 'string'"
// }
