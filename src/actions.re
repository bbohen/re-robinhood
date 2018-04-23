open Types;

type graphPayload = {. "symbol": string, "index": int};

type t =
  | AddSymbol
  | AddSymbolSuccess(quote)
  | LoadHistoricalDataForQuote(graphPayload)
  | LoadHistoricalDataForQuoteSuccess(quote, int)
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

let loadHistoricalData = (graphPayload) => LoadHistoricalDataForQuote(graphPayload);

let removeQuote = (symbol) => RemoveSymbol(symbol);

let toggleTheme = (_event) => ToggleTheme;

let updateSymbolInput = (event) =>
  UpdateSymbolInput(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);