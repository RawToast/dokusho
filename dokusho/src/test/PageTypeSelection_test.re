open Jest;

describe("PageTypeSelection", () => {
  open ExpectJs;

  test("Renders when given an onChangeSelect function", () => {
    let onChangeSelectFunction = (_pt) => ();
    let component = ReactShallowRenderer.renderWithRenderer(
        <PageTypeSelection onChangeSelect=onChangeSelectFunction/>
      );
    
    expect(Js.Undefined.return(component)) |> toBeDefined;
  });
});