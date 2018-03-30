open Input;
open Types;
open Day;
open PageTypeSelection;
open Actions;
open Entries;
open Footer;

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
            Actions.addNewEntry(pageType, count);
        | UpdateHistory(days) => 
            ReasonReact.Update({readingData: {days: days}, selectedEntry: selectedEntry}); 
        | LoadUserData(userId) => 
            Actions.loadUserData(userId);
          },
    didMount: (_self) => {
      Actions.loadUserData(testUser);
    },
    render: (self) => {
      let pageCount = Day.pageCount(List.hd(self.state.readingData.days));      
          <div>
            <div className="title"> 
              (ReasonReact.stringToElement("Dokusho"))
              <Input 
                selection=self.state.selectedEntry
                onSubmit=(self.reduce((text) => AddEntry(self.state.selectedEntry, int_of_string(text))))
                />
              <PageTypeSelection onChangeSelect=(self.reduce(selected => ChangeSelection(selected))) />
            </div>

            <Entries entries=(List.hd(self.state.readingData.days).entries) />
            
            <Footer pageCount=(pageCount) />
          </div>
    }
  };  
}
