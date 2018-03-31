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
};

let authOptions = {
    "domain": "dokusho.eu.auth0.com",
    "clientID": "mal13rQ1KYJSpAjTBvs72ioa8xhnq8wh",
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
