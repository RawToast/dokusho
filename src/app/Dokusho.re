open Input;
open Entry;
open Types;
open ReadingData;

module Dokusho {
  let component = ReasonReact.reducerComponent("Dokusho");
  let initState = {
    readingData: ReadingData.empty,
    selectedEntry: Book
  };
  
  let make = (_children) => {
    ...component,
    initialState: () => initState,
    reducer: (action, { readingData, selectedEntry }) => 
      switch action {
        | ChangeSelection(pageType) => 
            ReasonReact.Update({readingData: readingData, selectedEntry: pageType}); 
        | AddEntry(pageTypeString, count) => 
            ReasonReact.Update(
                ReadingData.createEntry(List.length(readingData.entries), pageTypeString, count) |>
                ReadingData.appendEntry(readingData) |>
                (rd => {readingData: rd, selectedEntry: selectedEntry}));
      },
    render: ({state: { readingData, selectedEntry }, reduce}) => {
      let pageCount = ReadingData.pageCount(readingData);
  
      <div className="app">
        <div className="title"> 
          (ReasonReact.stringToElement("Dokusho"))
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
          (ReasonReact.stringToElement(string_of_float(pageCount) ++ " pages"))
        </div>
      </div>
    }
  };
  
}
