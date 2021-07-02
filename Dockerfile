ARG JEKYLL_VERSION=3.8
FROM jekyll/jekyll:${JEKYLL_VERSION}

# Set Jekyll configuration variables
ENV JEKYLL_UID=1000
ENV JEKYLL_GID=1000
ENV JEKYLL_DEBUG=""
ENV VERBOSE=""
ENV FORCE_POLLING=""

# Set workdir to where all install should take place
COPY ./ /srv/jekyll/
RUN chown -R jekyll /srv/jekyll/
WORKDIR /srv/jekyll

# Build HTML pages from markdown files
RUN jekyll build

# Expose a localhost port
EXPOSE 4000
