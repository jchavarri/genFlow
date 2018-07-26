/* @flow strict */

var Component1 = require("./Component1.bs");
var ReasonReact = require("reason-react/src/ReasonReact.js");

import type {Component as ReactComponent} from 'React';
import type {actionless as ReasonReactactionless} from './shims/ReasonReactShim';
import type {componentSpec as ReasonReactcomponentSpec} from './shims/ReasonReactShim';
import type {noRetainedProps as ReasonReactnoRetainedProps} from './shims/ReasonReactShim';
import type {stateless as ReasonReactstateless} from './shims/ReasonReactShim';
import type {variant as Component2variant} from './Component2.re';
const consumeVariant = Component1.consumeVariant;
const concat = (function (Arg1, Arg2) { const result = Component1.concat(Arg1, (Arg2 === null ? undefined : Arg2)); return result });
const plus = Component1.plus;
export type Props = {|message?:string|};
const component = ReasonReact.wrapReasonForJs(
  Component1.component,
  (function (jsProps: {...Props, children:any}) {
     return Component1.make(jsProps.message, jsProps.children);
  }));

exports.consumeVariant = (consumeVariant: (Component2variant) => number);
exports.concat = (concat: (string, ?string) => ?string);
exports.plus = (plus: <T10970>(number, T10970) => number);
exports.component = (component: React$ComponentType<Props>);