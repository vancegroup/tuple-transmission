#!/bin/sh
set -e

SCRIPTDIR=$(cd $(dirname $0) && pwd)
OUTDIR=$(cd $(dirname $0) && cd ../tuple-transmission && pwd)

query=${SCRIPTDIR}/query.lua
generate=${SCRIPTDIR}/variadicGenerate.lua

generate_base=$(basename "${generate}")

echo

for fn in ${SCRIPTDIR}/*.gen.lua; do
	input_base=$(basename "${fn}")
	output_rel=$("${query}" outFile "${fn}")
	output=${OUTDIR}/${output_rel}

	echo -n "Generating $output_rel from $input_base"

	"${generate}" "$fn" "${generate_base} on input ${input_base}" > "${output}"

	echo "\t-\tDone."
done

echo "Done generating headers."
echo
