#ifndef COLUMN_MAPPING_HH
#define COLUMN_MAPPING_HH

// New column indexes for the XLSX schema should be put in this namespace

// These are zero-based indexes, because they are used to reference into raw
// vector<string> (rather than being passed to the excel reader API)

// NB: If you modify these, you also need to modify the minimum and maximum
// columns in xlsx_reader.cc


#include <string>
#include <vector>
#include "custom_fields.hh"

using std::string;
using std::vector;

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

    // Update this if you add fields.  It should be n+1 where n is the highest
    // int above.
    const int MAX_FIELD = 24;
    const string MINIMUM_COLUMN = "A";
    const string MAXIMUM_COLUMN = "X";

    const vector<CustomFieldSpecification> CUSTOM_FIELDS = {
        {"Creator", CREATOR, FieldEncoder::STRING},
        {"Contributors", CONTRIBUTORS, FieldEncoder::STRING},
        {"Date", DATE, FieldEncoder::STRING},
        {"Type", TYPE, FieldEncoder::STRING},
        {"Source", SOURCE, FieldEncoder::STRING},
        {"Language", LANGUAGE, FieldEncoder::STRING},
        {"Relation", RELATION, FieldEncoder::STRING},
        {"Temporal", TEMPORAL, FieldEncoder::STRING},
        {"Spatial", SPATIAL, FieldEncoder::STRING},
        {"Spatial Relation", SPATIAL_RELATION, FieldEncoder::STRING},
        {"Identifier", IDENTIFIER, FieldEncoder::STRING},
        {"Rights", RIGHTS, FieldEncoder::STRING},
        {"Project", PROJECT, FieldEncoder::LIST},
        {"Collection", COLLECTION, FieldEncoder::LIST}
    };
};


#endif /* COLUMN_MAPPING_HH */
