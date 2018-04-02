open Types;

let combineEntries = (pt, entries) =>
  if (Rationale.RList.any((a => a.kind == pt), entries)) {
    entries 
      |> List.filter(e => e.kind == pt)
      |> List.fold_left((a, b) => {id: a.id, kind: pt, value: a.value + b.value}, {id: 0, kind: pt, value: 0})
      |> (entry: entry) => (<Entry key=(string_of_int(entry.id)) entry />)
  } else ReasonReact.nullElement;

let component = ReasonReact.statelessComponent("Entry");

let make = (~entries: list(entry), _children) => {
  ...component,
  render: (_) =>
    <div className="entries">
      (if (Rationale.RList.any((a => a.kind == Book), entries)) combineEntries(Book, entries) else ReasonReact.nullElement)
      (combineEntries(Lyric, entries))
      (combineEntries(Manga, entries))
      (combineEntries(Net, entries))
      (combineEntries(News, entries))
    </div>
};

