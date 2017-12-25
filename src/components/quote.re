let component = ReasonReact.statelessComponent("Quote");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~quote, _children) => {
  ...component,
  render: (self) =>
    <div onClick=(self.handle(handleClick))>
      <h2>
        (ReasonReact.stringToElement(quote##simple_name))
        (ReasonReact.stringToElement(" (" ++ quote##symbol ++ ")"))
      </h2>
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
};