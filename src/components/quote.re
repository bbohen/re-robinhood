let component = ReasonReact.statelessComponent("Quote");

let make = (~quote, ~loadGraphData, ~onRemoveClick, _children) => {
  ...component,
  didMount: (_self) => {
    loadGraphData();
    ()
  },
  render: (_self) => {
    let stockHadPositiveDelta = quote##trade_price_delta > 0;
    let quoteCssClass = stockHadPositiveDelta ? "positive" : "negative";
    let formattedDelta =
      "$"
      ++ string_of_int(quote##trade_price_delta)
      ++ " / "
      ++ quote##trade_price_delta_percentage;
    <div className=quoteCssClass>
      <div className="quote-header">
        <div>
          <div className="quote-symbol"> (ReasonReact.string(quote##symbol)) </div>
          <div className="quote-name"> (ReasonReact.string(quote##simple_name)) </div>
        </div>
        <div>
          <div className="quote-last-trade-price trend-color">
            (ReasonReact.string("$" ++ quote##last_trade_price))
          </div>
          <div className="quote-formatted-delta trend-color">
            (ReasonReact.string(formattedDelta))
          </div>
        </div>
      </div>
      <div className="quote-chart">
        <PixelChart chartId=quote##symbol values=quote##historical_data />
      </div>
      <div className="quote-body">
        <div>
          <span> (ReasonReact.string("Asking Price: ")) </span>
          <span> (ReasonReact.string(quote##ask_price)) </span>
        </div>
        <div>
          <span> (ReasonReact.string("52 Week Low: ")) </span>
          <span> (ReasonReact.string(quote##low_52_weeks)) </span>
        </div>
        <div>
          <span> (ReasonReact.string("52 Week High: ")) </span>
          <span> (ReasonReact.string(quote##high_52_weeks)) </span>
        </div>
        <div>
          <span> (ReasonReact.string("Last Updated: ")) </span>
          <span> (ReasonReact.string(quote##hours_since_update ++ " hours ago")) </span>
        </div>
      </div>
      <div onClick=onRemoveClick className="quote-footer"> (ReasonReact.string("Remove")) </div>
    </div>
  }
};