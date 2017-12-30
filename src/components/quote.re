let component = ReasonReact.statelessComponent("Quote");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~quote, _children) => {
  ...component,
  render: (self) => {
    let stockHadPositiveDelta = quote##trade_price_delta > 0;
    let quoteCssClass = stockHadPositiveDelta ? "positive" : "negative";
    <div className=quoteCssClass onClick=(self.handle(handleClick))>
      <div className="quote-header">
        <span>
          (ReasonReact.stringToElement(quote##simple_name))
          (ReasonReact.stringToElement(" (" ++ quote##symbol ++ ")"))
        </span>
        <span>
          (ReasonReact.stringToElement(quote##last_trade_price))
          (ReasonReact.stringToElement(" (" ++ string_of_int(quote##trade_price_delta) ++ ")"))
        </span>
      </div>
      <div>
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
      </div>
    </div>
  }
};