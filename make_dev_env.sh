#!/bin/sh

set -e

tag_as="uzr-dev"
port=8080

build_args="$(cat .env | xargs -n 1 echo --build-arg | tr '\n' ' ')"

sudo env docker build $build_args -t "$tag_as" -f Dockerfile.dev .

sudo docker run \
	--rm \
	-it \
	-p "$port:$port" \
	-v "$PWD/:/app" \
	"$tag_as" sh
