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

# Install latest changes for theme, from Gemfile
RUN [ ! -f "Gemfile.lock" ] || { \
    cat Gemfile.lock && \
    echo "Remove old Gemfile.lock" && \
    rm -f Gemfile.lock ; }
RUN gem install bundler
# Run bundle install separately, seems to hang sometimes when using one RUN
RUN bundle install && \
    bundle info --path just-the-docs

# Build HTML pages from markdown files
RUN pwd && ls -la && jekyll --version && \
    jekyll build --trace && \
    pwd && ls -la

# Expose a port
EXPOSE 4000
