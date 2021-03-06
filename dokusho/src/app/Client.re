[%raw "require('isomorphic-fetch')"];

open Types;
open Auth;

type serverResponse = {
  userId: string,
  readingHistory: readingHistory
};

module Client = {
  open Dom.Storage;

  let accessToken = (default) => sessionStorage |> getItem("accessToken") |> Rationale.Option.default(default);
  let backendURI = "http://35.197.251.200:8080";
  let jsonHeader = Fetch.HeadersInit.make({"Content-Type": "application/json"});
  let authHeader = (default) => Fetch.HeadersInit.makeWithArray([|( "Content-Type", "application/json" ), ( "accessToken", accessToken(default) )|]);

  let parseResponse = (json: Js.Json.t) => {
    Json.Decode.{
      userId: json |> field("userId", string),
      readingHistory: json |> field("readingHistory", Decoders.parseHistory)
    };
  };

  let parseResponseT = (jString) => 
    Json.parse(jString)
      |> Rationale.Option.default(Json.parseOrRaise("{\"userId\": \"userId\",\"readingHistory\": {\"days\": [] } }"))
      |> json =>
        Json.Decode.{
          userId: json |> field("userId", string),
          readingHistory: json |> field("readingHistory", Decoders.parseHistory)
        };

  /* Fetches the given user's reading history, or an empty one */
  let userHistory = (userId:string) => {
    Js.Console.log("Get history: " ++ Auth.getAccessToken());
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history",
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=authHeader(userId),
          ()))
      |> then_(Fetch.Response.text)
      |> then_(resp => resp |> parseResponseT |> resolve)
    );
  };

  /* Adds a new reading entry for today to a user's reading history */
  let newEntry = (userId:string, kind: pageType, value: int) => {
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/add",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Encoders.endcodeInput(kind, value) |> Js.Json.stringify),
        ~headers=authHeader(userId),
        ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };

  /* Resets a user's reading history */
  let resetUser = (userId:string) => {
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/reset",
        Fetch.RequestInit.make(
          ~method_=Put,
          ~headers=authHeader(userId),
          ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };
};
