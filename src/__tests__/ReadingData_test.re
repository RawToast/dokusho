open Jest;

open ReadingData;
open Types;

describe("ReadingData", () => {
  open Expect;

    describe("ReadingData.empty", () => {  
      test("Is an empty ReadingData object", () =>
        expect(List.length(ReadingData.empty.entries)) |> toBe(0));
    });

});
