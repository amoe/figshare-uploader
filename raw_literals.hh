// -*- fundamental -*-
// This namespace only even exists because of emacs cc-mode's bizarre and broken
// handling of C++11 raw string literals.

#include <string>

namespace raw_literals {
    const std::string httpbinResponse = R"V0G0N(
        {
          "user-agent": "Mozilla/5.0"
        }
    )V0G0N";

    const std::string categoryResponse = R"V0G0N(
        [
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
        ]
    )V0G0N";

    const std::string licensesResponse = R"V0G0N(
        [
            {
                "name": "CC BY 4.0",
                "url": "https://creativecommons.org/licenses/by/4.0/",
                "value": 1
            },
            {
                "name": "CC0",
                "url": "https://creativecommons.org/publicdomain/zero/1.0/",
                "value": 2
            },
            {
                "name": "MIT",
                "url": "https://opensource.org/licenses/MIT",
                "value": 3
            },
            {
                "name": "GPL",
                "url": "https://www.gnu.org/copyleft/gpl.html",
                "value": 4
            },
            {
                "name": "GPL 2.0+",
                "url": "https://www.gnu.org/licenses/gpl-2.0.html",
                "value": 5
            },
            {
                "name": "GPL 3.0+",
                "url": "https://www.gnu.org/licenses/gpl-3.0.html",
                "value": 6
            },
            {
                "name": "Apache 2.0",
                "url": "https://www.apache.org/licenses/LICENSE-2.0.html",
                "value": 7
            }
        ]
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
            ],
            "categories": [
                1703
            ],
            "authors": [
                {"name": "Freja Howat-Maxted"}
            ],
            "funding": "Some grant number",
            "defined_type": "figure",
            "license": 1
        }
    )V0G0N";

    const std::string fakeArticleCreationResponse = R"V0G0N(
        {
            "location": "http://nonexistent.net/"
        }
    )V0G0N";
};
