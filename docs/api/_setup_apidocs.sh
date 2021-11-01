#!/bin/bash
#
# Helper script to clone, copy and add files to make API documentation to work

#-------------------------------------------------------------------------------
# Variables
#-------------------------------------------------------------------------------

# Local directories
startdir=$PWD


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
prevver=3.4
apiver=4.0
apis="axevent axoverlay larod licensekey vdostream"

# Check API dirs
nativepage=native-api
nativepage_md=$nativepage.md
nativepage_html=api/$nativepage.html
gitdir=api-doc
gitdirver=$gitdir/$apiver
targetdirver=$apiver
apidir=$targetdirver/api
maindir=$targetdirver/main/html
sdkdir=$targetdirver/sdk/html

# Fetch new API version
[ -d $gitdir ] || {
  mkdir -p $apidir

	# Clone to copy out the desired version and then remove git repo
  git clone ssh://$USER@gittools.se.axis.com:29418/teams/rapid/api-doc.git
  for api in $apis
  do
    cp -r $gitdirver/generated/$api $apidir/
  done
  rm -rf $gitdir

  # Create help links
	mkdir -p $maindir $sdkdir
	add_api_redirect_pages $maindir/index.html $sdkdir/index.html $maindir/acap3_api.html
}

# Update native page to point to the new version
sed -i "s:$prevver:$apiver:g" $nativepage_md

# Remove previous API version
rm -rf $prevver

# Replace ACAP3 button
cd $targetdirver
replace_acap3_button
cd $startdir

printf "\n#Finished API replacement\n"
