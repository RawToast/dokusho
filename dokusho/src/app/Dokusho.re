open Input;
open Entry;
open Types;
open Day;
open PageTypeSelection;
open Client;

module Dokusho {
  let component = ReasonReact.reducerComponent("Dokusho");
  let initState = () => {
    readingData: { days : [Day.now()] },
    selectedEntry: Book
  };
  
  let make = (_children) => {
    ...component,
    initialState: () => initState(),
    reducer: (action, { readingData, selectedEntry }) => 
      switch action {
        | ChangeSelection(pageType) => 
            ReasonReact.Update({readingData: readingData, selectedEntry: pageType}); 
        | AddEntry(pageType, count) =>  
            ReasonReact.SideEffects(
              ( self =>
                Js.Promise.(
                  Client.newEntry(Types.testUser, pageType, count)
                  |> then_((serverResponse: Client.serverResponse) => {
                    self.send(UpdateHistory(serverResponse.readingHistory.days));
                    resolve(serverResponse);
                  })) 
                  |> ignore
              )
            );
        | UpdateHistory(days) => 
            ReasonReact.Update({readingData: {days: days}, selectedEntry: selectedEntry}); 
        | LoadUserData(userId) => 
            ReasonReact.SideEffects(
              (self =>
                Js.Promise.(
                  Client.userHistory(userId)
                    |> then_((serverResponse: Client.serverResponse) => {
                      self.send(UpdateHistory(serverResponse.readingHistory.days));
                      resolve(serverResponse);
                    }))
                |> ignore
              )
            );
          },
    didMount: (_self) => {
      ReasonReact.SideEffects(
              (self =>
                Js.Promise.(
                  Client.userHistory(Types.testUser)
                    |> then_((serverResponse: Client.serverResponse) => {
                      self.send(UpdateHistory(serverResponse.readingHistory.days));
                      resolve(serverResponse);
                    }))
                |> ignore
              )
            );
    },
    render: (self) => {
      let pageCount = Day.pageCount(List.hd(self.state.readingData.days));      
      
      <div className="app">
        <div className="title"> 
          (ReasonReact.stringToElement("Dokusho"))
          <Input 
            selection=self.state.selectedEntry
            onSubmit=(self.reduce((text) => AddEntry(self.state.selectedEntry, int_of_string(text))))
            />
          <PageTypeSelection onChangeSelect=(self.reduce(selected => ChangeSelection(selected))) />
        </div>
        <div className="entries">
          (List.hd(self.state.readingData.days).entries
              |> List.map((entry: entry) => <Entry key=(string_of_int(entry.id)) entry=entry />) 
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
