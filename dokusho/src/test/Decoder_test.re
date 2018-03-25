open Jest;
open Types;

describe("Decoders", () => {
  open Expect;

    describe("Decoders.parsePageType", () => {  

      test("Can parse all Page Types", () => {
        expect("Book" |> Decoders.parsePageType) |> toBe(Book) |> ignore;
        expect("Lyric" |> Decoders.parsePageType) |> toBe(Lyric) |> ignore;
        expect("Manga" |> Decoders.parsePageType) |> toBe(Manga) |> ignore;
        expect("Net" |> Decoders.parsePageType) |> toBe(Net) |> ignore;
        expect("News" |> Decoders.parsePageType) |> toBe(News) |> ignore;
        expect("Else" |> Decoders.parsePageType) |> toBe(Book);
      });
    });

    let entryStr = "{\"id\": 1, \"kind\": \"Book\", \"value\": 1}";
    let dayStr = "{\"date\": \"2018-03-25T00:00\", \"entries\": [" ++ entryStr ++ "]}";
    let historyStr = "{ \"days\": [" ++ dayStr++"]}";

    describe("Decoders.parseEnry", () => {
      test("Can parse valid json into an entry", () =>
        expect(entryStr
                |> Json.parseOrRaise 
                |> Decoders.parseEntry) 
                |> toEqual({id: 1, kind: Book, value: 1}))
    });

    describe("Decoders.parseDay", () => {
      test("Can parse valid json into a day", () =>
        expect(dayStr 
                |> Json.parseOrRaise 
                |> Decoders.parseDay) 
                |> toEqual(
                  {date: "2018-03-25T00:00", entries:[{id: 1, kind: Book, value: 1}]}
                  ))
    });

    describe("Decoders.parseHistory", () => {
      test("Can parse valid json into a reading history", () =>
        expect(historyStr 
                |> Json.parseOrRaise 
                |> Decoders.parseHistory) 
                |> toEqual({
                  days: [
                    {
                      date: "2018-03-25T00:00", 
                      entries:[{id: 1, kind: Book, value: 1}]
                    }
                  ]
                }
              ))
    });

});