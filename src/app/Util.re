module Util {
    let valueFromEvent = (evt) : string => ( evt
    |> ReactEventRe.Form.target
    |> ReactDOMRe.domElementToObj
    )##value;

    let intFromEvent = (evt) : string => (( evt
        |> ReactEventRe.Form.target
        |> ReactDOMRe.domElementToObj
        )##value)
            |> (s) => if (int_of_string(s) == 1) s else "";

    let string_map_partial = (f: char => option(char), s: string) => {
        let buf = Bytes.create(String.length(s));
        let j = ref(0);
        for (i in 0 to String.length(s) - 1) {
            switch (f(s.[i])) {
            | None => ()
            | Some(c) =>
            Bytes.set(buf, j^,c );
            incr(j);
            };
        };
        Bytes.sub_string(buf, 0, j^);
        };
}