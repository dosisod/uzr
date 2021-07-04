#!/bin/sh

UZR_API=http://localhost:8080

GET() {
	fetch GET $1 $2
}

POST() {
	fetch POST $1 $2
}

fetch() {
	printf "\nfetch $2\n"

	[ "$3" = "" ] || json="-d $3"

	raw=$(curl -o - -X $1 $json -w "\n%{http_code}" -s $UZR_API$2)

	response=$(echo "$raw" | head -n -1 -)
	http_code=$(echo "$raw" | tail -n 1 -)
}

die() {
	[ -f .env.bak ] && mv -f .env.bak .env
	exit 1
}

assert_status() {
	[ "$http_code" = "$1" ] || {
		printf "\033[91mFAIL\033[0m: Expected HTTP status \`$1\`, got \`$http_code\`\n"
		die
	}

	printf "\033[92mPASS\033[0m: HTTP $http_code\n"
}

assert_response() {
	[ "$response" = "$1" ] || {
		printf "\033[91mFAIL\033[0m: Expected response \`$1\`, got \`$response\`\n"
		die
	}

	printf "\033[92mPASS\033[0m: RESP $response\n"
}

assert_response_contains() {
	case "$response" in
		*$1*) ;;
		*)
			printf "\033[91mFAIL\033[0m: Expected response to contain \`$1\`, got \`$response\`\n";
			die
			;;
	esac

	printf "\033[92mPASS\033[0m: RESP contains $1\n"
}

SUDO=$(command -v doas || command -v sudo)

[ -f .env ] && mv -f .env .env.bak

export UZR_ADMIN_USER=ci
export UZR_ADMIN_PW=ci_testing_password

printf "UZR_ADMIN_USER=$UZR_ADMIN_USER\nUZR_ADMIN_PW=$UZR_ADMIN_PW\n" > .env

$SUDO docker-compose -p ci up --build -d || die

# not ideal
sleep 1

GET /health
assert_status 200
assert_response ok

POST /login '{"username":"'$UZR_ADMIN_USER'","password":"'$UZR_ADMIN_PW'"}'
assert_status 200
assert_response_contains $UZR_ADMIN_USER

POST /login '{"username":"'$UZR_ADMIN_USER'","password":"incorrect_password"}'
assert_status 401
assert_response "Invalid username or password"

POST /login '{"username":"invalid_username","password":"_"}'
assert_status 401
assert_response "Invalid username or password"

POST /login "invalid json"
assert_status 400
assert_response_contains "exception"

$SUDO docker-compose -p ci down -v

[ ! -f .env.bak ] || mv -f .env.bak .env
