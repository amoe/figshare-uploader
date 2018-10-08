#ifndef CUSTOM_FIELDS_HH
#define CUSTOM_FIELDS_HH

#include <vector>
#include <string>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

using std::string;
using std::vector;

enum class FieldEncoder {
    STRING, LIST
};

struct CustomFieldSpecification {
    string name;             // key that will be used in result
    int position;            // column position to expect result at
    FieldEncoder encoder;    // way the result will appear in the JSON
};

class CustomFieldDatum {
public:
    CustomFieldDatum(
        CustomFieldSpecification specification, string content
    ): specification(specification), content(content) { }

    QJsonValue getJsonValue() const;
    string getJsonKey() const;

private:
    CustomFieldSpecification specification;
    string content;
};

// The CustomFieldSet has to be copy-safe.  That means we can't use polymorphism
// to implement the encoding behaviour.
class CustomFieldSet {
public:
    CustomFieldSet() { }

    void add(CustomFieldDatum datum);
    QJsonObject render() const;

private:
    vector<CustomFieldDatum> content;
};

#endif /* CUSTOM_FIELDS_HH */
