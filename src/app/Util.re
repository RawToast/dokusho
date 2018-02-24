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
}