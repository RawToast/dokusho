open Types;
open PageType;

module Day {
  let now = () => {
    let dateString = () => 
      Js.Date.setHoursMSMs(Js.Date.make(), ~hours=0., ~minutes=0., ~seconds=0., ~milliseconds=0.,()) 
          |> Js.Date.fromFloat
          |> Js.Date.toISOString;

    { date: dateString(), entries: []};
  };

  let yesterday = () => {
    let dateString = () => 
      Js.Date.setHoursMSMs((Js.Date.now() -. 86400000.)
            |> Js.Date.fromFloat, ~hours=0., ~minutes=0., ~seconds=0., ~milliseconds=0.,()) 
      |> Js.Date.fromFloat
      |> Js.Date.toISOString;

    { date: dateString(), entries: []};
  };

  let empty = { date: "", entries: []};

  let createEntry = (nextId, pt, pageCount) => {
    id: nextId,
    kind: pt,
    value: pageCount
  };

  let appendEntry: (day, entry) => day = 
    (rd, entry) => {
      { date: rd.date, entries: [entry, ...rd.entries] };
  };

  let pageCount = (rd: day) => rd.entries 
        |> List.map(i => float_of_int(i.value) *. PageType.pageScore(i.kind))
        |> List.fold_left((a, b) => a +. b, 0.);
}