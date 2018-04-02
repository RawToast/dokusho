module Auth {
  type generatedAuth0Client = {.
    "authorize": [@bs.meth] (unit => unit)
  };

  type clientOptions = {
      .
      "domain": string,
      "clientID": string,
      "redirectUri": string,
      "responseType": string,
      "scope": string
    };

  [@bs.module "auth0-js"] [@bs.new]  external createClient : (clientOptions => generatedAuth0Client) = "WebAuth";  
  
  let matchAccessToken = [%re "/access_token=([^\$&]+)/g"];
  let matchExpiresIn = [%re "/expires_in=([^\$&]+)/g"];
  let matchIdToken = [%re "/id_token=([^\$&]+)/g"];

  let resolveOption = (opt) => switch opt {
  | None => ""
  | Some(s) => s
  };

  let resolveRegex = (exp, str) => {
    let res = exp |> Js.Re.exec(str);
    switch res {
    | None => ""
    | Some(result) => {
        let captures = result |> Js.Re.captures;
        switch captures {
        | [|_, token|] => token |> Js.Nullable.to_opt |> resolveOption 
        | _ => ""
        };
      }
    };
  };

  open Dom.Storage;

  let handleAuth = (url: ReasonReact.Router.url) => {

    let accessToken = url.hash |> resolveRegex(matchAccessToken);
    let idToken = url.hash |> resolveRegex(matchIdToken);
    let expiresIn = url.hash |> resolveRegex(matchExpiresIn);
    localStorage |> setItem("accessToken", accessToken);
    localStorage |> setItem("id_token", idToken);
    localStorage |> setItem("expiresIn", expiresIn);
  };

  let getIdToken = () => localStorage |> getItem("id_token") |> resolveOption;

};

let authOptions = {
    "domain": "dokusho.eu.auth0.com",
    "clientID": "mal13rQ1KYJSpAjTBvs72ioa8xhnq8wh",
    /* "redirectUri": "http://35.189.106.56:3000/callback", */
    "redirectUri": "http://localhost:3000/callback",
    "responseType": "token id_token",
    "scope": "openid"
};

let authClient = Auth.createClient(authOptions);

let component = ReasonReact.statelessComponent("LoginButton");

let make = (_) => {
  ...component,
  render: (_) => {
        let onLogin = (_event => authClient##authorize());
        <ReactToolbox.Button
            label="Hey"
            onClick=(onLogin)
        />
  }
};
