open Types;

type load = {. "fundamentals": array(fund)};

type state = {funds: array(fund)};

type action =
  | Load(load);

[@bs.module] external gql : gql = "graphql-tag";

let component = ReasonReact.reducerComponent("App");

let httpLinkOptions: ApolloClient.linkOptions = {"uri": "http://localhost:8080/graphql"};

let apolloClientOptions: ApolloClient.clientOptions = {
  "cache": ApolloClient.inMemoryCache(),
  "link": ApolloClient.httpLink(httpLinkOptions)
};

let client = ApolloClient.apolloClient(apolloClientOptions);

let fundamentals_query: query =
  gql(
    {|
      query fund($symbols: [String]) {
        fundamentals(symbols: $symbols) {
          market_cap
          description
        }
      }
    |}
  );

/* TODO: LEFT OFF HERE getting vars for the query */
/* let variables =  */
let make = (_children) => {
  ...component,
  initialState: () => {funds: [||]},
  reducer: (action, state) =>
    switch action {
    | Load(data) =>
      let fundamentals = data##fundamentals;
      ReasonReact.Update({funds: fundamentals})
    },
  didMount: ({reduce}) => {
    let variables = {"symbols": ("AAPL", "FB")};
    let options = {"query": fundamentals_query, "variables": variables};
    client##query(options)
    |> Js.Promise.then_(
         (response) => {
           let responseData = response##data;
           let loadAction = (responseData) => Load(responseData);
           reduce(loadAction, responseData);
           Js.Promise.resolve()
         }
       );
    ReasonReact.NoUpdate
  },
  render: ({state}) => {
    let fundItems = Array.map((fund) => <Fund description=fund##description />, state.funds);
    <div>
      <h1> (ReasonReact.stringToElement("Funds!")) </h1>
      (ReasonReact.arrayToElement(fundItems))
    </div>
  }
};