open Jest;

open Input;

describe("Input", () => {
  open Expect;

    describe("Input.str", () => {  
      test("Is an alias for React", () =>
        expect(Input.str("Hello")) |> toBe(ReasonReact.stringToElement("Hello")));
    });
});
