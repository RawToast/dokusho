module Util {
    let valueFromEvent = (evt) : string => ( evt
    |> ReactEventRe.Form.target
    |> ReactDOMRe.domElementToObj
    )##value;
}