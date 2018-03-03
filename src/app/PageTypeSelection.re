open PageType;
open Types;
open DokuUtil;

module PageTypeSelection = {
    type inputState = { 
      selection: pageType
    };

    let str = ReasonReact.stringToElement;
    let component = ReasonReact.statelessComponent("PageTypeSelection");

    let make = (~onChangeSelect, _) => {
      ...component,
      render: (_) => {
            <select
                onChange=((evt) => {
                    switch ( evt |> DokuUtil.valueFromEvent 
                        |> PageType.findOptType ) {
                            | Some(pt) => 
                              onChangeSelect(pt);
                              | None => ()
                          }
                  })>
                ((PageType.pageTypes |>
                List.map((pt: content) => 
                    <option key=pt.name value=pt.name>(str(pt.name))</option>)
                    |> Array.of_list
                    |> ReasonReact.arrayToElement))
            </select>
        }
    };
  };
