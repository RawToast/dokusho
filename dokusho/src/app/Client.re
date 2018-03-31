[%raw "require('isomorphic-fetch')"];

open Types;

type serverResponse = {
  userId: string,
  readingHistory: readingHistory
};

module Client = {
  open Dom.Storage;

  let accessToken = () => localStorage |> getItem("accessToken") |> Rationale.Option.default("no_token");

  let backendURI = "http://35.189.70.144:8080";
  let jsonHeader = Fetch.HeadersInit.make({"Content-Type": "application/json"});
  let authHeader = () => Fetch.HeadersInit.makeWithArray([|( "Content-Type", "application/json" ), ( "accessToken", accessToken() )|]);

  let parseResponse = (json: Js.Json.t) => {
    Json.Decode.{
      userId: json |> field("userId", string),
      readingHistory: json |> field("readingHistory", Decoders.parseHistory)
    };
  };
  /* Fetches the given user's reading history */
  let userHistory = (userId:string) => {
    Js.Console.log("Get history " ++ accessToken());
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/" ++ userId,
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=authHeader(),
          ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };

  /* Adds a new reading entry for today to a user's reading history */
  let newEntry = (userId:string, kind: pageType, value: int) => {
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/" ++ userId ++ "/add",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Encoders.endcodeInput(kind, value) |> Js.Json.stringify),
        ~headers=authHeader(),
        ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };

  /* Resets a user's reading history */
  let resetUser = (userId:string) => {
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/" ++ userId ++ "/reset",
        Fetch.RequestInit.make(
          ~method_=Put,
          ~headers=authHeader(),
          ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };
};
