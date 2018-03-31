open PageType;

open Types;

let component = ReasonReact.reducerComponent("PageTypeSelection");

let make = (~onChangeSelect, _) => {
  ...component,
  initialState: () => "Book",
  reducer: (state, _ext) => ReasonReact.Update(state),
  render: ({state, reduce}) =>
    <ReactToolbox.Dropdown
      className="pageselect"
      auto=true
      source=(
        PageType.pageTypes
        |> List.map(i => {"value": i.name, "label": i.name})
        |> Array.of_list
      )
      value=(`String(state))
      onChange=(
        (txt, _mse) =>
          switch (txt |> PageType.findOptType) {
          | Some(pt) =>
            (reduce(() => PageType.toString(pt)))();
            onChangeSelect(pt);
          | None => ()
          }
      )
    />
};