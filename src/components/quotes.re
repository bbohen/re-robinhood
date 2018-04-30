let component = ReasonReact.statelessComponent("Quotes");

let make = (~quotes, ~loadHistoricalData, ~removeQuote, _children) => {
  ...component,
  render: (_self) => {
    let index = ref(0);
    let quoteItems =
      Array.map(
        (quote) => {
          let key = quote##symbol ++ "-" ++ string_of_int(index^);
          let onRemoveClick = (_event) => removeQuote(quote##symbol);
          let graphPayload = {"symbol": quote##symbol, "index": index^};
          let loadGraphData = () => loadHistoricalData(graphPayload);
          index := index^ + 1;
          <Quote key quote loadGraphData onRemoveClick />
        },
        quotes
      );
    <div className="quotes-container"> (ReasonReact.array(quoteItems)) </div>
  }
};