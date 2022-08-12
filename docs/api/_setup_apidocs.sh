#!/bin/bash
#
# Helper script to clone, copy and add files to make API documentation to work

#-------------------------------------------------------------------------------
# Variables
#-------------------------------------------------------------------------------

# Local directories
startdir=$PWD

#-------------------------------------------------------------------------------
# Log functions
#-------------------------------------------------------------------------------

usage() {
  echo "
--------------------------------------------------------------------------------
API utility script
--------------------------------------------------------------------------------

Update API documentation

Usage:
    $SCRIPT -v ver [--help]

General options:
    -v,--version ver      The new ACAP SDK version, e.g. 4.0
    -h, --help            Show this help

Example:
    $SCRIPT -v 4.0

--------------------------------------------------------------------------------
"
}

error() {
  printf "\n\nERROR: $*\n"
  cd $startdir
  exit 1
}

#-------------------------------------------------------------------------------
# Parse options
#-------------------------------------------------------------------------------

# Parse the options
apiver=
[ $# -ge 1 ] || {  usage && exit 0 ; }
while [ "$#" -gt 0 ]; do
  case $1 in
    -v|v|-ver|--version|-version) apiver=$2 ; shift ;;
    h|-h|help|--help) usage && exit 0 ;;
    *) usage && exit 0 ;;
  esac
  shift
done

#-------------------------------------------------------------------------------
# Functions
#-------------------------------------------------------------------------------

add_api_redirect_pages() {
	# $1 Replace "ACAP3 main pages"
	# $2 Replace "SDK main page", same as above
	# $3 Replace "API main page"

for apifile in $1 $2
do
echo "
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv='refresh' content='0; url=\"../../../../../index.html\"' />
  </head>
  <body>
    <p>Please follow <a href='../../../../../index.html'>this link</a>.</p>
  </body>
</html>
" > $apifile
done

echo "
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv='refresh' content='0; url=\"../../../../${nativepage_html}\"' />
  </head>
  <body>
    <p>Please follow <a href='../../../../$nativepage_html'>this link</a>.</p>
  </body>
</html>
" > $3
}

replace_acap3_button() {
  local oldtext="ACAP3 Main Page"
  local newtext="ACAP Main Page"
  local matchfiles=

  matchfiles=$(grep -lr "$oldtext")
  for match in $matchfiles
  do
    sed -i "s:$oldtext:$newtext:g" $match
  done
}

#-------------------------------------------------------------------------------
# Main
#-------------------------------------------------------------------------------

# Release settings
apis="axevent axoverlay larod licensekey vdostream"

# Version strings
apiver_minor="${apiver#*.}"

# Print variables
printf "New version:      $apiver\n"
printf "New minor:        $apiver_minor\n"
printf "APIs to update:   $apis\n"

# Control version format
if [ "${apiver%%.*}" != 4 ]; then
  error "Version $apiver needs to have major equal to '4'"
fi

# Check API dirs
nativepage=native-sdk-api
nativepage_md=$nativepage.md
nativepage_html=api/$nativepage.html
cvpage=computer-vision-sdk-apis
cvpage_md=$nativepage.md
gitdir=api-doc
gitdirver=$gitdir/$apiver
targetdir=src
targetdirprev=src_back
apidir=$targetdir/api
maindir=$targetdir/main/html
sdkdir=$targetdir/sdk/html

# Fetch new API version
[ -d $gitdirver ] || {
  error "The specified version $apiver has not been generated in $gitdir repo"
}

# Rename current source
[ ! -d $targetdir ] || {
  mv $targetdir $targetdirprev
}

# Create new structure and copy content
mkdir -p $apidir
for api in $apis
do
  cp -r $gitdirver/generated/$api $apidir/
done

# Create help links
mkdir -p $maindir $sdkdir
add_api_redirect_pages $maindir/index.html $sdkdir/index.html $maindir/acap3_api.html

# Remove API repo and previous API directory
rm -rf $targetdirprev

# Replace ACAP3 button
cd $targetdir
replace_acap3_button
cd $startdir

printf "\n#Finished API replacement\n"
