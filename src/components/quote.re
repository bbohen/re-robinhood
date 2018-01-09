let component = ReasonReact.statelessComponent("Quote");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~quote, _children) => {
  ...component,
  render: (self) => {
    let stockHadPositiveDelta = quote##trade_price_delta > 0;
    let quoteCssClass = stockHadPositiveDelta ? "positive" : "negative";
    let formattedDelta =
      "$"
      ++ string_of_int(quote##trade_price_delta)
      ++ " / "
      ++ quote##trade_price_delta_percentage;
    <div className=quoteCssClass onClick=(self.handle(handleClick))>
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
    </div>
    /* <div>
         (ReasonReact.stringToElement("Asking Price: "))
         (ReasonReact.stringToElement(quote##ask_price))
       </div>
       <div>
         (ReasonReact.stringToElement("52 Week Low: "))
         (ReasonReact.stringToElement(quote##low_52_weeks))
       </div>
       <div>
         (ReasonReact.stringToElement("52 Week High: "))
         (ReasonReact.stringToElement(quote##high_52_weeks))
       </div>
       <div>
         (ReasonReact.stringToElement("Last Updated: "))
         (ReasonReact.stringToElement(quote##updated_at))
       </div> */
  }
};