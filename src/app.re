open Types;

[@bs.module] external gql : string => 'a = "graphql-tag";

let component = ReasonReact.statelessComponent("App");

let httpLinkOptions: ApolloClient.linkOptions = {"uri": "http://localhost:8080/graphql"};

let cache = ApolloClient.inMemoryCache;

let link = ApolloClient.httpLink;

let make = (_children) => {
  ...component,
  render: (_self) => {
    let apolloClientOptions: ApolloClient.clientOptions = {
      "cache": cache(),
      "link": link(httpLinkOptions)
    };
    let client = ApolloClient.apolloClient(apolloClientOptions);
    let todos_query: query =
      gql(
        {|
          query fund {
            fundamentals(symbols: ["AAPL", "FB"]) {
              market_cap
              description
            }
          }
        |}
      );
    client##query({"query": todos_query}) |> Js.Promise.then_(() => Js.Promise.resolve());
    <Page message="Almost there..." />
  }
};
