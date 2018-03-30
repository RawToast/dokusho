let component = ReasonReact.statelessComponent("DateSelector");

let make = (~today: string, _children) => {
  ...component,
  render: (_) =>
    <div className="dateselector"> <ReactToolbox.DatePicker 
        label="Today"
        /> 
    </div>
};