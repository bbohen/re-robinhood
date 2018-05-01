type data;

type quote = {
  .
  "ask_price": string,
  "description": string,
  "high_52_weeks": string,
  "historical_data": array(int),
  "low_52_weeks": string,
  "simple_name": string,
  "last_trade_price": string,
  "symbol": string,
  "trade_price_delta": int,
  "trade_price_delta_percentage": string,
  "hours_since_update": string,
};

type payload = {. "quotes": array(quote)};

type possibleQuote =
  Js.Nullable.t(
    {
      .
      "ask_price": string,
      "description": string,
      "high_52_weeks": string,
      "historical_data": array(int),
      "low_52_weeks": string,
      "simple_name": string,
      "last_trade_price": string,
      "symbol": string,
      "trade_price_delta": int,
      "trade_price_delta_percentage": string,
      "hours_since_update": string,
    },
  );

type graphPayload = {. "symbol": string, "index": int};

type actions =
  | AddSymbol
  | AddSymbolSuccess(quote)
  | LoadHistoricalDataForQuote(graphPayload)
  | LoadHistoricalDataForQuoteSuccess(quote, int)
  | LoadInitialQuotesSuccess(payload)
  | RemoveSymbol(string)
  | RemoveSymbolSuccess(array(string), payload)
  | ToggleTheme
  | UpdateSymbolInput(string);

type gql = string => unit;

[@bs.module] external gql : gql = "graphql-tag";
