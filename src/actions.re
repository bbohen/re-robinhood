open Types;

type t =
  | AddSymbol
  | AddSymbolSuccess(quote)
  | LoadInitialQuotesSuccess(payload)
  | RemoveSymbol(string)
  | RemoveSymbolSuccess(array(string), payload)
  | ToggleTheme
  | UpdateSymbolInput(string);

let addSymbol = (event) => {
  ReactEventRe.Form.preventDefault(event);
  AddSymbol
};

let addQuote = (value) => AddSymbolSuccess(value);

let load = (responseData) => LoadInitialQuotesSuccess(responseData);

let removeQuote = (symbol) => RemoveSymbol(symbol);

let toggleTheme = (_event) => ToggleTheme;

let updateSymbolInput = (event) =>
  UpdateSymbolInput(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);