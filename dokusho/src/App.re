[%bs.raw {|require('./toolbox/theme.css')|}];

open Dokusho;

[@bs.module]
external theme : ReactToolbox.ThemeProvider.theme = "./toolbox/theme";
[%bs.raw {|require('./toolbox/theme.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <ReactToolbox.ThemeProvider theme>
      <div className="app">
        <Dokusho/>
      </div>
    </ReactToolbox.ThemeProvider>
};