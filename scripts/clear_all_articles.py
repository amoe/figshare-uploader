#!/usr/bin/env python3

import click
import hashlib
import json
import os
import sys
import pprint

import requests
from requests.exceptions import HTTPError

BASE_URL = 'https://api.figshare.com/v2/{endpoint}'

class ClearAllArticlesScript(object):
    token = None
    file_path = None

    def raw_issue_request(self, method, url, data=None, binary=False):
        headers = {'Authorization': 'token ' + self.token}
        if data is not None and not binary:
            data = json.dumps(data)
        response = requests.request(method, url, headers=headers, data=data)
        try:
            response.raise_for_status()
            try:
                data = response.json()
            except ValueError:
                data = response.content
        except HTTPError as error:
            print('Caught an HTTPError: {}'.format(error))
            print('Body:\n', response.content)
            raise

        return data

    def issue_request(self, method, endpoint, *args, **kwargs):
        return self.raw_issue_request(method, BASE_URL.format(endpoint=endpoint), *args, **kwargs)

    def list_articles(self):
        result = self.issue_request('GET', 'account/articles')
        return result

    def upload_part(self, file_info, stream, part):
        udata = file_info.copy()
        udata.update(part)
        url = '{upload_url}/{partNo}'.format(**udata)

        stream.seek(part['startOffset'])
        data = stream.read(part['endOffset'] - part['startOffset'] + 1)

        self.raw_issue_request('PUT', url, data=data, binary=True)
        print('  Uploaded part {partNo} from {startOffset} to {endOffset}'.format(**part))

    def delete_article(self, article):
        result = self.issue_request('DELETE', 'account/articles/{}'.format(article['id']))
        print(result)

    def main(self, args):
        self.token = args[0]
        
        # don't bother with pagination, just loop until there aren't any more
        # articles left

        REQUIRE_CONFIRM = True

        while True:
            all_articles = [a for a in self.list_articles()
                            if a['published_date'] is None]
            if not all_articles: 
                print("No more articles to delete.")
                break

            for article in all_articles:
                print("Deleting article ", article['id'])
                if REQUIRE_CONFIRM:
                    pprint.pprint(article)

                    if click.confirm("Really delete?", default=True):
                        self.delete_article(article)


if __name__ == '__main__':
    obj = ClearAllArticlesScript()
    obj.main(sys.argv[1:])
