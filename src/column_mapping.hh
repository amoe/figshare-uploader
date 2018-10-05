// New column indexes for the XLSX schema should be put in this namespace

// These are zero-based indexes, because they are used to reference into raw
// vector<string> (rather than being passed to the excel reader API)

// NB: If you modify these, you also need to modify the minimum and maximum
// columns in xlsx_reader.cc

namespace column_mapping {
    const int CREATOR = 9;
    const int CONTRIBUTORS = 10;
    const int DATE = 11;
    const int TYPE = 12;
    const int SOURCE = 13;
    const int LANGUAGE = 14;
    const int RELATION = 15;
    const int TEMPORAL = 16;
    const int SPATIAL = 17;
    const int SPATIAL_RELATION = 18;
    const int IDENTIFIER = 19;
    const int RIGHTS = 20;
    const int REFERENCES = 6;
    const int GROUP_NAME = 21;
    const int PROJECT = 22;
    const int COLLECTION = 23;

    // Update this if you add fields.
    const int MAX_FIELD = 23;


    const map<string, int> CUSTOM_FIELDS = {
        {"Creator", CREATOR},
        {"Contributors", CONTRIBUTORS},
        {"Date", DATE},
        {"Type", TYPE},
        {"Source", SOURCE},
        {"Language", LANGUAGE},
        {"Relation", RELATION},
        {"Temporal", TEMPORAL},
        {"Spatial", SPATIAL},
        {"Spatial Relation", SPATIAL_RELATION},
        {"Identifier", IDENTIFIER},
        {"Rights", RIGHTS}
    };
};
