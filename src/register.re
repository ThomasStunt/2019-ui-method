open Extractor;

type state = {
  email: string,
  password: string,
};

type action =
  | UpdateLogin(string)
  | UpdatePassword(string)
  | Register
  | RegisterUsers
  | RegisterUsersFailed;

let component = ReasonReact.reducerComponent("Register");

let register = state => {
  let usr = Js.Dict.empty();
  Js.Dict.set(usr, "email", Js.Json.string(state.email));
  Js.Dict.set(usr, "password", Js.Json.string(state.password));
  Js.Promise.(
    Fetch.fetchWithInit(
      "http://localhost:8080/api/v1/users/",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(usr))),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => {
         Js.log(json);
         json |> Extractor.readResponse |> (user => Some(user) |> resolve);
       })
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
                 | Some(user) => resolve(self.send(RegisterUsers))
                 }
               )
            |> catch(_err => {
                 Js.log(_err);
                 Js.Promise.resolve();
               })
            |> ignore
          ),
      )
    | RegisterUsers => ReasonReact.SideEffects(_ => ReasonReact.Router.push("score"))
    | _ => ReasonReact.Update(state)
    },
  render: _self =>
    <div>
      <h1> {ReasonReact.string("Register form")} </h1>
      <form>
        <label>
          {ReasonReact.string("Login")}
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
            type_="password"
            name="inputPwd"
            value={_self.state.password}
            onChange={event => _self.send(UpdatePassword(ReactEvent.Form.target(event)##value))}
          />
        </label>
        <br />
      </form>
      <button onClick={_ => _self.send({Register})}> {ReasonReact.string("register")} </button>
    </div>,
};
