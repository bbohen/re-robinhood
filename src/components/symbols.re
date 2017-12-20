let component = ReasonReact.statelessComponent("Symbols");

let make = (~symbols, _children) => {
  ...component,
  render: (_self) => {
    let symbols = Array.map((symbol) => <Symbol label=symbol />, symbols);
    <div>
      <p> (ReasonReact.stringToElement("Entered Symbols:")) </p>
      (ReasonReact.arrayToElement(symbols))
    </div>
  }
};