open Input;
open Types;
open Day;
open Actions;
open DokuUtil;
open Rationale;

module Dokusho {
  let component = ReasonReact.reducerComponent("Dokusho");
  let initState = () => {
    readingData: { days : [ Day.now() ] },
    selectedEntry: Book,
    selectedDate: Js.Date.make()
  };
  
  let make = (~token, _children) => {
    ...component,
    initialState: () => initState(),
    reducer: (action, { readingData, selectedEntry, selectedDate }) => 
      switch action {
        | ChangeSelection(pageType) => 
            ReasonReact.Update({readingData: readingData, selectedEntry: pageType, selectedDate: selectedDate});
        | AddEntry(pageType, count) =>  
            Actions.addNewEntry(token, pageType, count);
        | UpdateHistory(days) => 
            ReasonReact.Update({readingData: {days: days}, selectedEntry: selectedEntry, selectedDate: selectedDate}); 
        | LoadUserData(userId) => 
            Actions.loadUserData(userId);
        | SelectDate(date) => 
            ReasonReact.Update({readingData: readingData, selectedEntry: selectedEntry, selectedDate: date});
          },
    didMount: (self) => {
      self.send(LoadUserData(token));
    },
    render: (self) => {
      let dateKey = self.state.selectedDate |> DateUtil.dateWithoutTime |> DateUtil.asDateKey;
      
      let day = RList.find(d => d.date == dateKey, self.state.readingData.days);
      let pageCount = day |> Option.fmap(Day.pageCount) |> Option.default(0.);
      let entries = day |> Option.fmap(d => d.entries) |> Option.default([]);

      let availableDates = DateUtil.availableDates(self.state.readingData);

          <div>
            <div className="title"> 
              (ReasonReact.string("Dokusho"))
            </div> 
            <div className="dokusho">
              <Input 
                selection=self.state.selectedEntry
                onSubmit=(text => self.send(AddEntry(self.state.selectedEntry, int_of_string(text))))
                />

              <PageTypeSelection onChangeSelect=(selected => self.send(ChangeSelection(selected))) />
            
              <DateSelector 
                onChangeSelect=(date => {
                  let action = SelectDate(date);
                  self.send(action)}
                )
                enabledDates=(availableDates) />  

              <Entries entries=(entries) />
           </div>
            <Footer pageCount=(pageCount) />
          </div>
    }
  };  
}
