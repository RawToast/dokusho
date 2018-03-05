open Jest;

open Day;
open Types;

describe("Day", () => {
  open Expect;

    describe("Day.empty", () => {  
      test("Is an empty Day object", () =>
        expect(List.length(Day.empty.entries)) |> toBe(0));
    });

    describe("Day.now", () => {  
      test("Creates a Date with no reading entires", () =>
        expect(List.length(Day.now().entries)) |> toBe(0));

      test("Sets the date field", () =>
        expect(String.length(Day.now().date)) |> toBeGreaterThan(0));
        
      test("Sets the date field with a parsable date", () => {
        let testDate = Day.now().date;

        let otherDate = Js.Date.parse(testDate) |> Js.Date.toISOString;

        expect(testDate) |> toEqual(otherDate)
        });
      });

    describe("Day.createEntry", () => {  
      test("Can create an entry type", () =>
        expect(Day.createEntry(1, Lyric, 1)) |> toEqual({id: 1, kind: Lyric, value: 1}));
    });

    describe("Day.pageCount", () => {  
      test("Counts all pages types to give a weighted total", () =>
        expect(Day.pageCount({ date: "", entries: [
          {id: 1, kind: Book, value: 1},
          {id: 2, kind: Lyric, value: 1},
          {id: 3, kind: Manga, value: 1},
          {id: 4, kind: Net, value: 1},
          {id: 5, kind: News, value: 1},]})) |> toBeLessThan(5.));

      test("Returns 0 for an empty list of entries", () =>
        expect(Day.pageCount(Day.empty)) |> toBe(0.));
    });

});
