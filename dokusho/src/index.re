[%bs.raw {|require('./styles/index.css')|}];

[@bs.module "./registerServiceWorker"] external register_service_worker : unit => unit = "default";

open Dokusho;

ReactDOMRe.renderToElementWithId(<Dokusho />, "root");

register_service_worker();