open Jest;

open Input;

describe("Input", () => {
  open Expect;

    describe("Input.render", () => {  
      test("Is an alias for React", () =>
        expect(Input.str("Hello")) |> toBe(ReasonReact.string("Hello")));
    });
});
