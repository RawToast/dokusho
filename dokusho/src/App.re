[%bs.raw {|require('./toolbox/theme.css')|}];
[%bs.raw {|require('../node_modules/auth0-js/build/auth0.js')|}];

[@bs.module]
external theme : ReactToolbox.ThemeProvider.theme = "./toolbox/theme";

open Dokusho;
open Types;

type action =
  | ChangeRoute(Routes.route);

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update( route )
  };

let component = ReasonReact.reducerComponent("App");

let mapUrlToRoute = (url: ReasonReact.Router.url) => {
  switch url.path {
    | [] =>  {
      Routes.Home;
    }
    | ["callback"] => {
      LoginButton.Auth.handleAuth(url);
    }
    | _ => {
      Routes.Home;
    }  /* Routes.NotFound */
  }
};

let make = _children => {
  ...component,
  reducer,
  initialState: () => { Routes.Home },
  subscriptions: (self) => [
    Sub(
      () => ReasonReact.Router.watchUrl((url) => self.send(ChangeRoute(url |> mapUrlToRoute))),
        ReasonReact.Router.unwatchUrl
    )
  ],
  render: self =>
    <ReactToolbox.ThemeProvider theme>
      <div className="app">
        (switch self.state {
        | Routes.Home => <Dokusho/>
        })
      </div>
    </ReactToolbox.ThemeProvider>
};
