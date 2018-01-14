let component = ReasonReact.statelessComponent("Quote");

let make = (~quote, ~onRemoveClick, _children) => {
  ...component,
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
          <div className="quote-symbol"> (ReasonReact.stringToElement(quote##symbol)) </div>
          <div className="quote-name"> (ReasonReact.stringToElement(quote##simple_name)) </div>
        </div>
        <div>
          <div className="quote-last-trade-price trend-color">
            (ReasonReact.stringToElement("$" ++ quote##last_trade_price))
          </div>
          <div className="quote-formatted-delta trend-color">
            (ReasonReact.stringToElement(formattedDelta))
          </div>
        </div>
      </div>
      <div className="quote-body">
        <div>
          <span> (ReasonReact.stringToElement("Asking Price: ")) </span>
          <span> (ReasonReact.stringToElement(quote##ask_price)) </span>
        </div>
        <div>
          <span> (ReasonReact.stringToElement("52 Week Low: ")) </span>
          <span> (ReasonReact.stringToElement(quote##low_52_weeks)) </span>
        </div>
        <div>
          <span> (ReasonReact.stringToElement("52 Week High: ")) </span>
          <span> (ReasonReact.stringToElement(quote##high_52_weeks)) </span>
        </div>
        <div>
          <span> (ReasonReact.stringToElement("Last Updated: ")) </span>
          <span> (ReasonReact.stringToElement(quote##updated_at)) </span>
        </div>
      </div>
      <div onClick=onRemoveClick className="quote-footer">
        (ReasonReact.stringToElement("Remove"))
      </div>
    </div>
  }
};