#!/usr/bin/env bash
set -euo pipefail

# Build the WASM variant
bazel build -c  opt  //src/javascript:uml-wasm