#!/usr/bin/env lua

-- Data
local lines = {}

-- Utility function
local indent = function(amount)
	return ("\t"):rep(amount + data.baseIndent)
end

-- Main
local main = function(arg)
	if arg[1] == nil then
		error("Must pass a data file name!")
	end

	fn = arg[1]

	if arg[2] == nil then
		source = arg[0] .. " " .. arg[1]
	else
		source = arg[2]
	end

	data = dofile(arg[1])

	table.insert(lines, data.prefix:format(source))
	for i = 1, data.maxArity do
		data.generateOverload(i)
	end
	table.insert(lines, data.suffix)

	print(cat(lines, "\n"))
end

--[[ Functions callable by generation data ]]
out = function(a, b)
	if type(a) == "string" then
		table.insert(lines, indent(0) .. a)
	else
		table.insert(lines, indent(a) .. b)
	end
end

genRange = function(count, f, sep)
	local ret = {}
	for i = 1, count do
		table.insert(ret, f(i))
	end
	return cat(ret, sep or "")
end

cat = table.concat

-- Call main

main(arg)