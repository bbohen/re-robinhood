type data;

type symbol = string;

type quote = {
  .
  "ask_price": string,
  "description": string,
  "high_52_weeks": string,
  "low_52_weeks": string,
  "simple_name": string,
  "last_trade_price": string,
  "symbol": string,
  "trade_price_delta": int,
  "trade_price_delta_percentage": string,
  "updated_at": string
};

type possibleFund =
  Js.Nullable.t(
    {
      .
      "ask_price": string,
      "description": string,
      "high_52_weeks": string,
      "low_52_weeks": string,
      "simple_name": string,
      "last_trade_price": string,
      "symbol": string,
      "trade_price_delta": int,
      "trade_price_delta_percentage": string,
      "updated_at": string
    }
  );

type gql = string => unit;

[@bs.module] external gql : gql = "graphql-tag";