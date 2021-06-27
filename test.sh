#!/bin/sh

UZR_API=http://localhost:8080

fetch() {
	printf "\nfetch $1\n"

	raw=$(curl -o - -w "\n%{http_code}" -s $UZR_API$1)

	response=$(echo "$raw" | head -n -1 -)
	http_code=$(echo "$raw" | tail -n 1 -)
}

assert_status() {
	[ "$http_code" = "$1" ] || {
		printf "\033[91mFAIL\033[0m: Expected HTTP status \`$1\`, got \`$http_code\`\n"
		stop
	}

	printf "\033[92mPASS\033[0m: HTTP $http_code\n"
}

assert_response() {
	[ "$response" = "$1" ] || {
		printf "\033[91mFAIL\033[0m: Expected response \`$1\`, got \`$response\`\n"
		stop
	}

	printf "\033[92mPASS\033[0m: RESP $response\n"
}

assert_response_contains() {
	case "$response" in
		*$1*) ;;
		*)
			printf "\033[91mFAIL\033[0m: Expected response to contain \`$1\`, got \`$response\`\n";
			stop
			;;
	esac

	printf "\033[92mPASS\033[0m: RESP contains $1\n"
}

SUDO=$(command -v doas || command -v sudo)

export UZR_ADMIN_USER=ci
export UZR_ADMIN_PW=ci_testing_password

printf "UZR_ADMIN_USER=$UZR_ADMIN_USER\nUZR_ADMIN_PW=$UZR_ADMIN_PW\n" > .env

$SUDO docker-compose up --build -d || stop

# not ideal
sleep 1

fetch /health
assert_status 200
assert_response ok

fetch /login/$UZR_ADMIN_USER/$UZR_ADMIN_PW
assert_status 200
assert_response_contains $UZR_ADMIN_USER

fetch /login/$UZR_ADMIN_USER/incorrect_password
assert_status 401
assert_response "{}"

fetch /login/incorrect_username/_
assert_status 401
assert_response "{}"

$SUDO docker-compose down
rm .env
