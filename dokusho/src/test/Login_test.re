open Jest;

describe("Login", () => {
  open ExpectJs;

  describe("Login.make", () => {  
    test("renders with no parameters", () => {
      let component = ReactShallowRenderer.renderWithRenderer(<Login/>);
  
      expect(Js.Undefined.return(component)) |> toBeDefined;
    });
  });
});
