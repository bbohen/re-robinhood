open Types;

type t =
  | AddSymbol
  | AddSymbolSuccess(quote)
  | LoadInitialQuotesSuccess(load)
  | RemoveSymbol(string)
  | RemoveSymbolSuccess(array(string), load)
  | ToggleTheme
  | UpdateSymbolInput(string);

let addSymbol = (event) => {
  ReactEventRe.Form.preventDefault(event);
  AddSymbol
};

let addQuoteAction = (value) => AddSymbolSuccess(value);

let loadAction = (responseData) => LoadInitialQuotesSuccess(responseData);

let removeQuote = (symbol) => RemoveSymbol(symbol);

let toggleTheme = (_event) => ToggleTheme;

let updateSymbolInput = (event) =>
  UpdateSymbolInput(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);