#!/usr/bin/env python3

import hashlib
import json
import os
import sys

import requests
from requests.exceptions import HTTPError


BASE_URL = 'https://api.figshare.com/v2/{endpoint}'
CHUNK_SIZE = 1048576
TITLE = 'A 3D cat object model'


class UploadExample(object):
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
        print('Listing current articles:')
        if result:
            for item in result:
                print(u'  {url} - {title}'.format(**item))
        else:
            print('  No articles.')
        print()


    def create_article(self, title):
        data = {
            'title': title  # You may add any other information about the article here as you wish.
        }
        result = self.issue_request('POST', 'account/articles', data=data)
        print('Created article:', result['location'], '\n')

        result = self.raw_issue_request('GET', result['location'])

        return result['id']


    def list_files_of_article(self, article_id):
        result = self.issue_request('GET', 'account/articles/{}/files'.format(article_id))
        print('Listing files for article {}:'.format(article_id))
        if result:
            for item in result:
                print('  {id} - {name}'.format(**item))
        else:
            print('  No files.')

        print()


    def get_file_check_data(self, file_name):
        with open(file_name, 'rb') as fin:
            md5 = hashlib.md5()
            size = 0
            data = fin.read(CHUNK_SIZE)
            while data:
                size += len(data)
                md5.update(data)
                data = fin.read(CHUNK_SIZE)
            return md5.hexdigest(), size


    def initiate_new_upload(self, article_id, file_name):
        endpoint = 'account/articles/{}/files'
        endpoint = endpoint.format(article_id)

        md5, size = self.get_file_check_data(file_name)
        data = {'name': os.path.basename(file_name),
                'md5': md5,
                'size': size}

        result = self.issue_request('POST', endpoint, data=data)
        print('Initiated file upload:', result['location'], '\n')

        result = self.raw_issue_request('GET', result['location'])

        return result


    def complete_upload(self, article_id, file_id):
        self.issue_request('POST', 'account/articles/{}/files/{}'.format(article_id, file_id))


    def upload_parts(self, file_info):
        url = '{upload_url}'.format(**file_info)
        result = self.raw_issue_request('GET', url)

        print('Uploading parts:')
        with open(self.file_path, 'rb') as fin:
            for part in result['parts']:
                self.upload_part(file_info, fin, part)
        print()


    def upload_part(self, file_info, stream, part):
        udata = file_info.copy()
        udata.update(part)
        url = '{upload_url}/{partNo}'.format(**udata)

        stream.seek(part['startOffset'])
        data = stream.read(part['endOffset'] - part['startOffset'] + 1)

        self.raw_issue_request('PUT', url, data=data, binary=True)
        print('  Uploaded part {partNo} from {startOffset} to {endOffset}'.format(**part))


    def main(self, args):
        self.token = args[0]
        self.file_path = args[1]

        # We first create the article
        self.list_articles()
        article_id = self.create_article(TITLE)
        self.list_articles()
        self.list_files_of_article(article_id)

        # Then we upload the file.
        file_info = self.initiate_new_upload(article_id, self.file_path)
        # Until here we used the figshare API; following lines use the figshare upload service API.
        self.upload_parts(file_info)
        # We return to the figshare API to complete the file upload process.
        self.complete_upload(article_id, file_info['id'])
        self.list_files_of_article(article_id)


if __name__ == '__main__':
    obj = UploadExample()
    obj.main(sys.argv[1:])
