#!/bin/bash

ret=0
base_url="192.168.0.90"
exclude_dir_list="\
  --exclude-dir=.github \
  --exclude-dir=src \
  --exclude-dir=_site \
  --exclude-dir=capture \
  --exclude=test.sh \
"
allowed_patterns="\
  \`$base_url\` \
  $base_url<space> \
  $base_url/index.html \
  $base_url/axis-cgi \
  @$base_url \
"

# Set +e to not having to handle the grep exit status
__url_grep_list=$(grep -nir "$base_url" $exclude_dir_list | \
  grep -vE "$base_url(\`| |/axis-cgi|/index.html#)" | \
  grep -vE "@$base_url" || :)
[ -z "$__url_grep_list" ] || {
    printf '\n%s\n%s\n\n' \
      "## Error - The following device URLs are not matching allowed patterns" \
      "$__url_grep_list"
    printf "## Allowed patterns (Including URLs prefixed http://):\n"
    for pattern in $allowed_patterns
    do
      printf '%s\n' "* $pattern"
    done
    printf "\nA typical error is to copy the redirected URL that include e.g. product specific string 'camera'\n"
    ret=1
}
exit $ret
