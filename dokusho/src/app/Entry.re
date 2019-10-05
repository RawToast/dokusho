open Types;

open PageType;

let component = ReasonReact.statelessComponent("Entry");

let make = (~entry: entry, _children) => {
  ...component,
  render: (_) =>
    <div className="entry">
      (
        entry.kind
        |> PageType.toString
        |> ((str) => str ++ ": " ++ string_of_int(entry.value) 
          |> ReasonReact.string)
      )
    </div>
};