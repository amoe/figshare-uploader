#!/usr/bin/env python3

"""
Dump a human-readable output of all available Figshare categories and their
respective IDs.
"""

import requests

response = requests.get('https://api.figshare.com/v2/categories')
data = response.json()

for datum in data:
    if datum['is_selectable']:
        print(datum['id'], datum['title'])
