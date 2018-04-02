open Client;
open Types;

module Actions = {
    let addNewEntry = (pageType, count) => ReasonReact.SideEffects(
        ( self =>
        Js.Promise.(
            Client.newEntry(Types.testUser, pageType, count)
            |> then_((serverResponse: serverResponse) => {
            self.send(UpdateHistory(serverResponse.readingHistory.days));
            resolve(serverResponse);
            })) 
            |> ignore
        )
    );

    let loadUserData = (userId) => ReasonReact.SideEffects(
        (self =>
            Client.userHistory(userId)
              |> Js.Promise.then_((serverResponse: serverResponse) => {
                if(List.length(serverResponse.readingHistory.days) != 0) {
                  self.send(
                    UpdateHistory(
                      serverResponse.readingHistory.days))
                };
                Js.Promise.resolve(serverResponse);
              })
          |> ignore
        )
      );
};