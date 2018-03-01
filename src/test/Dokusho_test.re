open Jest;

open Dokusho;
open Types;

describe("Dokusho", () => {
  open ExpectJs;

describe("Dokusho.initialState", () => {  
    test("Should have an empty list of entries", () =>
      expect(Dokusho.initState().readingData.entries |> List.length) |> toBe(0));

    test("Should have Book selected", () =>
      expect(Dokusho.initState().selectedEntry) |> toBe(Book));
  });

  describe("Dokusho.make", () => {  
    test("can render without any provided parameters", () => {
      let component = ReactShallowRenderer.renderWithRenderer(<Dokusho />);
  
      expect(Js.Undefined.return(component)) |> toBeDefined;
    });
  });

});
