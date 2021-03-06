open Types;

type clientOptions = {. "cache": unit, "link": unit};

type linkOptions = {. "uri": string};

[@bs.module "graphql-tag"] external gql : gql = "gql";

[@bs.module "apollo-client-preset"] [@bs.new] external apolloClient : clientOptions => 'a =
  "ApolloClient";

[@bs.module "apollo-client-preset"] [@bs.new] external httpLink : linkOptions => 'a = "HttpLink";

[@bs.module "apollo-client-preset"] [@bs.new] external inMemoryCache : unit => 'a =
  "InMemoryCache";

[@bs.module "react-apollo"] [@bs.new] external graphql : unit => 'a = "graphql";