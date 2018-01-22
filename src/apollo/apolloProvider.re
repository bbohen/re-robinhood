[@bs.module "react-apollo"] external apollo_provider : ReasonReact.reactClass = "ApolloProvider";

let make = (~client, children) =>
  ReasonReact.wrapJsForReason(~reactClass=apollo_provider, ~props={"client": client}, children);