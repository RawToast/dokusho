open Jest;

open Entry;
open Types;

describe("Component", () => {
  open ExpectJs;

  test("renders", () => {
    let entry = {id: 1, kind: Net, value: 1};
    let component = ReactShallowRenderer.renderWithRenderer(<Entry entry=entry/>);

    expect(Js.Undefined.return(component)) |> toBeDefined;
  });
});