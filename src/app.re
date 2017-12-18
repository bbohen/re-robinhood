open Types;

type load = {. "fundamentals": array(fund)};

type state = {
  funds: array(fund),
  symbols: array(symbol),
  symbolInput: string
};

type action =
  | AddFund(fund)
  | AddSymbol
  | Load(load)
  | UpdateSymbolInput(string);

[@bs.module] external gql : gql = "graphql-tag";

let component = ReasonReact.reducerComponent("App");

let httpLinkOptions: ApolloClient.linkOptions = {"uri": "http://localhost:8080/graphql"};

let apolloClientOptions: ApolloClient.clientOptions = {
  "cache": ApolloClient.inMemoryCache(),
  "link": ApolloClient.httpLink(httpLinkOptions)
};

let client = ApolloClient.apolloClient(apolloClientOptions);

let fundamentals_query =
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

let addSymbol = (event) => {
  ReactEventRe.Form.preventDefault(event);
  AddSymbol
};

let updateSymbolInput = (event) =>
  UpdateSymbolInput(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let make = (_children) => {
  ...component,
  initialState: () => {funds: [||], symbols: [|"AAPL", "FB"|], symbolInput: ""},
  reducer: (action, state) =>
    switch action {
    | Load(data) =>
      let fundamentals = data##fundamentals;
      ReasonReact.Update({...state, funds: fundamentals})
    | AddFund(fund) =>
      let newFunds = Array.append(state.funds, [|fund|]);
      ReasonReact.Update({...state, funds: newFunds})
    | AddSymbol =>
      let symbols = Array.append(state.symbols, [|state.symbolInput|]);
      ReasonReact.UpdateWithSideEffects(
        {...state, symbolInput: "", symbols},
        (
          (self) => {
            let variables = {"symbols": symbols};
            let options = {"query": fundamentals_query, "variables": variables};
            client##query(options)
            |> Js.Promise.then_(
                 (response) => {
                   let responseData = response##data;
                   let leng = Array.length(responseData##fundamentals);
                   let fundamentals: array(possibleFund) = responseData##fundamentals;
                   let newFund = fundamentals[leng - 1];
                   let nullableFund = Js.Nullable.to_opt(newFund);
                   switch nullableFund {
                   | None => Js.log("No matching symbol!")
                   | Some(name) =>
                     let addAction = (thinger) => AddFund(thinger);
                     let recreatedFund = {"description": name##description};
                     self.reduce(addAction, recreatedFund);
                     ()
                   };
                   Js.Promise.resolve()
                 }
               )
            |> ignore;
            ()
          }
        )
      )
    | UpdateSymbolInput(value) => ReasonReact.Update({...state, symbolInput: value})
    },
  didMount: ({reduce, state}) => {
    let variables = {"symbols": state.symbols};
    let options = {"query": fundamentals_query, "variables": variables};
    client##query(options)
    |> Js.Promise.then_(
         (response) => {
           let responseData = response##data;
           let loadAction = (responseData) => Load(responseData);
           reduce(loadAction, responseData);
           Js.Promise.resolve()
         }
       )
    |> ignore;
    ReasonReact.NoUpdate
  },
  render: ({reduce, state}) => {
    let fundItems = Array.map((fund: fund) => <Fund description=fund##description />, state.funds);
    let symbols = Array.map((symbol) => <Symbol label=symbol />, state.symbols);
    <div>
      <h1> (ReasonReact.stringToElement("Symbols:")) </h1>
      (ReasonReact.arrayToElement(symbols))
      <form onSubmit=(reduce(addSymbol))>
        <input onChange=(reduce(updateSymbolInput)) value=state.symbolInput />
      </form>
      <h1> (ReasonReact.stringToElement("Data:")) </h1>
      (ReasonReact.arrayToElement(fundItems))
    </div>
  }
};