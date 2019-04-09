#ifndef MODEL_HH
#define MODEL_HH

#include <string>

using std::string;

class Model {
public:
    void setSourceFile(string newSourceFile);

private:
    string sourceFile;
};

#endif /* MODEL_HH */
