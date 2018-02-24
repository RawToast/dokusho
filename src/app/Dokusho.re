open Input;
open Store;
open Entry;

type action = 
  | AddEntry(string, int);

type readingData = {
  entries: list(Store.entry)
};

let str = ReasonReact.stringToElement;
let component = ReasonReact.reducerComponent("Dokusho");
let initState: readingData = {
  entries: []
};

let newItem: (int, Store.pageType, int) => Store.entry = 
  (nextId, pt, pageCount) => {
    id: nextId,
    kind: pt,
    value: pageCount
};
let addEntry: (readingData, Store.entry) => readingData = 
  (rd, entry) => {
    let x: readingData = { entries: [entry, ...rd.entries] };
    x;
  };

let make = (_children) => {
  ...component,
  initialState: () => initState,
  reducer: (action, { entries }) => 
    switch action {
      | AddEntry(_text, int) => 
        ReasonReact.Update({ entries: addEntry({entries: entries}, newItem(9, Book, int)).entries })
    },
  render: ({state: { entries }, reduce}) => {
    let pageCount = entries 
      |> List.map((i: Store.entry) => i.value) 
      |> List.fold_left((a, b) => a + b, 0);

    <div className="app">
      <div className="title"> 
        (str("Dokusho"))
        <Input 
          onSubmit=(reduce((text) => AddEntry(text, int_of_string(text))))
          />
      </div>
      <div className="entries">
        (List.map((entry: Store.entry) => 
          <Entry 
            key=(string_of_int(entry.id)) 
            store=entry 
          />, entries)
            |> Array.of_list
            |> ReasonReact.arrayToElement)
      </div>
      <div className="footer">
        (str(string_of_int(pageCount) ++ " pages"))
      </div>
    </div>
  }
};
