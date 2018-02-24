open Util;
open PageType;

module Input = {
    type state = string;
    let str = ReasonReact.stringToElement;
    let component = ReasonReact.reducerComponent("Input");

    let make = (~onSubmit,  _) => {
      ...component,
      initialState: () => "",
      reducer: (newText: string, _text) => {
        let filtered = Util.string_map_partial(
            (c) =>
              if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || 
                    c == '6' || c == '7' || c == '8' || c == '9' || c == '0') {
                Some(c)
              } else {
                None
              },
            newText
          );
        ReasonReact.Update(filtered)
    },
      render: ({state: text, reduce}) => {
          <div>
            <input
            value=text
            _type="text"
            pattern="[0-9]*"
            placeholder="Pages"
            onChange=(reduce((evt) => Util.valueFromEvent(evt)))
            onKeyDown=((evt) =>
                if (ReactEventRe.Keyboard.key(evt) == "Enter") {
                onSubmit(text);
                (reduce(() => ""))()
                }
            )
            />
            <select onChange=(reduce((evt) => {
                let v:string = ((evt |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj)##target);
                v;
                }))>
                (List.map((pt: PageType.content) => 
                    <option key=pt.name value=pt.name>(str(pt.name))</option>, PageType.pageTypes)
                    |> Array.of_list
                    |> ReasonReact.arrayToElement)
            </select>
        </div>
        }
    };
  };
