open Jest;

open Types;

let entryStr = "{\"id\": 1, \"kind\": \"Book\", \"value\": 1}";
let dayStr = "{\"date\": \"2018-03-25T00:00\", \"entries\": [" ++ entryStr ++ "]}";
let historyStr = "{ \"days\": [" ++ dayStr ++ "]}";

describe("Decoders", () => {
  open Expect;

  describe("Decoders.parsePageType", () =>
    test("Can parse all Page Types", () => {
      expect("Book" |> Decoders.parsePageType) |> toBe(Book) |> ignore;
      expect("Lyric" |> Decoders.parsePageType) |> toBe(Lyric) |> ignore;
      expect("Manga" |> Decoders.parsePageType) |> toBe(Manga) |> ignore;
      expect("Net" |> Decoders.parsePageType) |> toBe(Net) |> ignore;
      expect("News" |> Decoders.parsePageType) |> toBe(News) |> ignore;
      expect("Else" |> Decoders.parsePageType) |> toBe(Book);
    })
  );

  describe("Decoders.parseEnry", () =>
    test("Can parse valid json into an entry", () =>
      expect(entryStr |> Json.parseOrRaise |> Decoders.parseEntry)
      |> toEqual({id: 1, kind: Book, value: 1})
    )
  );

  describe("Decoders.parseDay", () =>
    test("Can parse valid json into a day", () =>
      expect(dayStr |> Json.parseOrRaise |> Decoders.parseDay)
      |> toEqual({
           date: "2018-03-25T00:00",
           entries: [{id: 1, kind: Book, value: 1}]
         })
    )
  );

  describe("Decoders.parseHistory", () =>
    test("Can parse valid json into a reading history", () =>
      expect(historyStr |> Json.parseOrRaise |> Decoders.parseHistory)
      |> toEqual({
           days: [
             {
               date: "2018-03-25T00:00",
               entries: [{id: 1, kind: Book, value: 1}]
             }
           ]
         })
    )
  );
});

describe("Encoders", () => {
  open Expect;

  describe("Encoders.encodeEntry", () =>
    test("Can encode and entry to json", () =>
      expect(
        {id: 1, kind: Book, value: 1} |> Encoders.encodeEntry |> Json.stringify
      )
      |> toEqual(entryStr)
    )
  );

  describe("Encoders.encodeDay", () =>
    test("Can encode a day to json", () =>
      expect(
        {date: "2018-03-25T00:00", entries: [{id: 1, kind: Book, value: 1}]}
        |> Encoders.encodeDay
        |> Json.stringify
      )
      |> toEqual(dayStr)
    )
  );

  describe("Encoders.encodeHistory", () =>
    test("Can parse valid json into a reading history", () =>
      expect(
        {
          days: [
            {
              date: "2018-03-25T00:00",
              entries: [{id: 1, kind: Book, value: 1}]
            }
          ]
        }
        |> Encoders.encodeReadingHistory
        |> Json.stringify
      )
      |> toEqual(historyStr)
    )
  );
});