/*
 * This is needed for bucklescript to play nice with webpack css-loader
 * Once the apollo-client issue below is resolved, webpack can be removed in favor of parcel
 * https://github.com/apollographql/apollo-client/issues/2785
 */
[%bs.raw {|require('./styles.css')|}];

ReactDOMRe.renderToElementWithId(<App />, "index");
