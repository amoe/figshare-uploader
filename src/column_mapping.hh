// New column indexes for the XLSX schema should be put in this namespace

// These are zero-based indexes, because they are used to reference into raw
// vector<string> (rather than being passed to the excel reader API)

namespace column_mapping {
    const int CONTRIBUTORS = 10;
    const int REFERENCES = 6;
    const int RELATION = 15;
    const int IDENTIFIER = 19;
    const int GROUP_NAME = 21;

    const map<string, int> CUSTOM_FIELDS = {
        {"Contributors", CONTRIBUTORS}
    };
};
