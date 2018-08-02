#!/usr/bin/env python3

import hashlib
import json
import os
import sys
import json

import requests
from requests.exceptions import HTTPError

BASE_URL = 'https://api.figshare.com/v2/{endpoint}'

class ListAccountGroupsScript(object):
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

    def main(self, args):
        self.token = args[0]

        result = self.issue_request('GET', 'account/institution/groups')
        json.dump(result, sys.stdout, indent=4)
        print()


if __name__ == '__main__':
    obj = ListAccountGroupsScript()
    obj.main(sys.argv[1:])
