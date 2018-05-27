let component = ReasonReact.statelessComponent("Footer");

let make = (~pageCount: float, _children) => {
  ...component,
  render: (_) =>
    <div className="footer">
      (ReasonReact.string(string_of_float(pageCount) ++ " pages"))
    </div>
};