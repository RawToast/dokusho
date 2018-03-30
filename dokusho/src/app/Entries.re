open Types;
open Entry;

module Entries = {

  let component = ReasonReact.statelessComponent("Entry");
    
  let make = (~entries: list(entry), _children) => {
    ...component,
    render: (_) =>
      <div className="entries">
          (entries
              |> List.map((entry: entry) => <Entry key=(string_of_int(entry.id)) entry=entry />) 
              |> Array.of_list
              |> ReasonReact.arrayToElement)
      </div>
  };
};