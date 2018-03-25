[%raw "require('isomorphic-fetch')"];

open Types;

module Client = {
  type serverResponse = {
    userId: string,
    readingHistory: readingHistory
  };
  let parseResponse = (json: Js.Json.t) : serverResponse =>
    Json.Decode.{
      userId: json |> field("userId", string),
      readingHistory: json |> field("readingHistory", Decoders.parseHistory)
    };
  let backendURI = "http://35.189.70.144:8080";
  /* let backendURI = "http://localhost:8080"; */
  let jsonHeader = Fetch.HeadersInit.make({"Content-Type": "application/json"});

  /* Fetches the given user's reading history */
  let userHistory = (userId:string) =>
    Js.Promise.(
      Fetch.fetch(backendURI ++ "/history/" ++ userId)
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );

  /* Adds a new reading entry for today to a user's reading history */
  let newEntry = (userId:string, kind: pageType, value: int) => {
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/" ++ userId ++ "/add",
        Fetch.RequestInit.make(~method_=Post,
        ~body=Fetch.BodyInit.make(Encoders.endcodeInput(kind, value) |> Js.Json.stringify),
        ~headers=jsonHeader,
        ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };

  /* Resets a user's reading history */
  let resetUser = (userId:string) => {
    Js.Promise.(
      Fetch.fetchWithInit(backendURI ++ "/history/" ++ userId ++ "/reset",
        Fetch.RequestInit.make(~method_=Put,
        ~headers=jsonHeader,
        ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };
};
