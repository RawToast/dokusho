open Jest;

open Day;

describe("Day", () => {
  open Expect;

    describe("Day.today", () => {  
      let today = Day.now();
      test("Creates a day with no entries", () =>
        expect(today.entries |> List.length) |> toBe(0));

      test("Creates a string representation of a date time", () =>
        expect(today.date |> String.length ) |> toBe(24));
    });

    describe("Day.yesterday", () => {  
      let today = Day.yesterday();
      test("Creates a day with no entries", () =>
        expect(today.entries |> List.length) |> toBe(0));

      test("Creates a string representation of a date time", () =>
        expect(today.date |> String.length ) |> toBe(24));
    });


    describe("Day.entries", () => {  
      let today = Day.now();
      test("Is a helper method to get the Day's entry list", () =>
        expect(today.entries) |> toEqual(Day.entries(today)));
    });

    describe("Day.appendEntry", () => {  
      let today = Day.now();
      let appendedDay = Day.createEntry(1, News, 1) |> Day.appendEntry(today);
      test("Adds an entry to a day", () =>
        expect(appendedDay.entries |> List.length) |> toBe(1));
    });

});