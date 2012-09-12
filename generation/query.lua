#!/usr/bin/env lua
if arg[1] == nil then
	error("Must pass a parameter and a data file name!")
end
paramName = arg[1]

if arg[2] == nil then
	error("Must pass a data file name too!")
end
fn = arg[2]

data = dofile(fn)
print(data[paramName])
