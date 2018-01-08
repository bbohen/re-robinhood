open Json;

let namespace = "reason-react-robinhood";

let parseJson = (stringifiedJson) => Json.parseOrRaise(stringifiedJson) |> Decode.(array(string));

let saveLocally = (symbols) =>
  switch (Js.Json.stringifyAny(symbols)) {
  | None => ()
  | Some(stringifiedSymbols) =>
    Dom.Storage.(localStorage |> setItem(namespace, stringifiedSymbols))
  };