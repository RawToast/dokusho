open Jest;

open Types;
open Entry;
 
describe("Entry", () => {
  open ExpectJs;

  test("Renders when given an entry", () => {
    let entry = {id: 1, kind: Net, value: 1};
    let component = ReactShallowRenderer.renderWithRenderer(<Entry entry=entry/>);
    
    expect(Js.Undefined.return(component)) |> toBeDefined;
  });
});