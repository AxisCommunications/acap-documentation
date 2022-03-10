# Contribute to the ACAP SDK documentation

## Types of contributions
Contributions to the ACAP documentation can be made by:
* **Issue tracker** - Suggest a general change or ask a question.
* **Pull request** - Report typos or errors, or propose a code change.

## A note on auto-generated content
Some files in the documentation are automatically generated and should not be
changed in the acap-documentation but in the upstream source:

* API technical documentation pages: **docs/api/4.X/**
* Manifest schema field descriptions: **docs/develop/schema-field-descriptions-{VERSION}.md**

To suggest changes to these files/directories, open a new issue.

## Develop and test documentation changes locally
If you like to propose a code change and see how it looks, you may serve the
documentation web page locally.

### Pre-requisites
To test the documentation locally you need:
- [Docker](https://docs.docker.com/get-docker/)
- [Git](https://git-scm.com/downloads)

To be able to make a pull request you also need:
- [Github account](https://github.com)


### Build and serve documentation
In a terminal,
```bash
# Clone the repository with HTTPS or SSH
git clone https://github.com/AxisCommunications/acap-documentation.git
git clone git@github.com:AxisCommunications/acap-documentation.git

# Set permission for Jekyll user
chmod 777 acap-documentation

# Build a local Docker image
cd acap-documentation
docker build -t doc:1 .

# Run the Docker image to serve the web page
docker run --rm -p 4000:4000 -v $PWD:/srv/jekyll -it doc:1 jekyll serve
```
The web page will be served on `http://0.0.0.0:4000/acap-documentation`. If you
can't open this page, try `localhost:4000/acap-documentation`.

Now when you make changes to a Markdown or HTML page and save it - reload the
web page and the changes will be shown.

> In the terminal where you run the `docker run` command, make sure to check
> the output messages and act on any warnings or errors if you want to make a
> pull request.

## Open a pull request
To allow developers without write access to contribute, Github recommends
using [forks][aboutforks].

### Work with the change locally
1. [Fork the repository][forkrepo] to be able to make changes without affecting
upstream repository during work.

2. Create a branch for your changes

3. [Serve web page locally](develop-and-test-documentation-changes-locally) to
see how your changes look like when converted to a web page.

### Create pull request
When your change is ready, have a look at [How to make a good pull
request](#how-to-make-a-good-pull-request) to fasten up the review process.

Now, [create a pull request from your fork][pr-from-fork].


## How to make a good pull request
- Follow the [conventional commits](https://www.conventionalcommits.org)
  message style in the commit messages.
- Make sure that the there are no errors in the terminal from which you serve
  the web page locally, see more info in section for
  [serving the web page locally](develop-and-test-documentation-changes-locally).
- Check the [Guidelines for changes](guidelines-for-changes).


## Guidelines for changes
The documentation is generated with [Jekyll](https://jekyllrb.com) and a Jekyll
theme called [Just the Docs](https://pmarsceill.github.io/just-the-docs/). This
allows documentation to be written in Markdown which will then be built in to a
page with the layout of the site.

Generally changes can be divided in *content* and *layout*. To make a
contribution to the content, only knowledge about Markdown is required.

### Write in Markdown
You can find documentation of the Markdown syntax online:
* [markdownguide.org](https://www.markdownguide.org/)
* [Official documentation](https://daringfireball.net/projects/markdown/)

### Change of content
Most, if not all the content pages are written in Markdown, files with suffix
`.md`. You can find the majority of the pages for documentation content under
directory `docs/`. Even though the files are Markdown, they contain
[Front Matter](https://jekyllrb.com/docs/front-matter)
notation in the top of each file for Jekyll and may also contain HTML code. We
recommend you to use Markdown whenever possible.

Do also see the following sections for Jekyll theme and other general
considerations.

#### Jekyll theme "Just the Docs"
This Jekyll theme [Just the Docs](https://pmarsceill.github.io/just-the-docs/)
has some handy formatting for things like [spacing and
alignment](https://pmarsceill.github.io/just-the-docs/docs/utilities/layout/).

#### General format
To keep a more consistent and easy to read format:
* Use a maximum text width of 80 characters. Two consecutive rows of text will
  be interpreted as a single line by Markdown. An exception to this is special
  objects like tables that don't allow row breaks

#### Notes and important squares
To add a note, use the Markdown symbol for blockquotes `> ` followed by a space
on each line that the note consists of, e.g.:
```markdown
Here is some text before

> ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP ACAP
> NATIVE NATIVE NATIVE NATIVE NATIVE NATIVE NATIVE NATIVE NATIVE NATIVE NATIVE
> SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK SDK

Here is some text after
```

To mark that something is extra important, start the blockquote with an
'Important' marked in bold, i.e.:
```markdown
> **Important** Pay extra attention!
```

#### Tables
Tables are not very flexible when it comes to line breaks. To get a line break
in a cell, use the HTML formatting for a line break `<br>` where needed.

Make also sure to keep an empty line before and after the table code or else it
won't be generated as a table.

#### Fenced code blocks and syntax highlighting
Fenced code blocks may be used to display a command-line or a code snippet. To
get syntax highlighting it's required to append the three first backticks with
the language. See [Syntax
Highlighting](https://www.markdownguide.org/extended-syntax/#syntax-highlighting)
for more info. A simple example for bash,
~~~~
```bash
git log
```
~~~~

To find the language name, a good start is to search for the suffix or the
language in [pygments.org](https://pygments.org/docs/lexers/) and use the
*Short names*.

**Some common languages short names:**
* bash, sh
* make
* dockerfile
* json
* c
* html

### Change of layout
Layout and theme configuration changes are usually managed by the repository
owners. If frequent configuration updates are expected during development, the
utility script for splitting build steps will help to make the iteration loop
faster, run `./build-multistage --help` for more instructions.


[aboutforks]: https://docs.github.com/en/github/collaborating-with-pull-requests/working-with-forks/about-forks
[forkrepo]: https://docs.github.com/en/github/getting-started-with-github/fork-a-repo#fork-an-example-repository
[pr-from-fork]: https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork