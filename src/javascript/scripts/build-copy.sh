#!/usr/bin/env bash

# Copy over to the `bin` directory
test -f bazel-bin/src/javascript/uml-wasm/uml-wasm.js && cp -rf bazel-bin/src/javascript/uml-wasm/uml-wasm.js src/javascript/bin/
test -f bazel-bin/src/javascript/uml-js/uml-js.js && cp -rf bazel-bin/src/javascript/uml-js/uml-js.js src/javascript/bin/

exit 0