let saveTok = value => {
  Dom.Storage.(localStorage |> setItem("Authorization", value));
};

let getTok = () => {
  Dom.Storage.(localStorage |> getItem("Authorization"));
};
