open Types;

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