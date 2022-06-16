# Contribute to the ACAP SDK documentation

## Types of contributions

Contributions to the ACAP documentation can be made by:

- **Issue tracker** - Suggest a general change or ask a question.
- **Pull request** - Report typos or errors, or propose a code change.

## A note on auto-generated content

Some files in the documentation are automatically generated and should not be
changed in the acap-documentation but in the upstream source:

- API technical documentation pages: **docs/api/4.X/**
- Manifest schema field descriptions: **docs/develop/schema-field-descriptions-{VERSION}.md**

To suggest changes to these files/directories, open a new issue.

## Develop and test documentation changes locally

If you like to propose a code change and see how it looks, you may serve the
documentation web page locally.

### Pre-requisites

To test the documentation locally you need:

- [Docker](https://docs.docker.com/get-docker/)
- [Git](https://git-scm.com/downloads)

To be able to make a pull request you also need:

- [GitHub account](https://github.com)

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
# Why this long command? See a longer exaplanation in the troubleshooting link
ACAPDOC="$(git rev-parse --show-toplevel)" && \
{ [ "${ACAPDOC##*/}" = "acap-documentation" ] || [ "${ACAPDOC##*/}" = "acap-documentation-staging" ] ; } && \
docker run --rm -p 4000:4000 -v "$ACAPDOC":/srv/jekyll -it doc:1 jekyll serve || \
printf "\nERROR: The current directory is not acap-documentation*\n"
```

The web page will be served on `http://0.0.0.0:4000/acap-documentation`.

Now when you make changes to a Markdown or HTML page and save it - reload the
web page and the changes will be shown.

> In the terminal where you run the `docker run` command, make sure to check
> the output messages and act on any warnings or errors if you want to make a
> pull request.

For issues serving the local web page, see [TROUBLESHOOTING](./TROUBLESHOOTING.md).

### Lint of code base

A set of different linters test the code base and these must pass in order to get a pull request approved.

#### Linters in GitHub Action

When you create a pull request, a set of linters will run syntax and format checks on different file types in GitHub Actions by making use of a tool called [super-linter](https://github.com/github/super-linter). If any of the linters gives an error, this will be shown in the action connected to the pull request.

In order to fasten up development, it's possible to run linters as part of your local development environment.

#### Run super-linter locally

Since super-linter is using a Docker image in GitHub Actions, users of other editors may run it locally to lint the code base. For complete instructions and guidance, see super-linter page for [running locally](https://github.com/github/super-linter/blob/main/docs/run-linter-locally.md).

To run a number of linters on the code base from command line:

```sh
docker run --rm  \
  -v $PWD:/tmp/lint \
  -e RUN_LOCAL=true \
  -e VALIDATE_MARKDOWN=true \
  -e FILTER_REGEX_EXCLUDE='docs/develop/schema-field-descriptions-v*' \
  -e LINTER_RULES_PATH=/ \
  -e MARKDOWN_CONFIG_FILE=.markdownlint.yml \
  github/super-linter:slim-v4
```

##### Run super-linter interactively

It might be more convenient to run super-linter interactively. Run container and enter command line:

```sh
docker run --rm \
  -v $PWD:/tmp/lint \
  -w /tmp/lint \
  --entrypoint /bin/bash \
  -it github/super-linter:slim-v4
```

Then from the container terminal, the following commands can lint the code base for different file types:

```sh
# Lint Markdown files
markdownlint -i docs/develop/schema-field-descriptions-v\* .
```

## Open a pull request

To allow developers without write access to contribute, GitHub recommends
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

## Special markers

### Beta APIs

Beta APIs should be marked with a preceding `BETA -` as in `BETA - Test API`
in the;

- overview list, for example `* [BETA - Test API](./beta---test-api)`
- section title, for example `## BETA - Test API`

The API section should start with a link to the Beta API page:

```markdown
**This API is a [Beta version](./beta-api) and developers are encouraged to
test and leave feedback.**
```

If referred to in section text, use *Beta API* with capital letter.

## Guidelines for changes

The documentation is generated with [Jekyll](https://jekyllrb.com) and a Jekyll
theme called [Just the Docs](https://just-the-docs.github.io/just-the-docs/). This
allows documentation to be written in Markdown which will then be built in to a
page with the layout of the site.

Generally changes can be divided in *content* and *layout*. To make a
contribution to the content, only knowledge about Markdown is required.

### Write in Markdown

You can find documentation of the Markdown syntax online:

- [markdownguide.org](https://www.markdownguide.org/)
- [Official documentation](https://daringfireball.net/projects/markdown/)

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

This Jekyll theme [Just the Docs](https://just-the-docs.github.io/just-the-docs/)
has some handy formatting for things like [spacing and
alignment](https://just-the-docs.github.io/just-the-docs/docs/utilities/layout/).

#### General format

To keep a more consistent and easy to read format:

- Use a maximum text width of 80 characters. Two consecutive rows of text will
  be interpreted as a single line by Markdown. An exception to this is special
  objects like tables that don't allow row breaks

#### Notes and important squares

To add a note, use the Markdown symbol for blockquotes `>` followed by a space
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

<!-- markdownlint-disable MD040 MD048 -->
~~~~
```bash
git log
```
~~~~

To find the language name, a good start is to search for the suffix or the
language in [pygments.org](https://pygments.org/docs/lexers/) and use the
*Short names*.

**Some common languages short names:**

- bash, sh
- make
- dockerfile
- json
- c
- html

### Change of layout

Layout and theme configuration changes are usually managed by the repository
owners. If frequent configuration updates are expected during development, the
utility script for splitting build steps will help to make the iteration loop
faster, run `./build-multistage --help` for more instructions.

[aboutforks]: https://docs.github.com/en/github/collaborating-with-pull-requests/working-with-forks/about-forks
[forkrepo]: https://docs.github.com/en/github/getting-started-with-github/fork-a-repo#fork-an-example-repository
[pr-from-fork]: https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork
