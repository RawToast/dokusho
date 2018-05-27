let component = ReasonReact.reducerComponent("DateSelector");

let make = (~onChangeSelect, ~enabledDates, _children) => {
  ...component,
  initialState: () => Js.Date.make(),
  reducer: (state, _ext) => ReasonReact.Update(state),
  render: self => {
        <div> 
            <ReactToolbox.DatePicker 
                label="Date" 
                value=(`Date(self.state))
                enabledDates=(enabledDates)
                onChange=((date, _mouse) =>
                    {   
                        onChangeSelect(date);
                        self.send(date);
                    })/> 
        </div>
  }
};
