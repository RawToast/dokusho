open Types;
open PageType;

module Entry = {
  let component = ReasonReact.statelessComponent("Entry");
  
  let make = (~store: entry, _children) => {
    ...component,
    render: (_) =>
      <div className="entry">
          (store.kind |> 
          PageType.toString |> 
          (str) => str ++ ": " ++ string_of_int(store.value) |>
          ReasonReact.stringToElement)
      </div>
  };
};