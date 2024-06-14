#!/bin/bash

#-------------------------------------------------------------------------------
# Functions
#-------------------------------------------------------------------------------

print_section() {
  local sep40="----------------------------------------"
  printf '\n\n%s\n%s\n%s\n' "$sep40$sep40" " $*" "$sep40$sep40"
}

check_device_ip_paths() {
  local ret=0
  local __url_grep_list=
  base_url="192.168.0.90"
  exclude_dir_list="\
    --exclude-dir=.github \
    --exclude-dir=src \
    --exclude-dir=_site \
    --exclude-dir=capture \
  "
  allowed_patterns="\
    \`$base_url\` \
    $base_url<space> \
    $base_url/index.html[a-z] \
    $base_url/axis-cgi \
    @$base_url \
  "

  print_section "Check that device URLs follow allowed pattern"

  # shellcheck disable=SC2086
  __url_grep_list=$(grep -nir "$base_url" $exclude_dir_list |
    grep -vE "$base_url(\`|$| |:|/axis-cgi|/index.html#[a-z]|/local)" |
    grep -vE "@$base_url" || :)

  if [ "$__url_grep_list" ]; then
    printf '\n%s\n%s\n\n' \
      "## Error - The following device URLs are not matching allowed patterns" \
      "$__url_grep_list"
    printf "## Allowed patterns (Including URLs prefixed http://):\n"
    for pattern in $allowed_patterns; do
      printf '%s\n' "* $pattern"
    done
    printf "\nA typical error is to copy the redirected URL that include e.g. product specific string 'camera'\n"
    ret=1
  else
    printf "* All device URLs follow pattern\n"
  fi

  return $ret
}

#-------------------------------------------------------------------------------
# Main
#-------------------------------------------------------------------------------

exit_value=0
found_error=no

if ! check_device_ip_paths; then found_error=yes; fi

[ "$found_error" = no ] || exit_value=1

exit $exit_value
