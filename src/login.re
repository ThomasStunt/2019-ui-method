let component = ReasonReact.statelessComponent("Login");
let make = (_children) => {
    ...component,
    render: self => {
            <div className="container">
                <br/>
                <form>
                  <br/>
                  <div className="form-group">
                    <label htmlFor="inputMail">(ReasonReact.string("Email address"))</label>
                    <input type_="email" className="form-control" id="inputMail" placeholder="Enter email"/>
                  </div>
                  <div className="form-group">
                    <label htmlFor="inputPwd">(ReasonReact.string("Password"))</label>
                    <input type_="password" className="form-control" id="inputPwd" placeholder="Password"/>
                  </div>
                  <button type_="submit" className="btn btn-primary">(ReasonReact.string("Submit"))</button>
                </form>
            </div>
    }
};
