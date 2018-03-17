open Types;

module Client = {
  open JsonDecoders;

  type serverResponse = {
    userId: string,
    readingHistory
  };
  let parseResponse = (json: Js.Json.t) : serverResponse =>
    Json.Decode.{
      userId: json |> field("userId", string),
      readingHistory: json |> field("readingHistory", JsonDecoders.parseHistory)
    };
  let backendURI = "http://192.168.64.4:30908";
  let getIt = () =>
    Js.Promise.(
      Axios.get(backendURI ++ "/history/safe/full")
      |> then_(response => resolve(parseResponse(response##data)))
    );
};