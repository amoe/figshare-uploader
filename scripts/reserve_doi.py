import sys
import requests

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

article_id = create_demo_article(token)


reserve_response = requests.post(
    get_api_url("account/articles/{}/reserve_doi".format(article_id)),
    headers=headers
)
print(reserve_response.json())

