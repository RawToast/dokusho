open DokuUtil;
open Types;

module Input = {
    type inputState = { 
      text: string, 
      selection: pageType
    };
    let str = ReasonReact.string;
    let numbers = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'];
    let component = ReasonReact.reducerComponent("Input");

    let make = (~selection, ~onSubmit, _) => {
      ...component,
      initialState: () => { text: "", selection: selection},
      reducer: (state: inputState, _ext) => {
        let filtered = DokuUtil.string_map_partial(
            (c: char) =>
              if (Rationale.RList.contains(c, numbers)) Some(c) else None,
            state.text
          );
        ReasonReact.Update({ text: filtered, selection: state.selection })
    },
      render: self => {
        <ReactToolbox.Input
              className="textinput"
              value=self.state.text
              _type="text"
              hint=str("Pages")
              onChange=((txt, _mse) => {
                self.send({text: txt, selection: self.state.selection})
              })
              onKeyDown=((evt) =>
                if (ReactEventRe.Keyboard.key(evt) == "Enter") {
                  onSubmit(self.state.text);
                  self.send({text: "", selection: self.state.selection })
                }
              )
            />
         }
    };
  };
