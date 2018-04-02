open Auth;

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
        <div>
          <ReactToolbox.Button
            label="login"
            onClick=(onLogin)
            className="loginbutton"
          />
        </div>
  }
};
