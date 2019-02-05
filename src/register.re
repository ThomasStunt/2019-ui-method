let component = ReasonReact.statelessComponent("Register");
let make = (_children) => {
    ...component,
    render: self => {
            <div className="container">
                <br/>
                <form>
                  <small id="emailHelp" className="form-text text-muted">(ReasonReact.string("We'll never share your infos with anyone else."))</small>
                  <br/>
                  <div className="form-group">
                    <label htmlFor="firstNameInput">(ReasonReact.string("First name"))</label>
                    <input type_="text" className="form-control" id="firstNameInput" placeholder="Enter first name"/>
                  </div>
                  <div className="form-group">
                    <label htmlFor="lastNameInput">(ReasonReact.string("Last name"))</label>
                    <input type_="text" className="form-control" id="lastNameInput" placeholder="Enter last name"/>
                  </div>
                  <div className="form-group">
                    <label htmlFor="exampleInputEmail1">(ReasonReact.string("Email address"))</label>
                    <input type_="email" className="form-control" id="exampleInputEmail1" placeholder="Enter email"/>
                  </div>
                  <div className="form-group">
                    <label htmlFor="exampleInputPassword1">(ReasonReact.string("Password"))</label>
                    <input type_="password" className="form-control" id="exampleInputPassword1" placeholder="Password"/>
                  </div>
                  <button type_="submit" className="btn btn-primary">(ReasonReact.string("Submit"))</button>
                </form>
            </div>
    }
};
