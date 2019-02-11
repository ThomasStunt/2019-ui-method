open Extractor;
open Session;

let url_dev = "http://localhost:8080/";
type state = {
  email: string,
  password: string,
};

type action =
  | UpdateLogin(string)
  | UpdatePassword(string)
  | Login
  | Loading
  | LoadedUsers
  | Ok;

let log = state => {
  let currentUsr = Js.Dict.empty();

  Js.Dict.set(currentUsr, "password", Js.Json.string(state.password));
  Js.Dict.set(currentUsr, "email", Js.Json.string(state.email));
  Js.Promise.(
    Fetch.fetchWithInit(
      "http://localhost:8080/api/v1/users/login",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(currentUsr))),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
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
                 | Some(user) => resolve(self.send(LoadedUsers))
                 | None => resolve()
                 }
               )
            |> catch(_err => Js.Promise.resolve())
            |> ignore
          ),
      )
    | LoadedUsers => ReasonReact.SideEffects(_ => ReasonReact.Router.push("score"))
    | _ => ReasonReact.NoUpdate
    },
  render: _self =>
    <div>
      <h1> {ReasonReact.string("Login")} </h1>
      <form>
        <label>
          {ReasonReact.string("Login : ")}
          <input
            type_="text"
            name="inputLogin"
            value={_self.state.email}
            onChange={event => _self.send(UpdateLogin(ReactEvent.Form.target(event)##value))}
          />
        </label>
        <br />
        <label>
          {ReasonReact.string("Password : ")}
          <input
            type_="text"
            name="inputPwd"
            value={_self.state.password}
            onChange={event => _self.send(UpdatePassword(ReactEvent.Form.target(event)##value))}
          />
        </label>
        <br />
      </form>
      <button onClick={_ => _self.send({Login})}> {ReasonReact.string("Log in")} </button>
    </div>,
};
