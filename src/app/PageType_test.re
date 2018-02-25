open Jest;

open PageType;
open Types;

describe("PageType", () => {
  open Expect;

    describe("PageType.pageScore", () => {
    
      test("Can score a page type", () =>
        expect(PageType.pageScore(Book)) |> toBe(1.));
    
      test("News and Net have the same score", () =>
        expect(PageType.pageScore(News)) |> toBe(PageType.pageScore(Net)));
    
      test("Lyric's score is less than Book's score", () =>
        expect(PageType.pageScore(Manga)) |> toBeLessThan(PageType.pageScore(Book)));
    
      test("Manga's score is less than Lyric's score", () =>
        expect(PageType.pageScore(Manga)) |> toBeLessThan(PageType.pageScore(Lyric)));
    });


    describe("PageType.toString", () => {
      test("Can convert a pageType into a string", () =>
        expect(PageType.toString(Book)) |> toBe("Book"));
    });

    describe("PageType.findOptType", () => {

      test("Returns `None` when given an invalid string", () =>
        expect(PageType.findOptType("ABC123")) |> toBe(None));
        
      test("Returns some(pageType) when given valid input", () =>
        expect(PageType.findOptType("News")) |> toEqual(Some(News)));

      test("Interacts with toString as expected", () =>
        expect(PageType.findOptType(PageType.toString(Manga))) |> toEqual(Some(Manga)));
    });
});
