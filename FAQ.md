## How do I submit descriptions with multiple paragraphs?

The contents of the description field is stored in Figshare as HTML (their
decision, not mine).  That means that when the field gets rendered in the web
UI, spaces will be collapsed.  So you'll need to convert your description fields
into appropriate HTML.  Possibly just replace all newline characters with
`<br/>`.  When you write descriptions directly into Figshare's web UI, all
paragraphs are automatically surrounded by `<div>` tags and separated by `<br>`.
