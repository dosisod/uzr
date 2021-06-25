#!/bin/sh

UZR_API=http://localhost:8080

fetch() {
	printf "fetch $1\n"

	raw=$(curl -o - -w "\n%{http_code}" -s $UZR_API$1)

	response=$(echo "$raw" | head -n -1 -)
	http_code=$(echo "$raw" | tail -n 1 -)
}

assert_status() {
	[ "$http_code" = "$1" ] || {
		printf "\033[91mFAIL\033[0m: Expected HTTP status \`$1\`, got \`$http_code\`\n"
		exit 1
	}

	printf "\033[92mPASS\033[0m: HTTP $http_code\n"
}

assert_response() {
	[ "$response" = "$1" ] || {
		printf "\033[91mFAIL\033[0m: Expected response \`$1\`, got \`$response\`\n"
		exit 1
	}

	printf "\033[92mPASS\033[0m: RESP $response\n"
}

fetch /health
assert_status 200
assert_response ok
