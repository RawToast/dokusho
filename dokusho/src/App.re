[%bs.raw {|require('./toolbox/theme.css')|}];
[%bs.raw {|require('../node_modules/auth0-js/build/auth0.js')|}];
[%bs.raw {|require('./toolbox/theme.css')|}];

open Dokusho;

[@bs.module]
external theme : ReactToolbox.ThemeProvider.theme = "./toolbox/theme";

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