open Reducer;

open Utils;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    let symbols: array(string) =
      switch Dom.Storage.(localStorage |> getItem(namespace)) {
      | None => [||]
      | Some(stringifiedJson) => parseJson(stringifiedJson)
      };
    {darkTheme: true, quotes: [||], symbols, symbolInput: ""}
  },
  reducer: appReducer,
  didMount: ({reduce, state}) => {
    if (Array.length(state.symbols) > 0) {
      let variables = {"symbols": state.symbols};
      let options = {"query": Queries.quotes, "variables": variables};
      client##query(options)
      |> Js.Promise.then_(
           (response) => {
             let responseData = response##data;
             reduce(Actions.loadAction, responseData);
             Js.Promise.resolve()
           }
         )
      |> ignore
    };
    ReasonReact.NoUpdate
  },
  render: ({reduce, state}) => {
    let themeClassName = state.darkTheme ? "dark-theme" : "light-theme";
    let appClassName = "app-container " ++ themeClassName;
    <div className=appClassName>
      <AppHeader isDarkTheme=state.darkTheme onThemeToggle=(reduce(Actions.toggleTheme)) />
      <div className="symbols-container">
        <form onSubmit=(reduce(Actions.addSymbol))>
          <input
            placeholder="Enter a stock symbol"
            onChange=(reduce(Actions.updateSymbolInput))
            value=state.symbolInput
          />
        </form>
      </div>
      <Quotes removeQuote=(reduce(Actions.removeQuote)) quotes=state.quotes />
    </div>
  }
};