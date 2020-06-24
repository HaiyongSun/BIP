#!/bin/bash
FDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ROOT=${FDIR}

ENGINE=${1:-reference-engine}

export PATH=$PATH:$(ls -d ${FDIR}/bipc-*/bin/)

export BIP2_ENGINE_LIB_DIR=$(ls -d ${FDIR}/BIP-${ENGINE}-*/lib/static/)

export BIP2_ENGINE_SPECIFIC_DIR=$(ls -d ${FDIR}/BIP-${ENGINE}-*/include/specific/)
export BIP2_ENGINE_GENERIC_DIR=$(ls -d ${FDIR}/BIP-${ENGINE}-*/include/generic/)
echo "Environment configured for engine: " ${ENGINE}


