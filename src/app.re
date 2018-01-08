open Types;

open Utils;

type load = {. "quotes": array(quote)};

type state = {
  quotes: array(quote),
  symbols: array(symbol),
  symbolInput: string
};

type action =
  | AddQuote(quote)
  | AddSymbol
  | Load(load)
  | UpdateSymbolInput(string);

let component = ReasonReact.reducerComponent("App");

let httpLinkOptions: ApolloClient.linkOptions = {"uri": "http://localhost:8080/graphql"};

let apolloClientOptions: ApolloClient.clientOptions = {
  "cache": ApolloClient.inMemoryCache(),
  "link": ApolloClient.httpLink(httpLinkOptions)
};

let client = ApolloClient.apolloClient(apolloClientOptions);

let addSymbol = (event) => {
  ReactEventRe.Form.preventDefault(event);
  AddSymbol
};

let updateSymbolInput = (event) =>
  UpdateSymbolInput(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let make = (_children) => {
  ...component,
  initialState: () => {
    let symbols: array(string) =
      switch Dom.Storage.(localStorage |> getItem(namespace)) {
      | None => [||]
      | Some(stringifiedJson) => parseJson(stringifiedJson)
      };
    {quotes: [||], symbols, symbolInput: ""}
  },
  reducer: (action, state) =>
    switch action {
    | Load(data) =>
      let quotes = data##quotes;
      ReasonReact.Update({...state, quotes})
    | AddQuote(quote) =>
      let quotes = Array.append(state.quotes, [|quote|]);
      let symbols = Array.append(state.symbols, [|state.symbolInput|]);
      saveLocally(symbols);
      ReasonReact.Update({quotes, symbols, symbolInput: ""})
    | AddSymbol =>
      let symbols = Array.append(state.symbols, [|state.symbolInput|]);
      ReasonReact.UpdateWithSideEffects(
        state,
        (
          (self) => {
            let variables = {"symbols": symbols};
            let options = {"query": Queries.quotes, "variables": variables};
            client##query(options)
            |> Js.Promise.then_(
                 (response) => {
                   let responseData = response##data;
                   let leng = Array.length(responseData##quotes);
                   let quotes: array(possibleQuote) = responseData##quotes;
                   let newQuote = quotes[leng - 1];
                   let nullableQuote = Js.Nullable.to_opt(newQuote);
                   switch nullableQuote {
                   | None => Js.log("No matching symbol!")
                   | Some(quote) =>
                     let addQuoteAction = (value) => AddQuote(value);
                     let quoteToAdd = {
                       "ask_price": quote##ask_price,
                       "description": quote##description,
                       "high_52_weeks": quote##high_52_weeks,
                       "low_52_weeks": quote##low_52_weeks,
                       "last_trade_price": quote##last_trade_price,
                       "simple_name": quote##simple_name,
                       "symbol": quote##symbol,
                       "trade_price_delta": quote##trade_price_delta,
                       "trade_price_delta_percentage": quote##trade_price_delta_percentage,
                       "updated_at": quote##updated_at
                     };
                     self.reduce(addQuoteAction, quoteToAdd);
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
    if (Array.length(state.symbols) > 0) {
      let variables = {"symbols": state.symbols};
      let options = {"query": Queries.quotes, "variables": variables};
      client##query(options)
      |> Js.Promise.then_(
           (response) => {
             let responseData = response##data;
             let loadAction = (responseData) => Load(responseData);
             reduce(loadAction, responseData);
             Js.Promise.resolve()
           }
         )
      |> ignore
    };
    ReasonReact.NoUpdate
  },
  render: ({reduce, state}) =>
    <div className="app-container">
      <div className="symbols-container">
        <form onSubmit=(reduce(addSymbol))>
          <input
            placeholder="Enter a stock symbol"
            onChange=(reduce(updateSymbolInput))
            value=state.symbolInput
          />
        </form>
      </div>
      <Quotes quotes=state.quotes />
    </div>
};