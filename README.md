# ACAP 4 SDK Documentation
The ACAP 4 SDK Documentation is built with
[Github pages](https://pages.github.com/) and the Jekyll theme
[Just the Docs](https://pmarsceill.github.io/just-the-docs/).

## Contribute
Have you found an error, want to ask a question or give a suggestion? Then
continue to the [Contributing](./CONTRIBUTING.md) page for more information.

## Beta testers
For partners signed up as beta testers, the documentation is given as a Docker
container.

```bash
docker login
docker run --rm -p 4000:4000 -it axisecp/acap-documentation-staging:latest-master jekyll serve
```
Then open a web browser at `http://0.0.0.0:4000/acap-documentation` or if this
is not working, try `localhost:4000/acap-documentation`.

# Copyright
&copy;2021 Axis Communications AB. All rights reserved. AXIS COMMUNICATIONS, AXIS, ARTPEC and VAPIX are registered trademarks of Axis AB in various jurisdictions, and you are not granted any license to use them. All other trademarks are the property of their respective owners.
