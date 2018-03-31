open Jest;

open Types;

describe("Entry", () => {
  open ExpectJs;

  test("Renders when given an entry", () => {
    let entry = {id: 123, kind: Net, value: 123};
    let component = ReactShallowRenderer.renderWithRenderer(<Entry entry=entry/>);
    
    expect(Js.Undefined.return(component)) |> toBeDefined;
  });
});