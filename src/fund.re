let component = ReasonReact.statelessComponent("Page");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~description, _children) => {
  ...component,
  render: (self) =>
    <div onClick=(self.handle(handleClick))> (ReasonReact.stringToElement(description)) </div>
};