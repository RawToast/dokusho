open Jest;

describe("Util", () => {
  open Expect;
  open Util;

    describe("Util.string_map_partial", () => {  
      test("Can filter a string using a predicate", () =>
        expect(Util.string_map_partial(s => if(s == 'l') Some(s) else None, "Hello")) |> toBe("ll"));
    });

});
