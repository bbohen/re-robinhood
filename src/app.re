open Actions;

open Reducer;

open Utils;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    let symbols: array(string) =
      switch (Dom.Storage.(localStorage |> getItem(namespace))) {
      | None => [||]
      | Some(stringifiedJson) => parseJson(stringifiedJson)
      };
    {darkTheme: true, quotes: [||], symbols, symbolInput: ""};
  },
  reducer: appReducer,
  didMount: ({send, state}) =>
    if (Array.length(state.symbols) > 0) {
      let variables = {"symbols": state.symbols};
      let options = {"query": Queries.quotes, "variables": variables};
      client##query(options)
      |> Js.Promise.then_(response => {
           let responseData = response##data;
           send(LoadInitialQuotesSuccess(responseData));
           Js.Promise.resolve();
         })
      |> ignore;
    },
  render: ({send, state}) => {
    let themeClassName = state.darkTheme ? "dark-theme" : "light-theme";
    let appClassName = "app-container " ++ themeClassName;
    <div className=appClassName>
      <AppHeader
        isDarkTheme=state.darkTheme
        onThemeToggle={_event => send(ToggleTheme)}
      />
      <div className="symbols-container">
        <form onSubmit={event => {
          ReactEventRe.Form.preventDefault(event);
          send(AddSymbol);
        }}>
          <input
            placeholder="Enter a stock symbol"
            onChange={event => {
              send(UpdateSymbolInput(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
              ))
            }}
            value=state.symbolInput
          />
        </form>
      </div>
      <Quotes
        loadHistoricalData={data => send(LoadHistoricalDataForQuote(data))}
        removeQuote=(symbol => send(RemoveSymbol(symbol)))
        quotes=state.quotes
      />
    </div>;
  },
};
