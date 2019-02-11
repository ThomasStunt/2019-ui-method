let component = ReasonReact.statelessComponent("Header");
let make = _children => {
  ...component,
  render: self => {
    <nav className="navbar navbar-expand-lg navbar-light bg-light">
      <ul className="navbar-nav mr-auto">
        <li className="nav-item active">
          <a className="nav-link" href="/login"> {ReasonReact.string("Login")} </a>
        </li>
        <li className="nav-item active"> <a className="nav-link"> {ReasonReact.string("Register")} </a> </li>
      </ul>
    </nav>;
  },
};
