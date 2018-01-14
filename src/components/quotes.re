let component = ReasonReact.statelessComponent("Quotes");

let make = (~quotes, ~removeQuote, _children) => {
  ...component,
  render: (_self) => {
    let index = 0;
    let quoteItems =
      Array.map(
        (quote) => {
          let key = quote##symbol ++ "-" ++ string_of_int(index);
          let onRemoveClick = (_event) => removeQuote(quote##symbol);
          index + 1 |> ignore;
          <Quote key quote onRemoveClick />
        },
        quotes
      );
    <div className="quotes-container"> (ReasonReact.arrayToElement(quoteItems)) </div>
  }
};