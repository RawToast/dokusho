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
});