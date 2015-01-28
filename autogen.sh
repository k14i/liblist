#!/bin/bash

function _exec() {
  i=`expr $i + 1`
  echo "$i: Starting $1 $2"
  $1 $2
  if test $? -ne 0; then
    echo "$1 $2 Failed."
    exit $i
  fi
}

i=0
deps=''

if test x$deps != x''; then
  _exec "sudo yum install -y" "$deps"
fi

_exec "touch" "./NEWS"
_exec "touch" "./README"
_exec "touch" "./AUTHORS"
_exec "touch" "./ChangeLog"
_exec "aclocal" ""
_exec "libtoolize" "-i"
_exec "autoreconf" "-i"
_exec "automake" "-a"
_exec "autoconf" ""
_exec "automake" "--add-missing"
_exec "autoreconf" "-vi"

echo
echo "autogen.sh Successfully finished."
exit 0
