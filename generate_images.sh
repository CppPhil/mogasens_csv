#!/bin/bash

catch_errors() {
  printf "\ngenerate_images.sh failed!\n" >&2
  exit 1
}

trap catch_errors ERR;

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly PREV_DIR=$(pwd)

readonly GOTO_RUBY="$DIR/external/goto-ruby/goto-ruby.sh"

cd "$DIR"

"$GOTO_RUBY" "$DIR/ruby/generate_images.rb" "$@"

cd "$PREV_DIR"
exit 0

