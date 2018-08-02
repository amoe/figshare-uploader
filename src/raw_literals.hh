#ifndef RAW_LITERALS_HH
#define RAW_LITERALS_HH

// -*- fundamental -*-
// This namespace only even exists because of emacs cc-mode's bizarre and broken
// handling of C++11 raw string literals.

#include <string>

namespace raw_literals {
    const std::string groupApiResponse = R"V0G0N(
        [
            {
                "resource_id": "",
                "name": "The Planet Bethlehem Archive",
                "parent_id": 11353,
                "id": 11611
            },
            {
                "resource_id": "",
                "name": "School of History, Art History and Philosophy",
                "parent_id": 11278,
                "id": 11353
            }
        ]
    )V0G0N";

    const std::string serializedArticleGetResponse = R"V0G0N(
        {
            "id": 5702185
        }
    )V0G0N";


    const std::string serializedFileInfo = R"V0G0N(
        {
            "computed_md5": "",
            "download_url": "https://ndownloader.figshare.com/files/9993997",
            "id": 9993997,
            "is_link_only": false,
            "name": "pb_lc_bcr_c18980000-0004aa.tiff",
            "preview_state": "preview_not_available",
            "size": 23561500,
            "status": "created",
            "supplied_md5": "7b6a523ae2adc8ed0f55e7bb27f39ffc",
            "upload_token": "af4a43ba-1253-4960-8d5a-8b3ed971e9e8",
            "upload_url": "https://fup100010.figshare.com/upload/af4a43ba-1253-4960-8d5a-8b3ed971e9e8",
            "viewer_type": ""
        }
    )V0G0N";


    const std::string serializedFilePartInfo = R"V0G0N(
        {
            "endOffset": 10485759,
            "locked": false,
            "partNo": 1,
            "startOffset": 0,
            "status": "PENDING"
        }
    )V0G0N";


    const std::string serializedUploadContainerInfo = R"V0G0N(
        {
            "md5": "7b6a523ae2adc8ed0f55e7bb27f39ffc",
            "name": "9981382/pb_lc_bcr_c189800000004aa.tiff",
            "parts": [
                {
                    "endOffset": 10485759,
                    "locked": false,
                    "partNo": 1,
                    "startOffset": 0,
                    "status": "PENDING"
                },
                {
                    "endOffset": 20971519,
                    "locked": false,
                    "partNo": 2,
                    "startOffset": 10485760,
                    "status": "PENDING"
                },
                {
                    "endOffset": 23561499,
                    "locked": false,
                    "partNo": 3,
                    "startOffset": 20971520,
                    "status": "PENDING"
                }
            ],
            "size": 23561500,
            "status": "PENDING",
            "token": "1d71cd99-6695-420e-884a-e889571b307b"
        }
    )V0G0N";


    const std::string serializedUploadCreationRequest = R"V0G0N(
        {
          "name": "nonesuch.png",
          "size": 1234000,
          "md5": "9e107d9d372bb6826bd81d3542a419d6"
        }
    )V0G0N";

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
            "license": 1,
            "group_id": 11611,
            "custom_fields": {
                "Contributors": "foo"
            }
        }
    )V0G0N";

    const std::string fakeArticleCreationResponse = R"V0G0N(
        {
            "location": "http://nonexistent.net/"
        }
    )V0G0N";

const std::string generatedRequest = R"V0G0N(
{
    "authors": [
        {
            "name": "Freja Howat-Maxted"
        },
        {
            "name": "Jacob Norris"
        },
        {
            "name": "Leila Sansour"
        }
    ],
    "categories": [
        1703
    ],
    "defined_type": "figure",
    "description": "This is a digital reproduction of a black and white photographic print held in the Library of Congress.\n\nOlive wood carving is an ancient tradition in Palestine that continues to the present day. It involves the skillful chiseling of olive wood and is most common in the Bethlehem region. The trade of olive wood ties in more broadly to the fact that the olive tree is symbolic for Palestinians; the olive tree is connected to the earth, they affirm Palestinian roots in the land.\n\nBethlehem merchants were already trading in locally produced religious devotional objects from olive wood and had identified their potential value in foreign markets from as early as the 1690s. However, it wan't until the late 19th, early 20th centuries that the material experienced a boom and played a part in the global circulation of Bethlehem's souvenir industry. Olive wood continues to be used in the production of souvenirs within the region today.\n\nTaken in the early 20th century, the image exists as part of a wider series produced of traditional dress and people living in the area by G. Eric Matson.\n\nThis image exists as part of the Bethlehem Crafts collection in the Planet Bethlehem Archive.",
    "funding": null,
    "keywords": [
        "Bethlehem Crafts"
    ],
    "license": 1,
    "references": [
        "https://www.loc.gov/item/mpc2004001373/PP/"
    ],
    "title": "Camels laden with olive wood, c.1900-1920"
}
)V0G0N";


};

#endif // RAW_LITERALS_HH
