type data;

type symbol = string;

type fund = {. "description": string};

type possibleFund = Js.Nullable.t({. "description": string});

type gql = string => unit;

[@bs.module] external gql : gql = "graphql-tag";