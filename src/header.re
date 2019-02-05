let component = ReasonReact.statelessComponent("Header");
let make = (_children) => {
    ...component,
    render: self =>
        <nav className="navbar navbar-expand-lg navbar-light bg-light">
            <a href="">(ReasonReact.string(" Login "))</a>
        </nav>
};
