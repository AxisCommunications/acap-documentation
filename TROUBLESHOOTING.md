# TROUBLESHOOTING

## Serving local web page

### Cannot serve 0.0.0.0:4000

The web page is by default served on `http://0.0.0.0:4000/acap-documentation`,
but if you cannot open this page, try `localhost:4000/acap-documentation`.

### Avoid accidental ownership change of sensitive user files

GitHub Pages is based on Jekyll to build and serve web pages. The
**acap-documentation** repository builds Docker container images based on the
official [Jekyll Docker image](https://hub.docker.com/r/jekyll) to be able to
test changes without having to install dependencies like Ruby and Jekyll.

To serve this page from the acap-documentation directory, it's enough to run

```sh
docker run --rm -p 4000:4000 -v "$PWD":/srv/jekyll -it doc:1 jekyll serve
```

but in the [CONTRIBUTING](./CONTRIBUTING.md#build-and-serve-documentation) page
the instruction is much longer, why?

The Jekyll image has permission to change the directory and sub-directories that
gets mounted with `-v "$PWD":/srv/jekyll`. On Unix systems it's common to
search the command history to run a recurring command and here's the nasty
thing; running the above command from home directory `~/` instead of
`acap-documentation` directory will change ownership of certain directories,
one of them being `~/.cache`. A program affected by this is **Firefox**. The
change is not noted until a restart and the error is complaining on that the
profile cannot be loaded, making this a tricky problem to troubleshoot.

A quick solution is to add checks that this image can only be run from the
correct directory as described in the comments of the below code block.

```sh
# Run the Docker image to serve the web page
# - Check that current directory is a git repository
# - Check that the current directory has the expected name "acap-documentation"
#   or "acap-documentation-staging"
# - Run Docker image and mount the top git directory
# - If error in any of the previous steps, print a help message
ACAPDOC="$(git rev-parse --show-toplevel)" && \
{ [ "${ACAPDOC##*/}" = "acap-documentation" ] || [ "${ACAPDOC##*/}" = "acap-documentation-staging" ] ; } && \
docker run --rm -p 4000:4000 -v "$ACAPDOC":/srv/jekyll -it doc:1 jekyll serve || \
printf "\nERROR: The current directory is not acap-documentation*\n"
```
