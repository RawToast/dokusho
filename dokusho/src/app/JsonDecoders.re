open Types;

module JsonDecoders = {
  open PageType;
  let parsePageType = json : pageType =>
    switch (PageType.findOptType(Json.stringify(json))) {
    | Some(pt) => pt
    | None => Book /* Not wise but gets things working */
    };

  let parseEntry = (json: Js.Json.t) : entry =>
    Json.Decode.{
      id: json |> field("id", int),
      kind: json |> field("kind", parsePageType),
      value: json |> field("value", int)
    };

  let parseEntriesJson = json => Json.Decode.list(parseEntry, json);

  let parseDay = (json: Js.Json.t) : day =>
    Json.Decode.{
      date: json |> field("date", string),
      entries: json |> field("entries", parseEntriesJson)
    };

  let parseDaysJson = json => Json.Decode.list(parseDay, json);

  let parseHistory = (json: Js.Json.t) : readingHistory =>
    Json.Decode.{days: json |> field("days", parseDaysJson)};
};