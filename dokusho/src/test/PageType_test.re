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
      test("Can convert Book pageType into a string", () => 
        expect(PageType.toString(Book)) |> toBe("Book"));

      test("Can convert Lyric pageType into a string", () => 
        expect(PageType.toString(Lyric)) |> toBe("Lyric"));

      test("Can convert Manga pageType into a string", () => 
        expect(PageType.toString(Manga)) |> toBe("Manga"));

      test("Can convert News pageType into a string", () => 
        expect(PageType.toString(News)) |> toBe("News"));

      test("Can convert Net pageType into a string", () => 
        expect(PageType.toString(Net)) |> toBe("Net"));
    });

    describe("PageType.findOptType", () => {

      test("Returns `None` when given an invalid string", () => 
        expect(PageType.findOptType("ABC123")) |> toBe(None));
        
      test("Returns some(pageType) when given valid input", () => 
        expect(PageType.findOptType("News")) |> toEqual(Some(News)));

      test("Can find the Net pageType", () =>
        expect(PageType.findOptType("Net")) |> toEqual(Some(Net)));

      test("Can find the Lyric pageType", () =>
        expect(PageType.findOptType("Lyric")) |> toEqual(Some(Lyric)));

      test("Can find the manga pageType", () =>
        expect(PageType.findOptType("Manga")) |> toEqual(Some(Manga)));

      test("Can find the Book pageType", () =>
        expect(PageType.findOptType("Book")) |> toEqual(Some(Book)));
        

      test("Interacts with toString as expected", () =>
        expect(PageType.findOptType(PageType.toString(Manga))) |> toEqual(Some(Manga)));
    });

    describe("PageType.pageTypes", () => {

      test("Returns a list of page types", () => 
        expect(PageType.pageTypes |> List.hd |> i => i.pageType) |> toBe(Book));
        
      test("Including all page types", () =>
        expect(PageType.pageTypes |> List.length) |> toBe(5));
        
    });
});
