# figshare-uploader (aka upgraded-fortnight)

For docs on how to build the thing, read [doc/BUILD.md](doc/BUILD.md).

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

The program works simply.  You prepare your uploads in Excel format, following a
certain schema.  The settings allow flexible mapping of Excel fields.

## Why write this in C++?

There are several reasons:

* It was originally intended to be able to handle very large uploads.  When
  saying large, I am talking terabytes of uncompressed video.  Such a program
  would be difficult to make work with a web-based app.  Authentication would
  also be more difficult to handle if creating a web app.
* The Python Qt interface would be a reasonable option, but in my limited
  experience, it didn't provide a good developer experience.  I had to
  frequently resort to reading the C++ API anyway.
* I dislike Electron, and writing JavaScript is essentially a punishment
  experience for me.

## Example

You need three files:

* [The XLSX file](resources/basic_schema_for_non_institutional_account_upload.xlsx)
* [The sample image to attach](resources/eye.jpg)
* [The JSON field mapping file](resources/basic_schema_for_non_institutional_account.json)

Start the program, press the 'Pick' button to pick the file.  Enter your
token.  Then go to the Settings dialogue in the menu (which may be named 
Preferences on Mac systems).  You'll see the field mapping menu.  Choose "Load".
Then load in the JSON file.  Press OK.

Now press "Start upload process".  The tool will create an article in your
account named `Test article`, with `eye.jpg` attached to it.

You can copy the sheet and modify it for your own purposes.  All non-header rows
in the default sheet will be treated as items to upload.  (Multiple sheets in
a workbook are not supported at this time.)

### Supported item types

The supported values for the "Item Type" field -- known as `defined_type` in API
terms -- are Figure, Dataset, Media, Poster, Paper, and Fileset.  Other values
are not yet supported.

## Install

Currently there's a .dmg file for Mac, a zip for windows (no installer), and
Linux users have to build it yourselves.

## Limitations

Currently the tool does not operate as a 'synchronization': that is, if you
already have the articles present and uploaded, it will attempt to upload them
again.

It does not have support for pause and resuming, of the kind that the API would
allow, and dealing with intermittent connections.  That kind of support would
be useful when dealing with upload of very large files.

It only supports `.xlsx`.

## TODO

* Refactor out the various HTTP lookup classes, a lot of duplication at present.

## Support

This work was supported by the [Sussex Humanities Lab](http://www.sussex.ac.uk/shl).

## License

Apache 2.0, see the `LICENSE` file.
Yow! x7
