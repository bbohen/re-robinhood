let component = ReasonReact.statelessComponent("Quote");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~quote, _children) => {
  ...component,
  render: (self) =>
    <div onClick=(self.handle(handleClick))>
      <span> (ReasonReact.stringToElement(quote##symbol)) </span>
      <span> (ReasonReact.stringToElement(quote##ask_price)) </span>
    </div>
};