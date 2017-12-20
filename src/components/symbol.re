let component = ReasonReact.statelessComponent("Symbol");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~label, _children) => {
  ...component,
  render: (self) =>
    <div onClick=(self.handle(handleClick))> (ReasonReact.stringToElement(label)) </div>
};