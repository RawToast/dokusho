let component = ReasonReact.statelessComponent("Login");

let make = (_) => {
  ...component,
  render: (_) =>
    <div>
      <div className="title"> (ReasonReact.string("Dokusho")) </div>
      <div className="desc">
        <text>
          (ReasonReact.string(
              "Dokusho is a japanese reading tracker"
            )
          )
        </text>
      </div>
      <div className="login"> <LoginButton /> </div>
    </div>
};