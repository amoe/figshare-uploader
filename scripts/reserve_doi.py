import sys
import requests
import pprint

token = sys.argv[1]
API_PREFIX = "https://api.figshare.com/v2/"
headers = {'Authorization': 'token ' + token}

def get_api_url(path):
    return API_PREFIX + path

def create_demo_article(token):
    data = {
        'title': 'A test article',
        'group_id': 20852
    }
    result = requests.post(
        get_api_url('account/articles'), json=data, headers=headers
    )
    location = result.headers['location']
    article_data = requests.get(location, headers=headers).json()
    return article_data['id']

def doi_to_url(doi):
    return "https://doi.org/{}".format(doi)



article_id = create_demo_article(token)
reserve_response = requests.post(
    get_api_url("account/articles/{}/reserve_doi".format(article_id)),
    headers=headers
)
reserve_data = reserve_response.json()
doi = reserve_data['doi']

# it won't become active until it's actually reserved
print(doi_to_url(doi))


