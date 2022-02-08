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
    $SCRIPT -v ver [-u user] [--help]

General options:
    -v,--version ver      The new ACAP SDK version, e.g. 4.0
    -u,--user user        Use a different user to clone Gerrit repos
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
apiuser=$USER
apiver=
[ $# -ge 1 ] || {  usage && exit 0 ; }
while [ "$#" -gt 0 ]; do
  case $1 in
    -v|v|-ver|--version|-version) apiver=$2 ; shift ;;
    -u|u|-user|--user|-user) apiuser=$2 ; shift ;;
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
prevver=$(find . -maxdepth 1 -name "4.*" | grep -o 4.*)
apiver_minor="${apiver#*.}"
prevver_minor="${prevver#*.}"

# Print variables
printf "Previous verison: $prevver\n"
printf "New version:      $apiver\n"
printf "Previous minor:   $prevver_minor\n"
printf "New minor:        $apiver_minor\n"
printf "APIs to update:   $apis\n"

# Control version format
if [ "${apiver%%.*}" != 4 ]; then
  error "Version $apiver needs to have major equal to '4'"
elif [ "$apiver" = "$prevver" ]; then
  error "Version $apiver already exists"
fi

# Control that new version minor is larger than current version
if [ $apiver_minor -lt $prevver_minor ]; then
  error "Version minor of $apiver should be greater than $prevver minor"
fi

# Check API dirs
nativepage=native-api
nativepage_md=$nativepage.md
nativepage_html=api/$nativepage.html
cvpage=cv-api
cvpage_md=$nativepage.md
gitdir=api-doc
gitdirver=$gitdir/$apiver
targetdirver=$apiver
apidir=$targetdirver/api
maindir=$targetdirver/main/html
sdkdir=$targetdirver/sdk/html

# Fetch new API version
[ -d $gitdir ] || {
	# Clone to copy out the desired version and then remove git repo
  git clone ssh://$apiuser@gittools.se.axis.com:29418/teams/rapid/api-doc.git

  [ -d $gitdirver ] || {
    rm $gitdir -rf
    error "The specified version $apiver has not been generated in $gitdir repo"
  }
  mkdir -p $apidir

  for api in $apis
  do
    cp -r $gitdirver/generated/$api $apidir/
  done
  rm -rf $gitdir

  # Create help links
	mkdir -p $maindir $sdkdir
	add_api_redirect_pages $maindir/index.html $sdkdir/index.html $maindir/acap3_api.html
}

# Update native and cv pages to point to the new version
sed -i "s:$prevver:$apiver:g" $nativepage_md
sed -i "s:$prevver:$apiver:g" $cvpage_md

# Remove previous API version
rm -rf $prevver

# Replace ACAP3 button
cd $targetdirver
replace_acap3_button
cd $startdir

printf "\n#Finished API replacement\n"
