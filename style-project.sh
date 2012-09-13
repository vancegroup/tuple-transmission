#!/bin/sh

PROJECT=$(cd $(dirname $0) && pwd)
astyle -n --recursive "${PROJECT}/tuple-transmission/*.h" "${PROJECT}/tests/*.cpp"
astyle -n --exclude=ProtocolForTest.h --recursive "${PROJECT}/tests/*.h"
if which lua-styler > /dev/null; then
	lua-styler --nobackup ${PROJECT}/generation/*.lua
fi
