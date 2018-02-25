open Jest;

open DokuUtil;

describe("Util", () => {
  open Expect;
  
    describe("DokuUtil.string_map_partial", () => {  
      test("Can filter a string using a predicate", () =>
        expect(DokuUtil.string_map_partial(s => if(s == 'l') Some(s) else None, "Hello")) |> toBe("ll"));
    });

});
