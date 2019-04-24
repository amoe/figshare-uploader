# Configuring field mapping

This is a guide for users.

The program has definitions for the built in Figshare fields already written.

Each rule for mapping a given field is called a _field encoder_.  For instance,
the `title` encoder is a rule that maps an Excel cell to the title of a Figshare
article.  

In some cases, the mapping is more complex.  For instance, in your Figshare
tracker sheets, you might want to asssociate your items with a specific project.
Projects in Figshare have to be identified by their group ID -- which is a
number -- but you want to indicate them by their name in your tracker sheet.

Each field encoder specifies a _converter_ -- this is one of a fixed set of
methods for performing the mapping.  In the case of the `title` encoder, the
converter is named `String` -- it simply copies the string value as written.

However, for more complicated cases there are converters like `LookupValue`,
which will allow looking up group IDs based on project names, as in the project
example above.

## Custom fields

You can use the same system as configuring regular field encoders.  Just select
"Custom" instead of "Standard".  All the same converters are available, but 
probably only simple `String` will be useful.

