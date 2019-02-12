open Extractor;
open Session;

type state = {
  email: string,
  password: string,
};

type action =
  | UpdateLogin(string)
  | UpdatePassword(string)
  | Login
  | Loading
  | UserLoaded
  | Ok;

let log = state => {
  let currentUsr = Js.Dict.empty();

  Js.Dict.set(currentUsr, "password", Js.Json.string(state.password));
  Js.Dict.set(currentUsr, "email", Js.Json.string(state.email));
  Js.Promise.(
    Fetch.fetchWithInit(
      "https://cors-anywhere.herokuapp.com/http://app-3895ccd8-bdf5-4169-85d6-63c1f6b70406.cleverapps.io/api/v1/users/login",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(currentUsr))),
        ~headers=
          Fetch.HeadersInit.make({
            "Content-Type": "application/json",
            "Origin": "http://app-3895ccd8-bdf5-4169-85d6-63c1f6b70406.cleverapps.io/api/v1/users/login",
          }),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Extractor.readResponse |> (finalUser => Some(finalUser) |> resolve))
  );
};

let component = ReasonReact.reducerComponent("Login");

let make = _children => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateLogin(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    | Login =>
      ReasonReact.UpdateWithSideEffects(
        state,
        self =>
          Js.Promise.(
            log(state)
            |> then_(result =>
                 switch (result) {
                 | Some(user) => resolve(self.send(UserLoaded))
                 | None => resolve()
                 }
               )
            |> catch(_err => Js.Promise.resolve())
            |> ignore
          ),
      )
    | UserLoaded => ReasonReact.SideEffects(_ => ReasonReact.Router.push("score"))
    | _ => ReasonReact.NoUpdate
    },
  render: _self =>
    <div>
      <Header />
      <div className="container">
        <br />
        <form>
          <br />
          <div className="form-group">
            <label htmlFor="exampleInputEmail1"> {ReasonReact.string("Email address")} </label>
            <input
              type_="text"
              name="inputMail"
              className="form-control"
              value={_self.state.email}
              placeholder="Email address"
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
              name="inputPwd"
              className="form-control"
              value={_self.state.password}
              placeholder="Password"
              onChange={event => _self.send(UpdatePassword(ReactEvent.Form.target(event)##value))}
            />
          </div>
        </form>
        <button onClick={_ => _self.send({Login})} className="btn btn-primary">
          {ReasonReact.string("Connect")}
        </button>
      </div>
    </div>,
};
