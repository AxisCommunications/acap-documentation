#!/bin/bash
#
# Helper script to clone, copy and add files to make API documentation to work

#-------------------------------------------------------------------------------
# Variables
#-------------------------------------------------------------------------------

# Local directories
startdir=$PWD
src=$startdir

# API mainpage
api_html=apidocs.html

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
    <meta http-equiv='refresh' content='0; url=\"../../../../${api_html}\"' />
  </head>
  <body>
    <p>Please follow <a href='../../../../$api_html'>this link</a>.</p>
  </body>
</html>
" > $3
}

#-------------------------------------------------------------------------------
# Main
#-------------------------------------------------------------------------------

# Move to source directory
cd $src
ls -la

# Check API dirs
apidir=api-doc
apidirver=$apidir/3.3
maindir=$apidirver/main/html
sdkdir=$apidirver/sdk/html

cd $src
[ -d $apidir ] || {
  mkdir $apidir
  cd $apidir

	# Clone to copy out the desired version and then remove git repo
  git clone ssh://$USER@gittools.se.axis.com:29418/teams/rapid/api-doc.git
  cp -r $apidirver .
  rm -rf $apidir

	# Rename api directory for links
	cd $src
	mv $apidirver/generated $apidirver/api

	mkdir -p $maindir $sdkdir
	add_api_redirect_pages $maindir/index.html $sdkdir/index.html $maindir/acap3_api.html
}

cd $startdir
