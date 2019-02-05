module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
        <div>
            <Header />
            <Register />
        </div>
    };
};

ReactDOMRe.renderToElementWithId(<App />, "main");
