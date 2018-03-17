[%raw "require('isomorphic-fetch')"];

open Types;

module Client = {
  type serverResponse = {
    userId: string,
    readingHistory
  };
  let parseResponse = (json: Js.Json.t) : serverResponse =>
    Json.Decode.{
      userId: json |> field("userId", string),
      readingHistory: json |> field("readingHistory", Decoders.parseHistory)
    };
  let backendURI = "http://192.168.64.4:30908";
  let internalURI = "http://backend:30908";
  let userHistory = userId =>
    Js.Promise.(
      Fetch.fetch(internalURI ++ "/history/safe/" ++ userId)
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  let jsonHeader = Fetch.HeadersInit.make({"Content-Type": "application/json"});
  let putReadingData = (userId, readingData) =>
    Js.Promise.(
      Fetch.fetchWithInit(
        internalURI ++ "/history/safe/" ++ userId,
        Fetch.RequestInit.make(
          ~method_=Put,
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(Encoders.encodeReadingHistory(readingData))
            ),
          ~headers=jsonHeader,
          ()
        )
      )
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  let newEntry = (userId, {kind, value}) => {
    Js.Promise.(
      Fetch.fetchWithInit(internalURI ++ "/history/" ++ userId ++ "/entries",
        Fetch.RequestInit.make(~method_=Post,
        ~body=Fetch.BodyInit.make(Encoders.endcodeInput(kind, value) |> Js.Json.stringify),
        ~headers=jsonHeader,
        ()))
      |> then_(Fetch.Response.json)
      |> then_(resp => resp |> parseResponse |> resolve)
    );
  };
};