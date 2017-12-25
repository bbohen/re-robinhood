open Types;

type load = {. "quotes": array(quote)};

type state = {
  quotes: array(quote),
  symbols: array(symbol),
  symbolInput: string
};

type action =
  | AddFund(quote)
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

let quotes_query =
  gql(
    {|
      query quote($symbols: [String]) {
        quotes(symbols: $symbols) {
          ask_price
          high_52_weeks
          low_52_weeks
          simple_name
          symbol
          updated_at
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
  initialState: () => {quotes: [||], symbols: [|"AAPL", "FB"|], symbolInput: ""},
  reducer: (action, state) =>
    switch action {
    | Load(data) =>
      let fundamentals = data##quotes;
      ReasonReact.Update({...state, quotes: fundamentals})
    | AddFund(quote) =>
      let newQuotes = Array.append(state.quotes, [|quote|]);
      ReasonReact.Update({...state, quotes: newQuotes})
    | AddSymbol =>
      let symbols = Array.append(state.symbols, [|state.symbolInput|]);
      ReasonReact.UpdateWithSideEffects(
        {...state, symbolInput: "", symbols},
        (
          (self) => {
            let variables = {"symbols": symbols};
            let options = {"query": quotes_query, "variables": variables};
            client##query(options)
            |> Js.Promise.then_(
                 (response) => {
                   let responseData = response##data;
                   let leng = Array.length(responseData##quotes);
                   let fundamentals: array(possibleFund) = responseData##quotes;
                   let newFund = fundamentals[leng - 1];
                   let nullableFund = Js.Nullable.to_opt(newFund);
                   switch nullableFund {
                   | None => Js.log("No matching symbol!")
                   | Some(quote) =>
                     let addAction = (value) => AddFund(value);
                     let quoteToAdd = {
                       "ask_price": quote##ask_price,
                       "description": quote##description,
                       "high_52_weeks": quote##high_52_weeks,
                       "low_52_weeks": quote##low_52_weeks,
                       "last_trade_price": quote##last_trade_price,
                       "simple_name": quote##simple_name,
                       "symbol": quote##symbol,
                       "updated_at": quote##updated_at
                     };
                     self.reduce(addAction, quoteToAdd);
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
    let options = {"query": quotes_query, "variables": variables};
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