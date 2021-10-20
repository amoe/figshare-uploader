# Manual

## Building

For detailed docs on how to build the program, read
[doc/BUILD.md](doc/BUILD.md).

## Supported item types

The supported values for the "Item Type" field -- known as `defined_type` in API
terms -- are Figure, Dataset, Media, Poster, Paper, and Fileset.  Other values
are not yet supported.


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
