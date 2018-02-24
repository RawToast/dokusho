open Util;
open PageType;

module Input = {
    type state = string;
    let str = ReasonReact.stringToElement;
    let component = ReasonReact.reducerComponent("Input");
    let make = (~onSubmit, ~onChange, _) => {
      ...component,
      initialState: () => "",
      reducer: (newText, _text) => ReasonReact.Update(newText),
      render: ({state: text, reduce}) =>{
          <div>
            <input
            value=text
            _type="text"
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
