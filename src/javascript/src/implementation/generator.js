/**
 * @implements Generator
 */
export const GeneratorImpl = (library) => {
  /**
   * @interface Generator
   */
  return {
    /**
     * UML Diagrams Generator
     *
     * @function
     * @name Generator.generate
     * @param {String} text Text to generate UML diagram from
     * @param {String} diagram Diagram type
     * @param {String} layout Layout type
     * @param {String} edge Edge type
     * @param {String} config Configuration JSON string
     * @returns {String} The generated UML diagram
     */
    generate(text = 'Text', diagram = 'class', layout = 'FMMM', edge = 'Bens', config='{}') {

      return library.Generator.Generate(text, diagram, layout, edge, config);
    },
  };
};
