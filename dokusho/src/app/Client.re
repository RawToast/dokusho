open Types;

module Client {
    open PageType;

    type serverResponse = {
        userId: string,
        readingHistory: readingHistory
    };

    let parsePageType = (json): pageType => switch(PageType.findOptType(Json.stringify(json))){
        | Some(pt) => pt
        | None => Book /* Not wise but gets things working */
    };
    let parseEntry = (json: Js.Json.t) : entry =>
        Json.Decode.{
            id: json |> field("id", int),
            kind: json |> field("kind", parsePageType),
            value: json |> field("value", int)
        };
    
    let parseEntriesJson = (json) => Json.Decode.list(parseEntry, json);

    let parseDay = (json: Js.Json.t) : day =>
        Json.Decode.{
            date: json |> field("date", string),
            entries: json |> field("entries", parseEntriesJson)
        };

    let parseDaysJson = (json) => Json.Decode.list(parseDay, json);


    let parseHistory = (json: Js.Json.t) : readingHistory =>
        Json.Decode.{
            days: json |> field("days", parseDaysJson)
        };

    let parseResponse = (json: Js.Json.t): serverResponse =>
        Json.Decode.{
            userId: json |> field("userId", string),
            readingHistory: json |> field("readingHistory", parseHistory)
        };
  let backendURI = "http://192.168.64.4:30908";

  let getIt = () => Js.Promise.(
      Axios.get(backendURI ++ "/history/safe/full")
      |> then_(response => resolve(parseResponse(response##data)))
    ); 
};
open Rationale;
Client.getIt() |> Js.Promise.then_(
    (data: Client.serverResponse) => {
        Js.log(Js.List.hd(data.readingHistory.days));
        Js.log(Option.bind(Js.List.hd(data.readingHistory.days), d => Js.List.hd(d.entries)));
        Js.log(data);
        Js.Promise.resolve();
    }
)