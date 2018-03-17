type pageType =
  | Manga
  | News
  | Book
  | Lyric
  | Net;

type content = {
  name: string,
  pageType
};

type entry = {
  id: int,
  kind: pageType,
  value: int
};

type day = {
  date: string,
  entries: list(entry)
};

type readingHistory = {days: list(day)};

type mainState = {
  readingData: readingHistory,
  selectedEntry: pageType
};

type action =
  | AddEntry(pageType, int)
  | ChangeSelection(pageType);

module Decoders = {
  let parsePageType = json : pageType =>
    switch (json |> Json.stringify) {
    | "Manga" => Manga
    | "News" => News
    | "Book" => Book
    | "Lyric" => Lyric
    | "Net" => Net
    | _ => Book
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

module Encoders = {
  let encodeEntry = entry =>
    Json.Encode.(
      object_([
        ("id", int(entry.id)),
        ("kind", string(switch entry.kind {
          | Manga => "Manga"
          | News => "News"
          | Book => "Book"
          | Lyric => "Lyric"
          | Net => "Net"
          })),
        ("value", int(entry.value))
      ])
    );
  let encodeDay = day =>
    Json.Encode.(
      object_([
        ("date", string(day.date)),
        ("value", day.entries |> list(encodeEntry))
      ])
    );
  let encodeReadingHistory = readingHistory =>
    Json.Encode.(
      object_([("date", readingHistory.days |> list(encodeDay))])
    );
};