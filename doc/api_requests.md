# API REQUESTS

To do simple demo API requests, you can use any http client.  I commonly use the
httpie tool.

nb: the token shown here is not a real or working token.

    amoe@cslp019129 $ http "https://api.figshare.com/v2/account/articles/6455465" "Authorization: token 84b30f70472ac768a9188a8a065323eb61cae33db7f2e69bc635cd4e14308d25907b68e0414be1958dbf2490232989098760d9a33ba07e2a38d480e70cf1041a"
    HTTP/1.1 200 OK
    Access-Control-Allow-Headers: Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Authorization
    Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
    Access-Control-Max-Age: 3600
    Connection: keep-alive
    Content-Encoding: gzip
    Content-Length: 1100
    Content-Type: application/json; charset=UTF-8
    Date: Mon, 16 Jul 2018 09:49:16 GMT
    Server: nginx
    Vary: Accept-Encoding

    {
        "authors": [
            {
                "full_name": "David Banks", 
                "id": 4602601, 
                "is_active": true, 
                "orcid_id": "", 
                "url_name": "David_Banks"
            }, 
            {
                "full_name": "Freja Howat-Maxted", 
                "id": 4671640, 
                "is_active": false, 
                "orcid_id": "", 
                "url_name": "_"
            }, 
            {
                "full_name": "Jacob Norris", 
                "id": 4677997, 
                "is_active": false, 
                "orcid_id": "", 
                "url_name": "_"
            }, 
            {
                "full_name": "Leila Sansour", 
                "id": 4598989, 
                "is_active": false, 
                "orcid_id": "", 
                "url_name": "_"
            }
        ], 
        "categories": [
            {
                "id": 1703, 
                "parent_id": 50, 
                "title": "Middle Eastern and African History"
            }
        ], 
        "citation": "Banks, David; Howat-Maxted, Freja; Norris, Jacob; Sansour, Leila (2018): Watering a garden from the open Wadi Biyar aqueduct, Solomon's Pools, c.1934-1939. figshare. Figure.", 
        "confidential_reason": "", 
        "created_date": "2018-06-07T11:39:13Z", 
        "custom_fields": [], 
        "defined_type": 1, 
        "description": "This is a digital reproduction of an image held in the Library of Congress. Solomon's Pools & ancient aqueducts. Peasant watering his garden from the open Wadi Biyar aqueduct.\nThis image exists as part of the Solomon's Pools collection in the Planet Bethlehem Archive.", 
        "doi": "", 
        "embargo_date": null, 
        "embargo_reason": "", 
        "embargo_type": null, 
        "figshare_url": "https://figshare.com/articles/_/6455465", 
        "files": [
            {
                "computed_md5": "8f33bc2f00886cd401f7cfc291a57346", 
                "download_url": "https://ndownloader.figshare.com/files/11876924", 
                "id": 11876924, 
                "is_link_only": false, 
                "name": "pb_lc_sol_c19340000-0026aa.tiff", 
                "preview_state": "preview_available", 
                "size": 10239662, 
                "status": "available", 
                "supplied_md5": "8f33bc2f00886cd401f7cfc291a57346", 
                "upload_token": "0e15654e-a609-422f-9400-aa7d691068b8", 
                "upload_url": "", 
                "viewer_type": "image"
            }
        ], 
        "funding": "", 
        "group_id": 11353, 
        "group_resource_id": "", 
        "has_linked_file": false, 
        "id": 6455465, 
        "is_active": true, 
        "is_confidential": false, 
        "is_embargoed": false, 
        "is_metadata_record": false, 
        "is_public": false, 
        "license": {
            "name": "CC BY 4.0", 
            "url": "https://creativecommons.org/licenses/by/4.0/", 
            "value": 1
        }, 
        "metadata_reason": "", 
        "modified_date": "2018-06-07T11:39:14Z", 
        "published_date": null, 
        "references": [], 
        "resource_doi": null, 
        "resource_title": null, 
        "size": 10239662, 
        "status": "draft", 
        "tags": [
            "Solomon's Pools"
        ], 
        "thumb": "https://ndownloader.figshare.com/files/11876924/preview/11876924/thumb.png", 
        "title": "Watering a garden from the open Wadi Biyar aqueduct, Solomon's Pools, c.1934-1939", 
        "url": "https://api.figshare.com/v2/account/articles/6455465", 
        "url_private_api": "https://api.figshare.com/v2/account/articles/6455465", 
        "url_private_html": "https://figshare.com/account/articles/6455465", 
        "url_public_api": "https://api.figshare.com/v2/articles/6455465", 
        "url_public_html": "https://figshare.com/articles/_/6455465", 
        "version": 0
    }


