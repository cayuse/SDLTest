#!/bin/sh

set -e
cd "$(dirname "$0")"

case $(uname) in
    Darwin)
        brew update
        brew install sdl2 sdl2_image
        ;;
    Linux)
        sudo apt-get update -qq
        sudo apt-get install -qq libsdl2-dev libsdl2-image-dev
        ;;
    *)
        echo "Unknown OS: $(uname)"
        exit 1
        ;;
esac

