#!/bin/sh

PROJECT=$(cd $(dirname $0) && pwd)
astyle -n --recursive "${PROJECT}/tuple-transmission/*.h" "${PROJECT}/tests/*.cpp"
