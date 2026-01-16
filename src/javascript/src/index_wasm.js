import WasmLibrary from '../bin/uml-wasm';

import {GeneratorImpl} from './implementation/generator';
import {createLoader} from './loader';

/**
 * Main export for the library
 */
export default async () => {
  const {library} = await createLoader(WasmLibrary);

  return {
    Generator: GeneratorImpl(library),
  };
};