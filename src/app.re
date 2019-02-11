open RouterConfig;

module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {...component, render: _self => <div> <RouterConfig /> </div>};
};

ReactDOMRe.renderToElementWithId(<App />, "main");
