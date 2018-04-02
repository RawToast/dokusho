[%bs.raw {|require('./toolbox/theme.css')|}];
[%bs.raw {|require('../node_modules/auth0-js/build/auth0.js')|}];

[@bs.module]
external theme : ReactToolbox.ThemeProvider.theme = "./toolbox/theme";

open Dokusho;
open Types;
open Auth;

type action =
  | ChangeRoute(Routes.route);

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update( route )
  };

let component = ReasonReact.reducerComponent("App");

let mapUrlToRoute = (url: ReasonReact.Router.url) => {
  switch url.path {
    | ["callback"] => {
      let token = Auth.handleAuth(url);
      ReasonReact.Router.push("/");
      Routes.Home(token);
    }
    | [] =>  {
      Js.Console.log("Home");
      let token = Auth.getAccessToken();
      if(token == "" && !Auth.tokenStillValid()) Routes.NoAuth else Routes.Home(token);
    }
    | _ => {
      Routes.NoAuth;
    }  /* Routes.NotFound */
  }
};

let make = _children => {
  ...component,
  reducer,
  initialState: () => { Routes.NoAuth },
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
        | Routes.Home(token) => <Dokusho token=token/>
        | Routes.NoAuth => <Login />
      })
      </div>
    </ReactToolbox.ThemeProvider>
};
