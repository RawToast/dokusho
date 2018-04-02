open Jest;

open Dokusho;
open Types;

describe("Dokusho", () => {
  open ExpectJs;
  open Day;

describe("Dokusho.initialState", () => { 
   
    test("Should have today as the only day", () =>
      expect(Dokusho.initState().readingData.days |> List.length) |> toBe(1));

    test("Today should have an empty list of entries", () =>
      expect(Dokusho.initState().readingData.days 
        |> List.hd 
        |> Day.entries
        |> List.length)
        |> toBe(0));

    test("Should have Book selected", () =>
      expect(Dokusho.initState().selectedEntry) |> toBe(Book));
  });

  describe("Dokusho.make", () => {  
    test("requires a string value to render", () => {
      let component = ReactShallowRenderer.renderWithRenderer(<Dokusho token=""/>);
  
      expect(Js.Undefined.return(component)) |> toBeDefined;
    });
  });
});
