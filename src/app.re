open RouterConfig;

module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {...component, render: _self => <Routeur />};
};

ReactDOMRe.renderToElementWithId(<App />, "main");
