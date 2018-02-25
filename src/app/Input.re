open Util;
open PageType;
open Types;

module Input = {
    type inputState = { 
      text: string, 
      selection: pageType
    };
    let str = ReasonReact.stringToElement;
    let component = ReasonReact.reducerComponent("Input");

    let make = (~selection, ~onSubmit, ~onChangeSelection, _) => {
      ...component,
      initialState: () => { text: "", selection: selection},
      reducer: (state: inputState, _text) => {
        let filtered = Util.string_map_partial(
            (c: char) =>
              if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || 
                    c == '6' || c == '7' || c == '8' || c == '9' || c == '0') {
                Some(c)
              } else {
                None
              },
            state.text
          );
        ReasonReact.Update({ text: filtered, selection: state.selection })
    },
      render: ({state: state, reduce}) => {
          <div>
            <input
            value=state.text
            _type="text"
            pattern="[0-9]*"
            placeholder="Pages"
            onChange=((evt) => {
              let txt = Util.valueFromEvent(evt);
              reduce(() => {text: txt, selection: state.selection})()
            })
            onKeyDown=((evt) =>
                if (ReactEventRe.Keyboard.key(evt) == "Enter") {
                onSubmit(state.text);
                (reduce(() => {text: "", selection: state.selection }))()
                }
            )
            />
            <select
            onChange=((evt) => {
              let txt = Util.valueFromEvent(evt);

              switch (PageType.findOptType(txt)) {
                | Some(pt) => 
                  onChangeSelection(pt);
                  reduce(() => {text: txt, selection: pt})()
                | None => ()
              }
            })
            >
                (List.map((pt: content) => 
                    <option key=pt.name value=pt.name>(str(pt.name))</option>, PageType.pageTypes)
                    |> Array.of_list
                    |> ReasonReact.arrayToElement)
            </select>
        </div>
        }
    };
  };
