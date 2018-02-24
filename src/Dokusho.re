open Input;

  type item = {
    id: int,
    title: string,
    completed: bool
  };
  
  type state = {
    items: list(item)
  };
  
  type action = 
    | AddItem(string)
    | ToggleItem(int);

let str = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  
  let make = (~item: item, ~onToggle, _children) => {
    ...component,
    render: (_) =>
      <div className="item" onClick=((_evt) => onToggle())>
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
          />
          (str(item.title))
      </div>
  };
};

let component = ReasonReact.reducerComponent("Dokusho");
let initState: state = {
  items: [
    { id: 0, title: "Write some things to do", completed: false }
  ]
};

let newItem = (nextId, text) => {
  id: nextId,
  title: text, 
  completed: true
};

let make = (_children) => {
  ...component,
  initialState: () => initState,
  reducer: (action, {items}) => 
    switch action {
      | AddItem(text) => ReasonReact.Update({items: [newItem(List.length(items),text), ...items]})
      | ToggleItem(id) =>
        let items = List.map(item => 
          item.id === id ? {...item, completed: !item.completed} : item,
          items);
        ReasonReact.Update({items: items})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);

    <div className="app">
      <div className="title"> 
        (str("Dokusho"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (List.map((item) => 
          <TodoItem 
            key=(string_of_int(item.id)) 
            onToggle=(reduce(() => ToggleItem(item.id))) item 
          />, items)
            |> Array.of_list
            |> ReasonReact.arrayToElement)
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
