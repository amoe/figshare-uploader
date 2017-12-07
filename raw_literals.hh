// This namespace only even exists because of emacs cc-mode's bizarre and broken
#include <string>

namespace raw_literals {
    const std::string httpbinResponse = R"V0G0N(
        {
          "user-agent": "Mozilla/5.0"
        }
    )V0G0N";

    const std::string categoryResponse = R"V0G0N(
        {
            "id": 1699,
            "parent_id": 1138,
            "title": "Hospitality Management"
        },
        {
            "id": 1700,
            "parent_id": 1138,
            "title": "Real Estate and Valuation Services"
        },
        {
            "id": 1701,
            "parent_id": 1138,
            "title": "Sport and Leisure Management"
        },
        {
            "id": 1702,
            "parent_id": 50,
            "title": "Maori History"
        },
        {
            "id": 1703,
            "parent_id": 50,
            "title": "Middle Eastern and African History"
        },
        {
            "id": 1704,
            "parent_id": 50,
            "title": "New Zealand History"
        },
        {
            "id": 1705,
            "parent_id": 50,
            "title": "North American History"
        },
        {
            "id": 1706,
            "parent_id": 50,
            "title": "Commercial and Contract Law"
        },
        {
            "id": 1707,
            "parent_id": 50,
            "title": "Comparative Law"
        }
    )V0G0N";

    const std::string expectedResult = R"V0G0N(
        {
            "title": "To Serve Man",
            "description": "Some description",
            "keywords": [
                "Bethlehem", "Crafts"
            ],
            "references": [
                "https://www.loc.gov/item/mpc2004001373/PP/"
            ]
        }
    )V0G0N";
};
