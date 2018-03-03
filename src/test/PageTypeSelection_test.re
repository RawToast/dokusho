open Jest;

open PageTypeSelection;

describe("PageTypeSelection", () => {
  open ExpectJs;

  test("Renders when given an onChangeSelect function", () => {

    let onChangeSelectFunction = (pt) => ();

    let component = ReactShallowRenderer.renderWithRenderer(
        <PageTypeSelection onChangeSelect=onChangeSelectFunction/>
      );
    
    expect(Js.Undefined.return(component)) |> toBeDefined;
  });

  describe("PageTypeSelection.str", () => {  
    test("Is an alias for ReasonReact.stringToElement", () =>
      expect(PageTypeSelection.str("Hello")) |> toBe(ReasonReact.stringToElement("Hello")));
  });  
});