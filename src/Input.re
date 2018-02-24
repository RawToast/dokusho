open Store;

module Input = {
    type state = string;
    let str = ReasonReact.stringToElement;
    let component = ReasonReact.reducerComponent("Input");

    let pageScore = (pt: Store.pageType) => { 
        switch pt {
        | Manga => 0.2
        | News => 1.0
        | Book => 1.0
        | Lyric => 0.8
        | Net => 1.0
        };
    };
    type content = { name: string, pageType: Store.pageType};

    let valueFromEvent = (evt) : string => ( evt
        |> ReactEventRe.Form.target
        |> ReactDOMRe.domElementToObj
        )##value;
  
    let make = (~onSubmit, _) => {
      ...component,
      initialState: () => "",
      reducer: (newText, _text) => ReasonReact.Update(newText),
      render: ({state: text, reduce}) =>{
          let pageTypes = [
            {name: "Book", pageType: Book}, 
            {name: "News", pageType: News}, 
            {name: "Manga", pageType: Manga}, 
            {name: "Net", pageType: Net}, 
            {name: "Lyric", pageType: Lyric}];

          <div>
            <input
            value=text
            _type="text"
            placeholder="Pages"
            onChange=(reduce((evt) => valueFromEvent(evt)))
            onKeyDown=((evt) =>
                if (ReactEventRe.Keyboard.key(evt) == "Enter") {
                onSubmit(text);
                (reduce(() => ""))()
                }
            )
            />
            <select>
                (List.map((pt) => 
                    <option key=pt.name value=pt.name>(str(pt.name))</option>, pageTypes)
                    |> Array.of_list
                    |> ReasonReact.arrayToElement)
            </select>
        </div>
        }
    };
  };
  