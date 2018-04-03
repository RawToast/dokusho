module DokuUtil = {
  let valueFromEvent = evt : string => (
                                         evt
                                         |> ReactEventRe.Form.target
                                         |> ReactDOMRe.domElementToObj
                                       )##value;
  let intFromEvent = evt : string =>
    (evt |> ReactEventRe.Form.target 
        |> ReactDOMRe.domElementToObj)##value
        |> s => if (int_of_string(s) == 1) { s } else { "" };
  let string_map_partial = (f: char => option(char), s) => {
    let buf = Bytes.create(String.length(s));
    let j = ref(0);
    for (i in 0 to String.length(s) - 1) {
      switch (f(s.[i])) {
      | None => ()
      | Some(c) =>
        Bytes.set(buf, j^, c);
        incr(j);
      };
    };
    Bytes.sub_string(buf, 0, j^);
  };
};

module DateUtil = {
  open Types; 

  let availableDates = (d: readingHistory) => d.days 
      |> List.map(d => Js.Date.fromString(d.date)) 
      |> (ls) => [Js.Date.make(), ...ls] 
      |> Array.of_list;

  let dateWithoutTime = selectedDate => Js.Date.fromFloat(Js.Date.utcWithYMDHMS(
        ~year=Js.Date.getFullYear(selectedDate),
        ~month=Js.Date.getMonth(selectedDate), 
        ~date=Js.Date.getDate(selectedDate),
        ~hours=0.,
        ~minutes=0.,
        ~seconds=0.)());

  let asDateKey = (date) => Js.String.slice(~from=0, ~to_=16, Js.Date.toISOString(date));
}