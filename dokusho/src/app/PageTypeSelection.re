open PageType;

open Types;

module PageTypeSelection = {

  type inputS = {text: string};

  let str = ReasonReact.stringToElement;
  let ptArray = PageType.pageTypes |> List.map(i => {"value": i.name, "label": i.name});

  let component = ReasonReact.reducerComponent("PageTypeSelection");

  let make = (~onChangeSelect, _) => {
    ...component,
    initialState: () => {text: "Book"},
    reducer: (state: inputS, _ext) => ReasonReact.Update({text: state.text}),
    render: ({state, reduce}) =>
        <ReactToolbox.Dropdown
          className="pageselect"
          auto=true
          source=(Array.of_list(ptArray))
          value=(`String(state.text))
          onChange=(
            (txt, _mse) =>
              switch (txt |> PageType.findOptType) {
              | Some(pt) =>
                (reduce(() => {text: PageType.toString(pt)}))();
                onChangeSelect(pt);
              | None => ()
              }
          )
        />
  };
};