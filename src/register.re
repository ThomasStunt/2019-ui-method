type state = {
  email: string,
  password: string,
};

type action =
  | UpdateLogin(string)
  | UpdatePassword(string)
  | Register
  | RegisteredUser
  | Error;

let component = ReasonReact.reducerComponent("Register");

let register = state => {
  let currentUsr = Js.Dict.empty();
  Js.Dict.set(currentUsr, "email", Js.Json.string(state.email));
  Js.Dict.set(currentUsr, "password", Js.Json.string(state.password));
  Js.Promise.(
    Fetch.fetchWithInit(
      Const.baseUrl() ++ "/api/v1/users/",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(currentUsr))),
        ~headers=
          Fetch.HeadersInit.make({
            "Content-Type": "application/json",
            "Origin": "https://app-3895ccd8-bdf5-4169-85d6-63c1f6b70406.cleverapps.io/api/v1/users/login",
          }),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Extractor.readResponse |> (finalUser => Some(finalUser) |> resolve))
  );
};

let make = _children => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateLogin(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    | Register =>
      ReasonReact.UpdateWithSideEffects(
        state,
        self =>
          Js.Promise.(
            register(state)
            |> then_(result =>
                 switch (result) {
                 | Some(_) => resolve(self.send(RegisteredUser))
                 | None => resolve()
                 }
               )
            |> catch(_err => Js.Promise.resolve())
            |> ignore
          ),
      )
    | RegisteredUser => ReasonReact.SideEffects(_ => ReasonReact.Router.push("score"))
    | _ => ReasonReact.Update(state)
    },

  render: _self => {
    <div>
      <Header />
      <div className="container">
        <br />
        <form>
          <br />
          <div className="form-group">
            <label htmlFor="firstNameInput"> {ReasonReact.string("First name")} </label>
            <input type_="text" className="form-control" id="firstNameInput" placeholder="Enter first name" />
          </div>
          <div className="form-group">
            <label htmlFor="lastNameInput"> {ReasonReact.string("Last name")} </label>
            <input type_="text" className="form-control" id="lastNameInput" placeholder="Enter last name" />
          </div>
          <div className="form-group">
            <label htmlFor="exampleInputEmail1"> {ReasonReact.string("Email address")} </label>
            <input
              type_="email"
              className="form-control"
              id="exampleInputEmail1"
              placeholder="Enter email"
              value={_self.state.email}
              onChange={event => _self.send(UpdateLogin(ReactEvent.Form.target(event)##value))}
            />
            <small id="emailHelp" className="form-text text-muted">
              {ReasonReact.string("We'll never share your infos with anyone else.")}
            </small>
          </div>
          <div className="form-group">
            <label htmlFor="exampleInputPassword1"> {ReasonReact.string("Password")} </label>
            <input
              type_="password"
              className="form-control"
              id="exampleInputPassword1"
              value={_self.state.password}
              onChange={event => _self.send(UpdatePassword(ReactEvent.Form.target(event)##value))}
              placeholder="Password"
            />
          </div>
        </form>
        <button onClick={_ => _self.send({Register})} className="btn btn-primary">
          {ReasonReact.string("Submit")}
        </button>
      </div>
    </div>;
  },
};
