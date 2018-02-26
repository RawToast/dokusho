open Jest;

open ReadingData;
open Types;

describe("ReadingData", () => {
  open Expect;

    describe("ReadingData.empty", () => {  
      test("Is an empty ReadingData object", () =>
        expect(List.length(ReadingData.empty.entries)) |> toBe(0));
    });

    describe("ReadingData.createEntry", () => {  
      test("Can create an entry type", () =>
        expect(ReadingData.createEntry(1, Lyric, 1)) |> toEqual({id: 1, kind: Lyric, value: 1}));
    });

    describe("ReadingData.pageCount", () => {  
      test("Counts all pages types to give a weighted total", () =>
        expect(ReadingData.pageCount({ entries: [
          {id: 1, kind: Book, value: 1},
          {id: 2, kind: Lyric, value: 1},
          {id: 3, kind: Manga, value: 1},
          {id: 4, kind: Net, value: 1},
          {id: 5, kind: News, value: 1},]})) |> toBeLessThan(5.));

      test("Returns 0 for an empty list of entries", () =>
        expect(ReadingData.pageCount(ReadingData.empty)) |> toBe(0.));
    });

});
