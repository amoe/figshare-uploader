# figshare-uploader

_figshare-uploader_ is a bulk upload tool for the research archiving & storage
provider, Figshare.

**This is an unofficial tool and is not developed by Figshare-the-company.**

It will accept spreadsheets in `.xlsx` format as input, upload the files listed
therein, with their associated metadata.

It is a GUI program that works on Windows, Mac, and Linux.  It supports uploading
files of unlimited size.

A personal token is required to access your Figshare account.  Please read the
[instructions](doc/creating_personal_token.md) for getting one.

## Guide

The program works simply.  You prepare your upload metadata in Excel format,
following a certain schema.  The settings allow flexible mapping of Excel
fields.

## Example

You need three files:

* [The XLSX file](resources/basic_schema_for_non_institutional_account_upload.xlsx?raw=true)
* [The sample image to attach](resources/eye.jpg?raw=true)
* [The JSON field mapping file](resources/basic_schema_for_non_institutional_account.json?raw=true)

Start the program, press the 'Pick' button to pick the file.  Enter your token.
Then go to the Settings dialogue in the menu (named Preferences on Mac systems).
You'll see the field mapping menu.  Choose "Load".  Then load in the JSON file.
Press OK.

Now press "Start upload process".  The tool will create an article in your
account named `Test article`, with `eye.jpg` attached to it.

You can copy the sheet and modify it for your own purposes.  All rows below the
header in the spreadsheet will be treated as items to upload.  (Other sheets in
the workbook will be ignored at present.  Only the first one will be handled.)

## Install

Currently there's a .dmg file for Mac, a portable zip for Windows, and Linux
users have to build it yourselves.  Linux is the primary testing and development
platform.

## Limitations

Currently the tool does not operate as a 'synchronization': that is, if you
already have the articles present and uploaded, it will attempt to upload them
again, potentially creating duplicates.

It does not have support for pause and resuming, of the kind that the API would
allow, and dealing with intermittent connections.  That kind of support would
be useful when dealing with upload of very large files.

It only supports `.xlsx` format sheets as input.

## Support

This work was supported by the [Sussex Humanities Lab](http://www.sussex.ac.uk/shl).

## License

Apache 2.0, see the `LICENSE` file.
