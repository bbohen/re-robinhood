type data;

type symbol = string;

type quote = {. "ask_price": string, "symbol": string};

type possibleFund = Js.Nullable.t({. "ask_price": string, "symbol": string});

type gql = string => unit;

[@bs.module] external gql : gql = "graphql-tag";