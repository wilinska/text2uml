// Copyrights MIT Licence bazel-emscripten poject

import {terser} from 'rollup-plugin-terser';

const variants = ['wasm'];
const formats = ['umd', 'es'];

const outputs = variants.reduce(
    (acc, variant) =>
        [...acc,
         {
           input: `src/javascript/src/index_${variant}.js`,
           output: formats.reduce(
               (acc, format) =>
                   [...acc,
                    {
                      file: `src/javascript/dist/${variant}/${format}/index.js`,
                      sourcemap: true,
                      format,
                      name: 'Text2UML',
                      plugins: [terser()],
                    },
],
               []),
         },
],
    []);

export default outputs;