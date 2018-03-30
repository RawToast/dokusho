let component = ReasonReact.reducerComponent("DateSelector");

let getDate = Js.Date.make;

let make = (~onChangeSelect, _children) => {
  ...component,
  initialState: () => getDate(),
  reducer: (state, _ext) => 
    ReasonReact.Update({ state }),
  render: (
      {state, reduce}) =>
        <div> 
            <ReactToolbox.DatePicker 
                label="Date" 
                value=(`Date(state))
                onChange=((date, _mouse) =>
                    {   
                        onChangeSelect(date);
                        (reduce(() => { date }))();
                    }
                )/> 
        </div>
};