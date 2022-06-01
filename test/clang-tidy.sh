#!/bin/sh

set -e

clang_tidy="$(command -v clang-tidy-13 || command -v clang-tidy-12 || command -v clang-tidy)"

"$clang_tidy" \
	--config-file=test/.clang-tidy.yml \
	$(find -L src test -type f -name "*.[ch]pp" ! -path "*/vendor/*") \
	-- -Isrc -Isrc/vendor -std=c++20
