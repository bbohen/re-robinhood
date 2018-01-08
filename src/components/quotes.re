open Types;

let component = ReasonReact.statelessComponent("Quotes");

let make = (~quotes, _children) => {
  ...component,
  render: (_self) => {
    let index = 0;
    let quoteItems =
      Array.map(
        (quote) => {
          Js.log(quotes);
          let key = quote##symbol ++ "index";
          index + 1;
          <Quote key quote />
        },
        quotes
      );
    <div className="quotes-container"> (ReasonReact.arrayToElement(quoteItems)) </div>
  }
};