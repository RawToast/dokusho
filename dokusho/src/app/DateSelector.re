let component = ReasonReact.reducerComponent("DateSelector");

let make = (~onChangeSelect, ~enabledDates, _children) => {
  ...component,
  initialState: () => Js.Date.make(),
  reducer: (state, _ext) => 
    ReasonReact.Update({ state }),
  render: (
      {state, reduce}) =>
        <div> 
            <ReactToolbox.DatePicker 
                label="Date" 
                value=(`Date(state))
                enabledDates=(enabledDates)
                onChange=((date, _mouse) =>
                    {   
                        onChangeSelect(date);
                        (reduce(() => { date }))();
                    }
                )/> 
        </div>
};