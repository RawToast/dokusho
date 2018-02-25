open Types;
open PageType;

module ReadingData {
  let empty = { entries: [] };

  let createEntry = (nextId, pt, pageCount) => {
    id: nextId,
    kind: pt,
    value: pageCount
  };

  let appendEntry: (readingData, entry) => readingData = 
    (rd, entry) => {
      { entries: [entry, ...rd.entries] };
  };

  let pageCount = (rd: readingData) => rd.entries 
        |> List.map(i => float_of_int(i.value) *. PageType.pageScore(i.kind))
        |> List.fold_left((a, b) => a +. b, 0.);
}