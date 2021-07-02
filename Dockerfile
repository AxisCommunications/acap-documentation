ARG JEKYLL_VERSION=3.8

FROM jekyll/jekyll:${JEKYLL_VERSION}
ENV JEKYLL_UID=1000
ENV JEKYLL_GID=1000
ENV JEKYLL_DEBUG=""
ENV VERBOSE=""
ENV FORCE_POLLING=""

#RUN apt-get update && apt-get install -y --no-install-recommends \

# Set workdir to where all install should take place
COPY ./ /srv/jekyll/
RUN chown -R jekyll /srv/jekyll/
WORKDIR /srv/jekyll

# Build HTML pages from markdown files
RUN jekyll build

# Expose a localhost port
EXPOSE 4000

# What to run when running a container
#ENTRYPOINT ["jekyll", "serve", "--host=0.0.0.0"]


