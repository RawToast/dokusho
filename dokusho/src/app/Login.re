let component = ReasonReact.statelessComponent("Login");

let make = (_) => {
  ...component,
  render: (_) =>
    <div>
      <div className="title"> (ReasonReact.stringToElement("Dokusho")) </div>
      <div className="desc">
        <text>
          (ReasonReact.stringToElement(
              "Dokusho is a japanese reading tracker"
            )
          )
        </text>
      </div>
      <div className="login"> <LoginButton /> </div>
    </div>
};