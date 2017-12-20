open Types;

let component = ReasonReact.statelessComponent("Funds");

let make = (~quotes, _children) => {
  ...component,
  render: (_self) => {
    let quoteItems = Array.map((quote: quote) => <Quote quote />, quotes);
    <div className="quotes-container"> (ReasonReact.arrayToElement(quoteItems)) </div>
  }
};