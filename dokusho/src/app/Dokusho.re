open Input;
open Types;
open Day;
open PageTypeSelection;
open Actions;
open Entries;
open Footer;
open Rationale;

module Dokusho {
  let component = ReasonReact.reducerComponent("Dokusho");
  let initState = () => {
    readingData: { days : [Day.now()] },
    selectedEntry: Book,
    selectedDate: Js.Date.make()
  };
  
  let make = (_children) => {
    ...component,
    initialState: () => initState(),
    reducer: (action, { readingData, selectedEntry, selectedDate }) => 
      switch action {
        | ChangeSelection(pageType) => 
            ReasonReact.Update({readingData: readingData, selectedEntry: pageType, selectedDate: selectedDate});
        | AddEntry(pageType, count) =>  
            Actions.addNewEntry(pageType, count);
        | UpdateHistory(days) => 
            ReasonReact.Update({readingData: {days: days}, selectedEntry: selectedEntry, selectedDate: selectedDate}); 
        | LoadUserData(userId) => 
            Actions.loadUserData(userId);
        | SelectDate(date) => 
            ReasonReact.Update({readingData: readingData, selectedEntry: selectedEntry, selectedDate: date});
          },
    didMount: (_self) => {
      Actions.loadUserData(testUser);
    },
    render: (self) => {
      let calendarDate = Js.Date.fromFloat(Js.Date.utcWithYMDHMS(
        ~year=Js.Date.getFullYear(self.state.selectedDate),
        ~month=Js.Date.getMonth(self.state.selectedDate), 
        ~date=Js.Date.getDate(self.state.selectedDate),
        ~hours=0.,
        ~minutes=0.,
        ~seconds=0.)());

      let dateKey = Js.String.slice(0, 16, Js.Date.toISOString(calendarDate));

      let day = RList.find(d => d.date == dateKey, self.state.readingData.days);
      let pageCount = day |> Option.fmap(Day.pageCount) |> Option.default(0.);
      let ents = day |> Option.fmap(d => d.entries) |> Option.default([]);

      let dats = self.state.readingData.days |> List.map(d => Js.Date.fromString(d.date)) |> (ls) => [Js.Date.make(), ...ls] |> Array.of_list;

          <div>
            <div className="title"> 
              (ReasonReact.stringToElement("Dokusho"))
            </div> 
            <div className="dokusho">
              <Input 
                selection=self.state.selectedEntry
                onSubmit=(self.reduce((text) => AddEntry(self.state.selectedEntry, int_of_string(text))))
                />
              <PageTypeSelection onChangeSelect=(self.reduce(selected => ChangeSelection(selected))) />
            
              <DateSelector onChangeSelect=(self.reduce(dt => SelectDate(dt))) enabledDates=(dats) />  

              <Entries entries=(ents) />
            
              <Footer pageCount=(pageCount) />
            </div>
          </div>
    }
  };  
}
