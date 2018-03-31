open Jest;

open DokuUtil;

describe("DateUtil", () => {
  open Expect;
  
    describe("DokuUtil.dateWithoutTime", () => {  
      test("Will remove the time data from a date", () =>
        expect(DateUtil.dateWithoutTime(Js.Date.make()) |> Js.Date.getMinutes) |> toBe(0.));
    });

    describe("DokuUtil.asDateKey", () => {  
      test("Will create a string of length 16", () =>
        expect(DateUtil.asDateKey(Js.Date.make()) |> String.length) |> toBe(16));
    });

    describe("DokuUtil.availableDates", () => {  
      test("Always returns a date", () =>
      
        expect(DateUtil.availableDates({days: []}) |> Array.length) |> toBeGreaterThan(0));
    });
});
