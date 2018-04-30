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