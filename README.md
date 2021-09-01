# ACAP 4 SDK Documentation

General information for ACAP 4 SDK Documentation as Github pages.

## View documentation offline

To view the documentation offline, which is necessary e.g. for versions that have not been released yet, you can run the docs container locally.

In this example, check out the latest version:

``` 
docker pull axisecp/acap-documentation-staging:latest-master
docker run --rm -p 4000:4000 -it axisecp/acap-documentation-staging:latest-master jekyll serve
```

Then open a web browser at http://localhost:4000.
