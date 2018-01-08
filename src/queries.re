open Types;

let quotes =
  gql(
    {|
      query quote($symbols: [String]) {
        quotes(symbols: $symbols) {
          ask_price
          last_trade_price
          high_52_weeks
          low_52_weeks
          simple_name
          symbol
          trade_price_delta
          trade_price_delta_percentage
          updated_at
        }
      }
    |}
  );