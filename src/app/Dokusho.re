open Input;
open Entry;
open PageType;
open Types;

type action = 
  | AddEntry(pageType, int)
  | ChangeSelection(pageType);
let str = ReasonReact.stringToElement;

type mainState = {
  readingData: readingData,

  selectedEntry: pageType
};
let component = ReasonReact.reducerComponent("Dokusho");
let initState: mainState = {
  readingData: { entries: [] },

  selectedEntry: Book
};

let newItem: (int, pageType, int) => entry = 
  (nextId, pt, pageCount) => {
    id: nextId,
    kind: pt,
    value: pageCount
};

let addEntry: (readingData, entry) => readingData = 
  (rd, entry) => {
    let x: readingData = { entries: [entry, ...rd.entries] };
    x;
  };

let make = (_children) => {
  ...component,
  initialState: () => initState,
  reducer: (action, { readingData, selectedEntry }) => 
    switch action {
      | ChangeSelection(pt) => ReasonReact.Update({readingData: readingData, selectedEntry: pt}); 
      | AddEntry(text, int) => 
        ReasonReact.Update(
            newItem(1, text, int) |>
            addEntry(readingData) |>
            (rd => {readingData: rd, selectedEntry: selectedEntry}));
    },
  render: ({state: { readingData, selectedEntry }, reduce}) => {
    let pageCount = readingData.entries 
      |> List.map(i => float_of_int(i.value) *. PageType.pageScore(i.kind))
      |> List.fold_left((a, b) => a +. b, 0.);

    <div className="app">
      <div className="title"> 
        (str("Dokusho"))
        <Input 
          selection=selectedEntry
          onSubmit=(reduce((text) => AddEntry(selectedEntry, int_of_string(text))))
          onChangeSelection=(reduce(selected => ChangeSelection(selected)))
          />
      </div>
      <div className="entries">
        (readingData.entries 
            |> List.map((entry: entry) => <Entry key=(string_of_int(entry.id)) store=entry />) 
            |> Array.of_list
            |> ReasonReact.arrayToElement)
      </div>
      <div className="footer">
        (str(string_of_float(pageCount) ++ " pages"))
      </div>
    </div>
  }
};
