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
      Js.Console.log("Storing auth: " ++ accessToken);
      let expiry = Js.Date.now() +. (float_of_string(expiresIn) *. 1000.);
      sessionStorage |> setItem("accessToken", accessToken);
      sessionStorage |> setItem("id_token", idToken);
      sessionStorage |> setItem("expiresIn", string_of_float(expiry));
  
      accessToken;
    };
  
    let getIdToken = () => sessionStorage |> getItem("id_token") |> resolveOption;
  
    let getAccessToken = () => (sessionStorage |> getItem("accessToken") |> resolveOption);
    let tokenStillValid = () => (sessionStorage 
          |> getItem("expiresIn") 
          |> Rationale.Option.fmap(e => float_of_string(e))
          |> Rationale.Option.fmap(e => e > Js.Date.now())
          |> Rationale.Option.default(false));
  };