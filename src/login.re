let component = ReasonReact.statelessComponent("Login");
let make = (_children) => {
    ...component,
    render: self =>
        <div>
            <form>
                <label>(ReasonReact.string("Login : "))</label>
                <input type_="text"/>
                <br/>
                <label>(ReasonReact.string("Password : "))</label>
                <input type_="password"/>
                <button>
                  (ReasonReact.string(" Connect "))
                </button>
            </form>
        </div>
};
