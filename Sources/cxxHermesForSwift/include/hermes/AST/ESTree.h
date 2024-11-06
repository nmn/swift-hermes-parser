/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef HERMES_AST_ESTREE_H
#define HERMES_AST_ESTREE_H

#include "hermes/AST/Context.h"
#include "hermes/Support/StringTable.h"

#include "llvh/ADT/ArrayRef.h"
#include "llvh/ADT/Optional.h"
#include "llvh/ADT/StringRef.h"
#include "llvh/ADT/ilist.h"
#include "llvh/Support/Casting.h"
#include "llvh/Support/ErrorHandling.h"
#include "llvh/Support/SMLoc.h"

namespace hermes {

using llvh::ArrayRef;

namespace sem {
class FunctionInfo;
} // namespace sem

namespace ESTree {

using llvh::cast;
using llvh::SMLoc;
using llvh::SMRange;

class Node;
/// This is a string which is guaranteed to contain only valid Unicode
/// characters when decoded. In particular no mismatched surrogate pairs.
/// It is encoded with our "modified" utf-8 encoding, where parts of surrogate
/// pairs are encoded as separate characters. So, it does NOT represent valid
/// utf-8. To turn it into valid utf-8 it must be reencoded.
using NodeLabel = UniqueString *;
/// This is a JS string, which is a sequence of arbitrary 16-bit values, which
/// may or may not represent a valid utf-16 string.
/// It is encoded with our "modified" utf-8 encoding, where each separate 16-bit
/// value is encoded as a separate character. There are no guarantees about the
/// validity.
using NodeString = UniqueString *;
using NodeBoolean = bool;
using NodeNumber = double;
using NodePtr = Node *;
using NodeList = llvh::simple_ilist<Node>;

enum class NodeKind : uint32_t {
#define ESTREE_FIRST(NAME, ...) _##NAME##_First,
#define ESTREE_LAST(NAME) _##NAME##_Last,
#define ESTREE_NODE_0_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_1_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_2_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_3_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_4_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_5_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_6_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_7_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_8_ARGS(NAME, ...) NAME,
#define ESTREE_NODE_9_ARGS(NAME, ...) NAME,
#ifndef HERMES_PARSER_CONFIG_H
#define HERMES_PARSER_CONFIG_H

#if !defined(HERMES_PARSE_JSX)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_JSX 0
#else
#define HERMES_PARSE_JSX 1
#endif
#endif

#if !defined(HERMES_PARSE_FLOW)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_FLOW 0
#else
#define HERMES_PARSE_FLOW 1
#endif
#endif

#if !defined(HERMES_PARSE_TS)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_TS 0
#else
#define HERMES_PARSE_TS 1
#endif
#endif

#endif

// clang-format off

// Defines the start of range of nodes with the same base
#ifndef ESTREE_FIRST
#define ESTREE_FIRST(NAME, BASE)
#endif

// Defines the end of range of nodes with the same base
#ifndef ESTREE_LAST
#define ESTREE_LAST(NAME)
#endif

// Ignores the given field if it is "empty" (e.g. nullptr, empty list).
#ifndef ESTREE_IGNORE_IF_EMPTY
#define ESTREE_IGNORE_IF_EMPTY(NODE, FIELD)
#endif

ESTREE_NODE_0_ARGS(Empty, Base)
ESTREE_NODE_0_ARGS(Metadata, Base)

ESTREE_FIRST(FunctionLike, Base)
ESTREE_NODE_1_ARGS(Program, FunctionLike,
    NodeList, body, false)
ESTREE_NODE_8_ARGS(
    FunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    ArrowFunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, expression, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    FunctionDeclaration, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, predicate)

#if HERMES_PARSE_FLOW

ESTREE_NODE_5_ARGS(
    ComponentDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, rendersType)

ESTREE_NODE_5_ARGS(
    HookDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, returnType)

#endif

ESTREE_LAST(FunctionLike)

ESTREE_FIRST(Statement, Base)

ESTREE_FIRST(LoopStatement, Statement)
ESTREE_NODE_2_ARGS(
    WhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_2_ARGS(
    DoWhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_3_ARGS(
    ForInStatement,
    LoopStatement,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodePtr,
    body,
    false)
ESTREE_NODE_4_ARGS(
    ForOfStatement, LoopStatement,
    NodePtr, left, false,
    NodePtr, right, false,
    NodePtr, body, false,
    NodeBoolean, await, false)
ESTREE_NODE_4_ARGS(
    ForStatement,
    LoopStatement,
    NodePtr,
    init,
    true,
    NodePtr,
    test,
    true,
    NodePtr,
    update,
    true,
    NodePtr,
    body,
    false)
ESTREE_LAST(LoopStatement)

ESTREE_NODE_0_ARGS(DebuggerStatement, Statement)
ESTREE_NODE_0_ARGS(EmptyStatement, Statement)
ESTREE_NODE_1_ARGS(BlockStatement, Statement, NodeList, body, false)
ESTREE_NODE_1_ARGS(BreakStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ContinueStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ThrowStatement, Statement, NodePtr, argument, false)
ESTREE_NODE_1_ARGS(ReturnStatement, Statement, NodePtr, argument, true)
ESTREE_NODE_2_ARGS(
    WithStatement,
    Statement,
    NodePtr,
    object,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    SwitchStatement,
    Statement,
    NodePtr,
    discriminant,
    false,
    NodeList,
    cases,
    false)

ESTREE_NODE_2_ARGS(
    LabeledStatement,
    Statement,
    NodePtr,
    label,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    ExpressionStatement,
    Statement,
    NodePtr,
    expression,
    false,
    NodeString,
    directive,
    true)

ESTREE_NODE_3_ARGS(
    TryStatement,
    Statement,
    NodePtr,
    block,
    false,
    NodePtr,
    handler,
    true,
    NodePtr,
    finalizer,
    true)

ESTREE_NODE_3_ARGS(
    IfStatement,
    Statement,
    NodePtr,
    test,
    false,
    NodePtr,
    consequent,
    false,
    NodePtr,
    alternate,
    true)

ESTREE_LAST(Statement)

ESTREE_NODE_0_ARGS(NullLiteral, Base)
ESTREE_NODE_1_ARGS(BooleanLiteral, Base, NodeBoolean, value, false)
ESTREE_NODE_1_ARGS(StringLiteral, Base, NodeString, value, false)
ESTREE_NODE_1_ARGS(NumericLiteral, Base, NodeNumber, value, false)
ESTREE_NODE_2_ARGS(
    RegExpLiteral,
    Base,
    NodeLabel,
    pattern,
    false,
    NodeLabel,
    flags,
    false)
ESTREE_NODE_1_ARGS(
    BigIntLiteral, Base,
    NodeLabel, bigint, false)

ESTREE_NODE_0_ARGS(ThisExpression, Base)
ESTREE_NODE_0_ARGS(Super, Base)
ESTREE_NODE_1_ARGS(SequenceExpression, Base, NodeList, expressions, false)
ESTREE_NODE_1_ARGS(ObjectExpression, Base, NodeList, properties, false)
ESTREE_NODE_2_ARGS(ArrayExpression, Base,
    NodeList, elements, false,
    NodeBoolean, trailingComma, false)

ESTREE_NODE_1_ARGS(
    SpreadElement, Base,
    NodePtr, argument, false)

ESTREE_NODE_3_ARGS(
    NewExpression, Base,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(NewExpression, typeArguments)
ESTREE_NODE_2_ARGS(
    YieldExpression, Base,
    NodePtr, argument, true,
    NodeBoolean, delegate, true)
ESTREE_NODE_1_ARGS(
    AwaitExpression, Base,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    ImportExpression, Base,
    NodePtr, source, false,
    NodePtr, attributes, true)

ESTREE_FIRST(CallExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    CallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(CallExpression, typeArguments)

ESTREE_NODE_4_ARGS(
    OptionalCallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(OptionalCallExpression, typeArguments)
ESTREE_LAST(CallExpressionLike)

ESTREE_NODE_3_ARGS(
    AssignmentExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false)

ESTREE_NODE_3_ARGS(
    UnaryExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_NODE_3_ARGS(
    UpdateExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_FIRST(MemberExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    MemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false)

ESTREE_NODE_4_ARGS(
    OptionalMemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false,
    NodeBoolean, optional, false)
ESTREE_LAST(MemberExpressionLike)

ESTREE_NODE_3_ARGS(
    LogicalExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_3_ARGS(
    ConditionalExpression,
    Base,
    NodePtr,
    test,
    false,
    NodePtr,
    alternate,
    false,
    NodePtr,
    consequent,
    false)

ESTREE_NODE_3_ARGS(
    BinaryExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_1_ARGS(Directive, Base, NodePtr, value, false)
ESTREE_NODE_1_ARGS(DirectiveLiteral, Base, NodeString, value, false)

ESTREE_NODE_3_ARGS(
    Identifier, Base,
    NodeLabel, name, false,
    NodePtr, typeAnnotation, true,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(Identifier, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(Identifier, optional)

ESTREE_NODE_1_ARGS(
    PrivateName, Base,
    NodePtr, id, false)

ESTREE_NODE_2_ARGS(
    MetaProperty,
    Base,
    NodePtr,
    meta,
    false,
    NodePtr,
    property,
    false)

ESTREE_NODE_2_ARGS(
    SwitchCase,
    Base,
    NodePtr,
    test,
    true,
    NodeList,
    consequent,
    false)

ESTREE_NODE_2_ARGS(
    CatchClause,
    Base,
    NodePtr,
    param,
    true,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclarator,
    Base,
    NodePtr,
    init,
    true,
    NodePtr,
    id,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclaration,
    Base,
    NodeLabel,
    kind,
    false,
    NodeList,
    declarations,
    false)

ESTREE_NODE_2_ARGS(TemplateLiteral, Base,
                   NodeList, quasis, false,
                   NodeList, expressions, false)

ESTREE_NODE_2_ARGS(TaggedTemplateExpression, Base,
                   NodePtr, tag, false,
                   NodePtr, quasi, false)

// In ESTree, it is defined as {tail : boolean,
//                              value : {cooked : string, raw : string}},
// we flatten the value field.
// If the template literal is tagged and the text has an invalid escape,
// cooked will be null.
ESTREE_NODE_3_ARGS(TemplateElement, Base,
                   NodeBoolean, tail, false,
                   NodeString, cooked, true,
                   NodeLabel, raw, false)

ESTREE_NODE_6_ARGS(
    Property, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, method, false,
    NodeBoolean, shorthand, false)

ESTREE_NODE_7_ARGS(
    ClassDeclaration, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, implements)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, decorators)

ESTREE_NODE_7_ARGS(
    ClassExpression, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, implements)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, decorators)

ESTREE_NODE_1_ARGS(
    ClassBody, Base,
    NodeList, body, false)

ESTREE_NODE_9_ARGS(
    ClassProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, computed, false,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, tsModifiers)

ESTREE_NODE_8_ARGS(
    ClassPrivateProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, tsModifiers)

ESTREE_NODE_5_ARGS(
    MethodDefinition, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, static, false)

// Imports ========================================

ESTREE_NODE_4_ARGS(
    ImportDeclaration, Base,
    NodeList, specifiers, false,
    NodePtr, source, false,
    NodeList, assertions, true,
    NodeLabel, importKind, false)

ESTREE_NODE_3_ARGS(
    ImportSpecifier, Base,
    NodePtr, imported, false,
    NodePtr, local, false,
    NodeLabel, importKind, false)
ESTREE_NODE_1_ARGS(
    ImportDefaultSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ImportNamespaceSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_2_ARGS(
    ImportAttribute, Base,
    NodePtr, key, false,
    NodePtr, value, false)


// ================================================

// Exports ========================================

ESTREE_NODE_4_ARGS(
    ExportNamedDeclaration, Base,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeLabel, exportKind, false)

ESTREE_NODE_2_ARGS(
    ExportSpecifier, Base,
    NodePtr, exported, false,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ExportNamespaceSpecifier, Base,
    NodePtr, exported, false)
ESTREE_NODE_1_ARGS(
    ExportDefaultDeclaration, Base,
    NodePtr, declaration, false)
ESTREE_NODE_2_ARGS(
    ExportAllDeclaration, Base,
    NodePtr, source, false,
    NodeLabel, exportKind, false)

// ================================================

// Patterns =======================================
ESTREE_FIRST(Pattern, Base)

ESTREE_NODE_2_ARGS(
    ObjectPattern, Pattern,
    NodeList, properties, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ObjectPattern, typeAnnotation)

ESTREE_NODE_2_ARGS(
    ArrayPattern, Pattern,
    NodeList, elements, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ArrayPattern, typeAnnotation)

ESTREE_NODE_1_ARGS(
    RestElement, Pattern,
    NodePtr, argument, false)

ESTREE_NODE_2_ARGS(
    AssignmentPattern, Pattern,
    NodePtr, left, false,          // Pattern
    NodePtr, right, false)         // Expression

ESTREE_LAST(Pattern)
// ================================================

// JSX ============================================

#if HERMES_PARSE_JSX

ESTREE_FIRST(JSX, Base)

ESTREE_NODE_1_ARGS(
    JSXIdentifier, JSX,
    NodeLabel, name, false)
ESTREE_NODE_2_ARGS(
    JSXMemberExpression, JSX,
    NodePtr, object, false,
    NodePtr, property, false)
ESTREE_NODE_2_ARGS(
    JSXNamespacedName, JSX,
    NodePtr, namespace, false,
    NodePtr, name, false)

ESTREE_NODE_0_ARGS(
    JSXEmptyExpression, JSX)
ESTREE_NODE_1_ARGS(
    JSXExpressionContainer, JSX,
    NodePtr, expression, false)
ESTREE_NODE_1_ARGS(
    JSXSpreadChild, JSX,
    NodePtr, expression, false)

ESTREE_NODE_4_ARGS(
    JSXOpeningElement, JSX,
    NodePtr, name, false,
    NodeList, attributes, false,
    NodeBoolean, selfClosing, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(JSXOpeningElement, typeArguments)
ESTREE_NODE_1_ARGS(
    JSXClosingElement, JSX,
    NodePtr, name, false)

ESTREE_NODE_2_ARGS(
    JSXAttribute, JSX,
    NodePtr, name, false,
    NodePtr, value, true)
ESTREE_NODE_1_ARGS(
    JSXSpreadAttribute, JSX,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    JSXStringLiteral, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_2_ARGS(
    JSXText, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_3_ARGS(
    JSXElement, JSX,
    NodePtr, openingElement, false,
    NodeList, children, false,
    NodePtr, closingElement, true)

ESTREE_NODE_3_ARGS(
    JSXFragment, JSX,
    NodePtr, openingFragment, false,
    NodeList, children, false,
    NodePtr, closingFragment, false)
ESTREE_NODE_0_ARGS(
    JSXOpeningFragment, JSX)
ESTREE_NODE_0_ARGS(
    JSXClosingFragment, JSX)

ESTREE_LAST(JSX)

#endif

// ================================================

// Types ==========================================

#if HERMES_PARSE_FLOW

ESTREE_FIRST(Flow, Base)

ESTREE_NODE_0_ARGS(ExistsTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(EmptyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(StringTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(NumberTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    StringLiteralTypeAnnotation, Flow,
    NodeString, value, false,
    NodeString, raw, false)
ESTREE_NODE_2_ARGS(
    NumberLiteralTypeAnnotation, Flow,
    NodeNumber, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_1_ARGS(
    BigIntLiteralTypeAnnotation, Flow,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(BooleanTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    BooleanLiteralTypeAnnotation, Flow,
    NodeBoolean, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(NullLiteralTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(SymbolTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(AnyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(MixedTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(BigIntTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(VoidTypeAnnotation, Flow)
ESTREE_NODE_5_ARGS(
    FunctionTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, this, true,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_4_ARGS(
    HookTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    FunctionTypeParam, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ComponentTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_3_ARGS(
    ComponentTypeParameter, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_1_ARGS(
    NullableTypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TypeofTypeAnnotation, Flow,
    NodePtr, argument, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(TypeofTypeAnnotation, typeArguments)
ESTREE_NODE_1_ARGS(
    KeyofTypeAnnotation, Flow,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    TypeOperator, Flow,
    NodeLabel, operator, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeofIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TupleTypeAnnotation, Flow,
    NodeList, types, false,
    NodeBoolean, inexact, false)
ESTREE_NODE_2_ARGS(
    TupleTypeSpreadElement, Flow,
    NodePtr, label, true,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_4_ARGS(
    TupleTypeLabeledElement, Flow,
    NodePtr, label, false,
    NodePtr, elementType, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true)
ESTREE_NODE_1_ARGS(
    ArrayTypeAnnotation, Flow,
    NodePtr, elementType, false)
ESTREE_NODE_1_ARGS(
    InferTypeAnnotation, Flow,
    NodePtr, typeParameter, false)
ESTREE_NODE_1_ARGS(
    UnionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    IntersectionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_2_ARGS(
    GenericTypeAnnotation, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    IndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_3_ARGS(
    OptionalIndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ConditionalTypeAnnotation, Flow,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)
ESTREE_NODE_3_ARGS(
    TypePredicate, Flow,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, true,
    NodeString, kind, true)

ESTREE_NODE_2_ARGS(
    InterfaceTypeAnnotation, Flow,
    NodeList, extends, false,
    NodePtr, body, true)

ESTREE_NODE_3_ARGS(
    TypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    OpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, false,
    NodePtr, supertype, true)

ESTREE_NODE_4_ARGS(
    InterfaceDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    DeclareTypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    DeclareOpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, true,
    NodePtr, supertype, true)
ESTREE_NODE_4_ARGS(
    DeclareInterface, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)
ESTREE_NODE_6_ARGS(
    DeclareClass, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodeList, implements, false,
    NodeList, mixins, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareFunction, Flow,
    NodePtr, id, false,
    NodePtr, predicate, true)
ESTREE_NODE_1_ARGS(
    DeclareHook, Flow,
    NodePtr, id, false)
ESTREE_NODE_5_ARGS(
    DeclareComponent, Flow,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_2_ARGS(
    DeclareVariable, Flow,
    NodePtr, id, false,
    NodeLabel, kind, false)
ESTREE_NODE_2_ARGS(
    DeclareEnum, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_4_ARGS(
    DeclareExportDeclaration, Flow,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeBoolean, default, false)
ESTREE_NODE_1_ARGS(
    DeclareExportAllDeclaration, Flow,
    NodePtr, source, false)
ESTREE_NODE_2_ARGS(
    DeclareModule, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareNamespace, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    DeclareModuleExports, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_2_ARGS(
    InterfaceExtends, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_2_ARGS(
    ClassImplements, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_1_ARGS(
    TypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_6_ARGS(
    ObjectTypeAnnotation, Flow,
    NodeList, properties, false,
    NodeList, indexers, false,
    NodeList, callProperties, false,
    NodeList, internalSlots, false,
    NodeBoolean, inexact, false,
    NodeBoolean, exact, false)
ESTREE_NODE_8_ARGS(
    ObjectTypeProperty, Flow,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, method, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, proto, false,
    NodePtr, variance, true,
    NodeLabel, kind, false)
ESTREE_NODE_1_ARGS(
    ObjectTypeSpreadProperty, Flow,
    NodePtr, argument, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeInternalSlot, Flow,
    NodePtr, id, false,
    NodePtr, value, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, method, false)
ESTREE_NODE_2_ARGS(
    ObjectTypeCallProperty, Flow,
    NodePtr, value, false,
    NodeBoolean, static, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeIndexer, Flow,
    NodePtr, id, true,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, static, false,
    NodePtr, variance, true)
ESTREE_NODE_5_ARGS(
    ObjectTypeMappedTypeProperty, Flow,
    NodePtr, keyTparam, false,
    NodePtr, propType, false,
    NodePtr, sourceType, false,
    NodePtr, variance, true,
    NodeString, optional, true)

ESTREE_NODE_1_ARGS(
    Variance, Flow,
    NodeLabel, kind, false)

ESTREE_NODE_1_ARGS(
    TypeParameterDeclaration, Flow,
    NodeList, params, false)
ESTREE_NODE_5_ARGS(
    TypeParameter, Flow,
    NodeLabel, name, false,
    NodePtr, bound, true,
    NodePtr, variance, true,
    NodePtr, default, true,
    NodeBoolean, usesExtendsBound, false)
ESTREE_IGNORE_IF_EMPTY(TypeParameter, usesExtendsBound)
ESTREE_NODE_1_ARGS(
    TypeParameterInstantiation, Flow,
    NodeList, params, false)

ESTREE_NODE_2_ARGS(
    TypeCastExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    AsExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_1_ARGS(
    AsConstExpression, Flow,
    NodePtr, expression, false)

ESTREE_NODE_0_ARGS(InferredPredicate, Flow)
ESTREE_NODE_1_ARGS(
    DeclaredPredicate, Flow,
    NodePtr, value, false)

ESTREE_NODE_2_ARGS(
    EnumDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    EnumStringBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumNumberBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBigIntBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBooleanBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_2_ARGS(
    EnumSymbolBody, Flow,
    NodeList, members, false,
    NodeBoolean, hasUnknownMembers, false)

ESTREE_NODE_1_ARGS(
    EnumDefaultedMember, Flow,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    EnumStringMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumNumberMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBigIntMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBooleanMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_3_ARGS(
    ComponentParameter, Flow,
    NodePtr, name, false,
    NodePtr, local, false,
    NodeBoolean, shorthand, false)

ESTREE_LAST(Flow)

#endif

#if HERMES_PARSE_TS

ESTREE_FIRST(TS, Base)

ESTREE_NODE_1_ARGS(
    TSTypeAnnotation, TS,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_0_ARGS(TSAnyKeyword, TS)
ESTREE_NODE_0_ARGS(TSNumberKeyword, TS)
ESTREE_NODE_0_ARGS(TSBooleanKeyword, TS)
ESTREE_NODE_0_ARGS(TSStringKeyword, TS)
ESTREE_NODE_0_ARGS(TSSymbolKeyword, TS)
ESTREE_NODE_0_ARGS(TSVoidKeyword, TS)
ESTREE_NODE_0_ARGS(TSUndefinedKeyword, TS)
ESTREE_NODE_0_ARGS(TSUnknownKeyword, TS)
ESTREE_NODE_0_ARGS(TSNeverKeyword, TS)
ESTREE_NODE_0_ARGS(TSBigIntKeyword, TS)
ESTREE_NODE_0_ARGS(TSThisType, TS)
ESTREE_NODE_1_ARGS(
    TSLiteralType, TS,
    NodePtr, literal, false)
ESTREE_NODE_2_ARGS(
    TSIndexedAccessType, TS,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_1_ARGS(
    TSArrayType, TS,
    NodePtr, elementType, false)
ESTREE_NODE_2_ARGS(
    TSTypeReference, TS,
    NodePtr, typeName, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSQualifiedName, TS,
    NodePtr, left, false,
    NodePtr, right, true)

ESTREE_NODE_3_ARGS(
    TSFunctionType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    TSConstructorType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSTypePredicate, TS,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_1_ARGS(
    TSTupleType, TS,
    NodeList, elementTypes, false)

ESTREE_NODE_2_ARGS(
    TSTypeAssertion, TS,
    NodePtr, typeAnnotation, false,
    NodePtr, expression, false)
ESTREE_NODE_2_ARGS(
    TSAsExpression, TS,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_5_ARGS(
    TSParameterProperty, TS,
    NodePtr, parameter, false,
    NodeLabel, accessibility, true,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)

ESTREE_NODE_3_ARGS(
    TSTypeAliasDeclaration, TS,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_4_ARGS(
    TSInterfaceDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false,
    NodeList, extends, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSInterfaceHeritage, TS,
    NodePtr, expression, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_1_ARGS(
    TSInterfaceBody, TS,
    NodeList, body, false)

ESTREE_NODE_2_ARGS(
    TSEnumDeclaration, TS,
    NodePtr, id, false,
    NodeList, members, false)
ESTREE_NODE_2_ARGS(
    TSEnumMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_2_ARGS(
    TSModuleDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    TSModuleBlock, TS,
    NodeList, body, false)
ESTREE_NODE_2_ARGS(
    TSModuleMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterDeclaration, TS,
    NodeList, params, false)
ESTREE_NODE_3_ARGS(
    TSTypeParameter, TS,
    NodePtr, name, false,
    NodePtr, constraint, true,
    NodePtr, default, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterInstantiation, TS,
    NodeList, params, false)

ESTREE_NODE_1_ARGS(
    TSUnionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSIntersectionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSTypeQuery, TS,
    NodePtr, exprName, false)
ESTREE_NODE_4_ARGS(
    TSConditionalType, TS,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)

ESTREE_NODE_1_ARGS(
    TSTypeLiteral, TS,
    NodeList, members, false)
ESTREE_NODE_8_ARGS(
    TSPropertySignature, TS,
    NodePtr, key, false,
    NodePtr, typeAnnotation, true,
    NodePtr, initializer, true,
    NodeBoolean, optional, false,
    NodeBoolean, computed, false,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)
ESTREE_NODE_4_ARGS(
    TSMethodSignature, TS,
    NodePtr, key, false,
    NodeList, params, false,
    NodePtr, returnType, true,
    NodeBoolean, computed, false)
ESTREE_NODE_2_ARGS(
    TSIndexSignature, TS,
    NodeList, parameters, false,
    NodePtr, typeAnnotation, true)
ESTREE_NODE_2_ARGS(
    TSCallSignatureDeclaration, TS,
    NodeList, params, false,
    NodePtr, returnType, true)

ESTREE_NODE_2_ARGS(
    TSModifiers, TS,
    NodeLabel, accessibility, false,
    NodeBoolean, readonly, false)

ESTREE_LAST(TS)

#endif

// ================================================

#ifndef ESTREE_DEFINE_COVER_NODES

ESTREE_FIRST(Cover, Base)

// CoverParenthesizedExpressionAndArrowParameterList: "(" ")"
ESTREE_NODE_0_ARGS(CoverEmptyArgs, Cover)

// CoverParenthesizedExpressionAndArrowParameterList:
//      "(" Expression "," ")"
// This is the dummy "empty expression" for the last comma inside a
// SequenceExpression.
ESTREE_NODE_0_ARGS(CoverTrailingComma, Cover)

// CoverInitializer
// This is used for destructuring object assignment with initializers. It
// will be the value node of a Property.
ESTREE_NODE_1_ARGS(
    CoverInitializer, Cover,
    NodePtr, init, false)

// CoverRestElement
// This is used for parsing "...elem" in "()" and in SequenceExpression, so it
// can later be reparsed as an arrow function rest parameter. "rest" will point
// to the actual RestElement.
ESTREE_NODE_1_ARGS(
    CoverRestElement, Cover,
    NodePtr, rest, false)

// CoverTypedIdentifier
// This is used for parsing "ident: type" as either a type cast expression
// or a typed parameter in the parameters list of an arrow function.
// 'left' is the identifier which is typed.
// 'right' is the type which is either the cast target or the type annotation,
//   which may be null if the identifier was simply given a '?' and no ':'
//   with a type annotation.
ESTREE_NODE_3_ARGS(
    CoverTypedIdentifier, Cover,
    NodePtr, left, false,
    NodePtr, right, true,
    NodeBoolean, optional, false)

ESTREE_LAST(Cover)

#endif

#undef ESTREE_FIRST
#undef ESTREE_LAST
#undef ESTREE_WRAP
#undef ESTREE_IGNORE_IF_EMPTY

#undef ESTREE_NODE_0_ARGS
#undef ESTREE_NODE_1_ARGS
#undef ESTREE_NODE_2_ARGS
#undef ESTREE_NODE_3_ARGS
#undef ESTREE_NODE_4_ARGS
#undef ESTREE_NODE_5_ARGS
#undef ESTREE_NODE_6_ARGS
#undef ESTREE_NODE_7_ARGS
#undef ESTREE_NODE_8_ARGS
#undef ESTREE_NODE_9_ARGS
};

/// This is the base class of all ESTree nodes.
class Node : public llvh::ilist_node<Node> {
  Node(const Node &) = delete;
  void operator=(const Node &) = delete;

  NodeKind kind_;

  /// How many parens this node was surrounded by.
  /// This value can be 0, 1 and 2 (indicating 2 or more).
  unsigned parens_ = 0;

  SMRange sourceRange_{};
  SMLoc debugLoc_{};

 public:
  explicit Node(NodeKind kind) : kind_(kind) {}

  void setSourceRange(SMRange rng) {
    sourceRange_ = rng;
  }
  SMRange getSourceRange() const {
    return sourceRange_;
  }
  void setStartLoc(SMLoc loc) {
    sourceRange_.Start = loc;
  }
  SMLoc getStartLoc() const {
    return sourceRange_.Start;
  }
  void setEndLoc(SMLoc loc) {
    sourceRange_.End = loc;
  }
  SMLoc getEndLoc() const {
    return sourceRange_.End;
  }
  void setDebugLoc(SMLoc loc) {
    debugLoc_ = loc;
  }
  SMLoc getDebugLoc() const {
    return debugLoc_;
  }

  unsigned getParens() const {
    return parens_;
  }
  void incParens() {
    parens_ = parens_ < 2 ? parens_ + 1 : 2;
  }
  void clearParens() {
    parens_ = 0;
  }

  /// Copy all location data from a different node.
  void copyLocationFrom(const Node *src) {
    setSourceRange(src->getSourceRange());
    setDebugLoc(src->getDebugLoc());
  }

  /// \returns the textual name of the node.
  llvh::StringRef getNodeName() {
    switch (getKind()) {
      default:
        llvm_unreachable("invalid node kind");

#define ESTREE_NODE_0_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_1_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_2_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_3_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_4_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_5_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_6_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_7_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_8_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;
#define ESTREE_NODE_9_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return #NAME;

#ifndef HERMES_PARSER_CONFIG_H
#define HERMES_PARSER_CONFIG_H

#if !defined(HERMES_PARSE_JSX)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_JSX 0
#else
#define HERMES_PARSE_JSX 1
#endif
#endif

#if !defined(HERMES_PARSE_FLOW)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_FLOW 0
#else
#define HERMES_PARSE_FLOW 1
#endif
#endif

#if !defined(HERMES_PARSE_TS)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_TS 0
#else
#define HERMES_PARSE_TS 1
#endif
#endif

#endif

// clang-format off

// Defines the start of range of nodes with the same base
#ifndef ESTREE_FIRST
#define ESTREE_FIRST(NAME, BASE)
#endif

// Defines the end of range of nodes with the same base
#ifndef ESTREE_LAST
#define ESTREE_LAST(NAME)
#endif

// Ignores the given field if it is "empty" (e.g. nullptr, empty list).
#ifndef ESTREE_IGNORE_IF_EMPTY
#define ESTREE_IGNORE_IF_EMPTY(NODE, FIELD)
#endif

ESTREE_NODE_0_ARGS(Empty, Base)
ESTREE_NODE_0_ARGS(Metadata, Base)

ESTREE_FIRST(FunctionLike, Base)
ESTREE_NODE_1_ARGS(Program, FunctionLike,
    NodeList, body, false)
ESTREE_NODE_8_ARGS(
    FunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    ArrowFunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, expression, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    FunctionDeclaration, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, predicate)

#if HERMES_PARSE_FLOW

ESTREE_NODE_5_ARGS(
    ComponentDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, rendersType)

ESTREE_NODE_5_ARGS(
    HookDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, returnType)

#endif

ESTREE_LAST(FunctionLike)

ESTREE_FIRST(Statement, Base)

ESTREE_FIRST(LoopStatement, Statement)
ESTREE_NODE_2_ARGS(
    WhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_2_ARGS(
    DoWhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_3_ARGS(
    ForInStatement,
    LoopStatement,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodePtr,
    body,
    false)
ESTREE_NODE_4_ARGS(
    ForOfStatement, LoopStatement,
    NodePtr, left, false,
    NodePtr, right, false,
    NodePtr, body, false,
    NodeBoolean, await, false)
ESTREE_NODE_4_ARGS(
    ForStatement,
    LoopStatement,
    NodePtr,
    init,
    true,
    NodePtr,
    test,
    true,
    NodePtr,
    update,
    true,
    NodePtr,
    body,
    false)
ESTREE_LAST(LoopStatement)

ESTREE_NODE_0_ARGS(DebuggerStatement, Statement)
ESTREE_NODE_0_ARGS(EmptyStatement, Statement)
ESTREE_NODE_1_ARGS(BlockStatement, Statement, NodeList, body, false)
ESTREE_NODE_1_ARGS(BreakStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ContinueStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ThrowStatement, Statement, NodePtr, argument, false)
ESTREE_NODE_1_ARGS(ReturnStatement, Statement, NodePtr, argument, true)
ESTREE_NODE_2_ARGS(
    WithStatement,
    Statement,
    NodePtr,
    object,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    SwitchStatement,
    Statement,
    NodePtr,
    discriminant,
    false,
    NodeList,
    cases,
    false)

ESTREE_NODE_2_ARGS(
    LabeledStatement,
    Statement,
    NodePtr,
    label,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    ExpressionStatement,
    Statement,
    NodePtr,
    expression,
    false,
    NodeString,
    directive,
    true)

ESTREE_NODE_3_ARGS(
    TryStatement,
    Statement,
    NodePtr,
    block,
    false,
    NodePtr,
    handler,
    true,
    NodePtr,
    finalizer,
    true)

ESTREE_NODE_3_ARGS(
    IfStatement,
    Statement,
    NodePtr,
    test,
    false,
    NodePtr,
    consequent,
    false,
    NodePtr,
    alternate,
    true)

ESTREE_LAST(Statement)

ESTREE_NODE_0_ARGS(NullLiteral, Base)
ESTREE_NODE_1_ARGS(BooleanLiteral, Base, NodeBoolean, value, false)
ESTREE_NODE_1_ARGS(StringLiteral, Base, NodeString, value, false)
ESTREE_NODE_1_ARGS(NumericLiteral, Base, NodeNumber, value, false)
ESTREE_NODE_2_ARGS(
    RegExpLiteral,
    Base,
    NodeLabel,
    pattern,
    false,
    NodeLabel,
    flags,
    false)
ESTREE_NODE_1_ARGS(
    BigIntLiteral, Base,
    NodeLabel, bigint, false)

ESTREE_NODE_0_ARGS(ThisExpression, Base)
ESTREE_NODE_0_ARGS(Super, Base)
ESTREE_NODE_1_ARGS(SequenceExpression, Base, NodeList, expressions, false)
ESTREE_NODE_1_ARGS(ObjectExpression, Base, NodeList, properties, false)
ESTREE_NODE_2_ARGS(ArrayExpression, Base,
    NodeList, elements, false,
    NodeBoolean, trailingComma, false)

ESTREE_NODE_1_ARGS(
    SpreadElement, Base,
    NodePtr, argument, false)

ESTREE_NODE_3_ARGS(
    NewExpression, Base,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(NewExpression, typeArguments)
ESTREE_NODE_2_ARGS(
    YieldExpression, Base,
    NodePtr, argument, true,
    NodeBoolean, delegate, true)
ESTREE_NODE_1_ARGS(
    AwaitExpression, Base,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    ImportExpression, Base,
    NodePtr, source, false,
    NodePtr, attributes, true)

ESTREE_FIRST(CallExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    CallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(CallExpression, typeArguments)

ESTREE_NODE_4_ARGS(
    OptionalCallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(OptionalCallExpression, typeArguments)
ESTREE_LAST(CallExpressionLike)

ESTREE_NODE_3_ARGS(
    AssignmentExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false)

ESTREE_NODE_3_ARGS(
    UnaryExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_NODE_3_ARGS(
    UpdateExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_FIRST(MemberExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    MemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false)

ESTREE_NODE_4_ARGS(
    OptionalMemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false,
    NodeBoolean, optional, false)
ESTREE_LAST(MemberExpressionLike)

ESTREE_NODE_3_ARGS(
    LogicalExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_3_ARGS(
    ConditionalExpression,
    Base,
    NodePtr,
    test,
    false,
    NodePtr,
    alternate,
    false,
    NodePtr,
    consequent,
    false)

ESTREE_NODE_3_ARGS(
    BinaryExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_1_ARGS(Directive, Base, NodePtr, value, false)
ESTREE_NODE_1_ARGS(DirectiveLiteral, Base, NodeString, value, false)

ESTREE_NODE_3_ARGS(
    Identifier, Base,
    NodeLabel, name, false,
    NodePtr, typeAnnotation, true,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(Identifier, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(Identifier, optional)

ESTREE_NODE_1_ARGS(
    PrivateName, Base,
    NodePtr, id, false)

ESTREE_NODE_2_ARGS(
    MetaProperty,
    Base,
    NodePtr,
    meta,
    false,
    NodePtr,
    property,
    false)

ESTREE_NODE_2_ARGS(
    SwitchCase,
    Base,
    NodePtr,
    test,
    true,
    NodeList,
    consequent,
    false)

ESTREE_NODE_2_ARGS(
    CatchClause,
    Base,
    NodePtr,
    param,
    true,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclarator,
    Base,
    NodePtr,
    init,
    true,
    NodePtr,
    id,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclaration,
    Base,
    NodeLabel,
    kind,
    false,
    NodeList,
    declarations,
    false)

ESTREE_NODE_2_ARGS(TemplateLiteral, Base,
                   NodeList, quasis, false,
                   NodeList, expressions, false)

ESTREE_NODE_2_ARGS(TaggedTemplateExpression, Base,
                   NodePtr, tag, false,
                   NodePtr, quasi, false)

// In ESTree, it is defined as {tail : boolean,
//                              value : {cooked : string, raw : string}},
// we flatten the value field.
// If the template literal is tagged and the text has an invalid escape,
// cooked will be null.
ESTREE_NODE_3_ARGS(TemplateElement, Base,
                   NodeBoolean, tail, false,
                   NodeString, cooked, true,
                   NodeLabel, raw, false)

ESTREE_NODE_6_ARGS(
    Property, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, method, false,
    NodeBoolean, shorthand, false)

ESTREE_NODE_7_ARGS(
    ClassDeclaration, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, implements)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, decorators)

ESTREE_NODE_7_ARGS(
    ClassExpression, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, implements)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, decorators)

ESTREE_NODE_1_ARGS(
    ClassBody, Base,
    NodeList, body, false)

ESTREE_NODE_9_ARGS(
    ClassProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, computed, false,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, tsModifiers)

ESTREE_NODE_8_ARGS(
    ClassPrivateProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, tsModifiers)

ESTREE_NODE_5_ARGS(
    MethodDefinition, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, static, false)

// Imports ========================================

ESTREE_NODE_4_ARGS(
    ImportDeclaration, Base,
    NodeList, specifiers, false,
    NodePtr, source, false,
    NodeList, assertions, true,
    NodeLabel, importKind, false)

ESTREE_NODE_3_ARGS(
    ImportSpecifier, Base,
    NodePtr, imported, false,
    NodePtr, local, false,
    NodeLabel, importKind, false)
ESTREE_NODE_1_ARGS(
    ImportDefaultSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ImportNamespaceSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_2_ARGS(
    ImportAttribute, Base,
    NodePtr, key, false,
    NodePtr, value, false)


// ================================================

// Exports ========================================

ESTREE_NODE_4_ARGS(
    ExportNamedDeclaration, Base,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeLabel, exportKind, false)

ESTREE_NODE_2_ARGS(
    ExportSpecifier, Base,
    NodePtr, exported, false,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ExportNamespaceSpecifier, Base,
    NodePtr, exported, false)
ESTREE_NODE_1_ARGS(
    ExportDefaultDeclaration, Base,
    NodePtr, declaration, false)
ESTREE_NODE_2_ARGS(
    ExportAllDeclaration, Base,
    NodePtr, source, false,
    NodeLabel, exportKind, false)

// ================================================

// Patterns =======================================
ESTREE_FIRST(Pattern, Base)

ESTREE_NODE_2_ARGS(
    ObjectPattern, Pattern,
    NodeList, properties, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ObjectPattern, typeAnnotation)

ESTREE_NODE_2_ARGS(
    ArrayPattern, Pattern,
    NodeList, elements, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ArrayPattern, typeAnnotation)

ESTREE_NODE_1_ARGS(
    RestElement, Pattern,
    NodePtr, argument, false)

ESTREE_NODE_2_ARGS(
    AssignmentPattern, Pattern,
    NodePtr, left, false,          // Pattern
    NodePtr, right, false)         // Expression

ESTREE_LAST(Pattern)
// ================================================

// JSX ============================================

#if HERMES_PARSE_JSX

ESTREE_FIRST(JSX, Base)

ESTREE_NODE_1_ARGS(
    JSXIdentifier, JSX,
    NodeLabel, name, false)
ESTREE_NODE_2_ARGS(
    JSXMemberExpression, JSX,
    NodePtr, object, false,
    NodePtr, property, false)
ESTREE_NODE_2_ARGS(
    JSXNamespacedName, JSX,
    NodePtr, namespace, false,
    NodePtr, name, false)

ESTREE_NODE_0_ARGS(
    JSXEmptyExpression, JSX)
ESTREE_NODE_1_ARGS(
    JSXExpressionContainer, JSX,
    NodePtr, expression, false)
ESTREE_NODE_1_ARGS(
    JSXSpreadChild, JSX,
    NodePtr, expression, false)

ESTREE_NODE_4_ARGS(
    JSXOpeningElement, JSX,
    NodePtr, name, false,
    NodeList, attributes, false,
    NodeBoolean, selfClosing, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(JSXOpeningElement, typeArguments)
ESTREE_NODE_1_ARGS(
    JSXClosingElement, JSX,
    NodePtr, name, false)

ESTREE_NODE_2_ARGS(
    JSXAttribute, JSX,
    NodePtr, name, false,
    NodePtr, value, true)
ESTREE_NODE_1_ARGS(
    JSXSpreadAttribute, JSX,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    JSXStringLiteral, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_2_ARGS(
    JSXText, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_3_ARGS(
    JSXElement, JSX,
    NodePtr, openingElement, false,
    NodeList, children, false,
    NodePtr, closingElement, true)

ESTREE_NODE_3_ARGS(
    JSXFragment, JSX,
    NodePtr, openingFragment, false,
    NodeList, children, false,
    NodePtr, closingFragment, false)
ESTREE_NODE_0_ARGS(
    JSXOpeningFragment, JSX)
ESTREE_NODE_0_ARGS(
    JSXClosingFragment, JSX)

ESTREE_LAST(JSX)

#endif

// ================================================

// Types ==========================================

#if HERMES_PARSE_FLOW

ESTREE_FIRST(Flow, Base)

ESTREE_NODE_0_ARGS(ExistsTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(EmptyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(StringTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(NumberTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    StringLiteralTypeAnnotation, Flow,
    NodeString, value, false,
    NodeString, raw, false)
ESTREE_NODE_2_ARGS(
    NumberLiteralTypeAnnotation, Flow,
    NodeNumber, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_1_ARGS(
    BigIntLiteralTypeAnnotation, Flow,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(BooleanTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    BooleanLiteralTypeAnnotation, Flow,
    NodeBoolean, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(NullLiteralTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(SymbolTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(AnyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(MixedTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(BigIntTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(VoidTypeAnnotation, Flow)
ESTREE_NODE_5_ARGS(
    FunctionTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, this, true,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_4_ARGS(
    HookTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    FunctionTypeParam, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ComponentTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_3_ARGS(
    ComponentTypeParameter, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_1_ARGS(
    NullableTypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TypeofTypeAnnotation, Flow,
    NodePtr, argument, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(TypeofTypeAnnotation, typeArguments)
ESTREE_NODE_1_ARGS(
    KeyofTypeAnnotation, Flow,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    TypeOperator, Flow,
    NodeLabel, operator, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeofIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TupleTypeAnnotation, Flow,
    NodeList, types, false,
    NodeBoolean, inexact, false)
ESTREE_NODE_2_ARGS(
    TupleTypeSpreadElement, Flow,
    NodePtr, label, true,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_4_ARGS(
    TupleTypeLabeledElement, Flow,
    NodePtr, label, false,
    NodePtr, elementType, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true)
ESTREE_NODE_1_ARGS(
    ArrayTypeAnnotation, Flow,
    NodePtr, elementType, false)
ESTREE_NODE_1_ARGS(
    InferTypeAnnotation, Flow,
    NodePtr, typeParameter, false)
ESTREE_NODE_1_ARGS(
    UnionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    IntersectionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_2_ARGS(
    GenericTypeAnnotation, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    IndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_3_ARGS(
    OptionalIndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ConditionalTypeAnnotation, Flow,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)
ESTREE_NODE_3_ARGS(
    TypePredicate, Flow,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, true,
    NodeString, kind, true)

ESTREE_NODE_2_ARGS(
    InterfaceTypeAnnotation, Flow,
    NodeList, extends, false,
    NodePtr, body, true)

ESTREE_NODE_3_ARGS(
    TypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    OpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, false,
    NodePtr, supertype, true)

ESTREE_NODE_4_ARGS(
    InterfaceDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    DeclareTypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    DeclareOpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, true,
    NodePtr, supertype, true)
ESTREE_NODE_4_ARGS(
    DeclareInterface, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)
ESTREE_NODE_6_ARGS(
    DeclareClass, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodeList, implements, false,
    NodeList, mixins, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareFunction, Flow,
    NodePtr, id, false,
    NodePtr, predicate, true)
ESTREE_NODE_1_ARGS(
    DeclareHook, Flow,
    NodePtr, id, false)
ESTREE_NODE_5_ARGS(
    DeclareComponent, Flow,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_2_ARGS(
    DeclareVariable, Flow,
    NodePtr, id, false,
    NodeLabel, kind, false)
ESTREE_NODE_2_ARGS(
    DeclareEnum, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_4_ARGS(
    DeclareExportDeclaration, Flow,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeBoolean, default, false)
ESTREE_NODE_1_ARGS(
    DeclareExportAllDeclaration, Flow,
    NodePtr, source, false)
ESTREE_NODE_2_ARGS(
    DeclareModule, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareNamespace, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    DeclareModuleExports, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_2_ARGS(
    InterfaceExtends, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_2_ARGS(
    ClassImplements, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_1_ARGS(
    TypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_6_ARGS(
    ObjectTypeAnnotation, Flow,
    NodeList, properties, false,
    NodeList, indexers, false,
    NodeList, callProperties, false,
    NodeList, internalSlots, false,
    NodeBoolean, inexact, false,
    NodeBoolean, exact, false)
ESTREE_NODE_8_ARGS(
    ObjectTypeProperty, Flow,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, method, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, proto, false,
    NodePtr, variance, true,
    NodeLabel, kind, false)
ESTREE_NODE_1_ARGS(
    ObjectTypeSpreadProperty, Flow,
    NodePtr, argument, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeInternalSlot, Flow,
    NodePtr, id, false,
    NodePtr, value, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, method, false)
ESTREE_NODE_2_ARGS(
    ObjectTypeCallProperty, Flow,
    NodePtr, value, false,
    NodeBoolean, static, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeIndexer, Flow,
    NodePtr, id, true,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, static, false,
    NodePtr, variance, true)
ESTREE_NODE_5_ARGS(
    ObjectTypeMappedTypeProperty, Flow,
    NodePtr, keyTparam, false,
    NodePtr, propType, false,
    NodePtr, sourceType, false,
    NodePtr, variance, true,
    NodeString, optional, true)

ESTREE_NODE_1_ARGS(
    Variance, Flow,
    NodeLabel, kind, false)

ESTREE_NODE_1_ARGS(
    TypeParameterDeclaration, Flow,
    NodeList, params, false)
ESTREE_NODE_5_ARGS(
    TypeParameter, Flow,
    NodeLabel, name, false,
    NodePtr, bound, true,
    NodePtr, variance, true,
    NodePtr, default, true,
    NodeBoolean, usesExtendsBound, false)
ESTREE_IGNORE_IF_EMPTY(TypeParameter, usesExtendsBound)
ESTREE_NODE_1_ARGS(
    TypeParameterInstantiation, Flow,
    NodeList, params, false)

ESTREE_NODE_2_ARGS(
    TypeCastExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    AsExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_1_ARGS(
    AsConstExpression, Flow,
    NodePtr, expression, false)

ESTREE_NODE_0_ARGS(InferredPredicate, Flow)
ESTREE_NODE_1_ARGS(
    DeclaredPredicate, Flow,
    NodePtr, value, false)

ESTREE_NODE_2_ARGS(
    EnumDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    EnumStringBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumNumberBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBigIntBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBooleanBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_2_ARGS(
    EnumSymbolBody, Flow,
    NodeList, members, false,
    NodeBoolean, hasUnknownMembers, false)

ESTREE_NODE_1_ARGS(
    EnumDefaultedMember, Flow,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    EnumStringMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumNumberMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBigIntMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBooleanMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_3_ARGS(
    ComponentParameter, Flow,
    NodePtr, name, false,
    NodePtr, local, false,
    NodeBoolean, shorthand, false)

ESTREE_LAST(Flow)

#endif

#if HERMES_PARSE_TS

ESTREE_FIRST(TS, Base)

ESTREE_NODE_1_ARGS(
    TSTypeAnnotation, TS,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_0_ARGS(TSAnyKeyword, TS)
ESTREE_NODE_0_ARGS(TSNumberKeyword, TS)
ESTREE_NODE_0_ARGS(TSBooleanKeyword, TS)
ESTREE_NODE_0_ARGS(TSStringKeyword, TS)
ESTREE_NODE_0_ARGS(TSSymbolKeyword, TS)
ESTREE_NODE_0_ARGS(TSVoidKeyword, TS)
ESTREE_NODE_0_ARGS(TSUndefinedKeyword, TS)
ESTREE_NODE_0_ARGS(TSUnknownKeyword, TS)
ESTREE_NODE_0_ARGS(TSNeverKeyword, TS)
ESTREE_NODE_0_ARGS(TSBigIntKeyword, TS)
ESTREE_NODE_0_ARGS(TSThisType, TS)
ESTREE_NODE_1_ARGS(
    TSLiteralType, TS,
    NodePtr, literal, false)
ESTREE_NODE_2_ARGS(
    TSIndexedAccessType, TS,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_1_ARGS(
    TSArrayType, TS,
    NodePtr, elementType, false)
ESTREE_NODE_2_ARGS(
    TSTypeReference, TS,
    NodePtr, typeName, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSQualifiedName, TS,
    NodePtr, left, false,
    NodePtr, right, true)

ESTREE_NODE_3_ARGS(
    TSFunctionType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    TSConstructorType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSTypePredicate, TS,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_1_ARGS(
    TSTupleType, TS,
    NodeList, elementTypes, false)

ESTREE_NODE_2_ARGS(
    TSTypeAssertion, TS,
    NodePtr, typeAnnotation, false,
    NodePtr, expression, false)
ESTREE_NODE_2_ARGS(
    TSAsExpression, TS,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_5_ARGS(
    TSParameterProperty, TS,
    NodePtr, parameter, false,
    NodeLabel, accessibility, true,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)

ESTREE_NODE_3_ARGS(
    TSTypeAliasDeclaration, TS,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_4_ARGS(
    TSInterfaceDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false,
    NodeList, extends, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSInterfaceHeritage, TS,
    NodePtr, expression, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_1_ARGS(
    TSInterfaceBody, TS,
    NodeList, body, false)

ESTREE_NODE_2_ARGS(
    TSEnumDeclaration, TS,
    NodePtr, id, false,
    NodeList, members, false)
ESTREE_NODE_2_ARGS(
    TSEnumMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_2_ARGS(
    TSModuleDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    TSModuleBlock, TS,
    NodeList, body, false)
ESTREE_NODE_2_ARGS(
    TSModuleMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterDeclaration, TS,
    NodeList, params, false)
ESTREE_NODE_3_ARGS(
    TSTypeParameter, TS,
    NodePtr, name, false,
    NodePtr, constraint, true,
    NodePtr, default, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterInstantiation, TS,
    NodeList, params, false)

ESTREE_NODE_1_ARGS(
    TSUnionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSIntersectionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSTypeQuery, TS,
    NodePtr, exprName, false)
ESTREE_NODE_4_ARGS(
    TSConditionalType, TS,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)

ESTREE_NODE_1_ARGS(
    TSTypeLiteral, TS,
    NodeList, members, false)
ESTREE_NODE_8_ARGS(
    TSPropertySignature, TS,
    NodePtr, key, false,
    NodePtr, typeAnnotation, true,
    NodePtr, initializer, true,
    NodeBoolean, optional, false,
    NodeBoolean, computed, false,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)
ESTREE_NODE_4_ARGS(
    TSMethodSignature, TS,
    NodePtr, key, false,
    NodeList, params, false,
    NodePtr, returnType, true,
    NodeBoolean, computed, false)
ESTREE_NODE_2_ARGS(
    TSIndexSignature, TS,
    NodeList, parameters, false,
    NodePtr, typeAnnotation, true)
ESTREE_NODE_2_ARGS(
    TSCallSignatureDeclaration, TS,
    NodeList, params, false,
    NodePtr, returnType, true)

ESTREE_NODE_2_ARGS(
    TSModifiers, TS,
    NodeLabel, accessibility, false,
    NodeBoolean, readonly, false)

ESTREE_LAST(TS)

#endif

// ================================================

#ifndef ESTREE_DEFINE_COVER_NODES

ESTREE_FIRST(Cover, Base)

// CoverParenthesizedExpressionAndArrowParameterList: "(" ")"
ESTREE_NODE_0_ARGS(CoverEmptyArgs, Cover)

// CoverParenthesizedExpressionAndArrowParameterList:
//      "(" Expression "," ")"
// This is the dummy "empty expression" for the last comma inside a
// SequenceExpression.
ESTREE_NODE_0_ARGS(CoverTrailingComma, Cover)

// CoverInitializer
// This is used for destructuring object assignment with initializers. It
// will be the value node of a Property.
ESTREE_NODE_1_ARGS(
    CoverInitializer, Cover,
    NodePtr, init, false)

// CoverRestElement
// This is used for parsing "...elem" in "()" and in SequenceExpression, so it
// can later be reparsed as an arrow function rest parameter. "rest" will point
// to the actual RestElement.
ESTREE_NODE_1_ARGS(
    CoverRestElement, Cover,
    NodePtr, rest, false)

// CoverTypedIdentifier
// This is used for parsing "ident: type" as either a type cast expression
// or a typed parameter in the parameters list of an arrow function.
// 'left' is the identifier which is typed.
// 'right' is the type which is either the cast target or the type annotation,
//   which may be null if the identifier was simply given a '?' and no ':'
//   with a type annotation.
ESTREE_NODE_3_ARGS(
    CoverTypedIdentifier, Cover,
    NodePtr, left, false,
    NodePtr, right, true,
    NodeBoolean, optional, false)

ESTREE_LAST(Cover)

#endif

#undef ESTREE_FIRST
#undef ESTREE_LAST
#undef ESTREE_WRAP
#undef ESTREE_IGNORE_IF_EMPTY

#undef ESTREE_NODE_0_ARGS
#undef ESTREE_NODE_1_ARGS
#undef ESTREE_NODE_2_ARGS
#undef ESTREE_NODE_3_ARGS
#undef ESTREE_NODE_4_ARGS
#undef ESTREE_NODE_5_ARGS
#undef ESTREE_NODE_6_ARGS
#undef ESTREE_NODE_7_ARGS
#undef ESTREE_NODE_8_ARGS
#undef ESTREE_NODE_9_ARGS
    }
  }

  template <class Visitor>
  void visit(Visitor &V) {
    ESTreeVisit(V, this);
  }

  /// \returns the kind of the value.
  NodeKind getKind() const {
    return kind_;
  }
  static bool classof(const NodePtr) {
    return true;
  }

  // Allow allocation of AST nodes by using the Context allocator or by a
  // placement new.

  void *
  operator new(size_t size, Context &ctx, size_t alignment = alignof(double)) {
    return ctx.allocateNode(size, alignment);
  }
  void *operator new(size_t, void *mem) {
    return mem;
  }

  void operator delete(void *, const Context &, size_t) {}
  void operator delete(void *, size_t) {}

 private:
  // Make new/delete illegal for AST nodes.

  void *operator new(size_t) {
    llvm_unreachable("AST nodes cannot be allocated with regular new");
  }
  void operator delete(void *) {
    llvm_unreachable("AST nodes cannot be released with regular delete");
  }
};

// Skip labels.
template <class Visitor>
void ESTreeVisit(Visitor &V, const NodeLabel &label) {}
template <class Visitor>
void ESTreeVisit(Visitor &V, const NodeBoolean &label) {}
template <class Visitor>
void ESTreeVisit(Visitor &V, const NodeNumber &label) {}

// Visit all nodes in a list.
template <class Visitor>
void ESTreeVisit(Visitor &V, NodeList &Lst) {
  for (auto &Elem : Lst) {
    ESTreeVisit(V, &Elem);
  }
}

// Forward declarations of all nodes.
#define ESTREE_FIRST(NAME, ...) class NAME##Node;
#define ESTREE_NODE_0_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_1_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_2_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_3_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_4_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_5_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_6_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_7_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_8_ARGS(NAME, ...) class NAME##Node;
#define ESTREE_NODE_9_ARGS(NAME, ...) class NAME##Node;

#ifndef HERMES_PARSER_CONFIG_H
#define HERMES_PARSER_CONFIG_H

#if !defined(HERMES_PARSE_JSX)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_JSX 0
#else
#define HERMES_PARSE_JSX 1
#endif
#endif

#if !defined(HERMES_PARSE_FLOW)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_FLOW 0
#else
#define HERMES_PARSE_FLOW 1
#endif
#endif

#if !defined(HERMES_PARSE_TS)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_TS 0
#else
#define HERMES_PARSE_TS 1
#endif
#endif

#endif

// clang-format off

// Defines the start of range of nodes with the same base
#ifndef ESTREE_FIRST
#define ESTREE_FIRST(NAME, BASE)
#endif

// Defines the end of range of nodes with the same base
#ifndef ESTREE_LAST
#define ESTREE_LAST(NAME)
#endif

// Ignores the given field if it is "empty" (e.g. nullptr, empty list).
#ifndef ESTREE_IGNORE_IF_EMPTY
#define ESTREE_IGNORE_IF_EMPTY(NODE, FIELD)
#endif

ESTREE_NODE_0_ARGS(Empty, Base)
ESTREE_NODE_0_ARGS(Metadata, Base)

ESTREE_FIRST(FunctionLike, Base)
ESTREE_NODE_1_ARGS(Program, FunctionLike,
    NodeList, body, false)
ESTREE_NODE_8_ARGS(
    FunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    ArrowFunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, expression, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    FunctionDeclaration, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, predicate)

#if HERMES_PARSE_FLOW

ESTREE_NODE_5_ARGS(
    ComponentDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, rendersType)

ESTREE_NODE_5_ARGS(
    HookDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, returnType)

#endif

ESTREE_LAST(FunctionLike)

ESTREE_FIRST(Statement, Base)

ESTREE_FIRST(LoopStatement, Statement)
ESTREE_NODE_2_ARGS(
    WhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_2_ARGS(
    DoWhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_3_ARGS(
    ForInStatement,
    LoopStatement,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodePtr,
    body,
    false)
ESTREE_NODE_4_ARGS(
    ForOfStatement, LoopStatement,
    NodePtr, left, false,
    NodePtr, right, false,
    NodePtr, body, false,
    NodeBoolean, await, false)
ESTREE_NODE_4_ARGS(
    ForStatement,
    LoopStatement,
    NodePtr,
    init,
    true,
    NodePtr,
    test,
    true,
    NodePtr,
    update,
    true,
    NodePtr,
    body,
    false)
ESTREE_LAST(LoopStatement)

ESTREE_NODE_0_ARGS(DebuggerStatement, Statement)
ESTREE_NODE_0_ARGS(EmptyStatement, Statement)
ESTREE_NODE_1_ARGS(BlockStatement, Statement, NodeList, body, false)
ESTREE_NODE_1_ARGS(BreakStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ContinueStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ThrowStatement, Statement, NodePtr, argument, false)
ESTREE_NODE_1_ARGS(ReturnStatement, Statement, NodePtr, argument, true)
ESTREE_NODE_2_ARGS(
    WithStatement,
    Statement,
    NodePtr,
    object,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    SwitchStatement,
    Statement,
    NodePtr,
    discriminant,
    false,
    NodeList,
    cases,
    false)

ESTREE_NODE_2_ARGS(
    LabeledStatement,
    Statement,
    NodePtr,
    label,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    ExpressionStatement,
    Statement,
    NodePtr,
    expression,
    false,
    NodeString,
    directive,
    true)

ESTREE_NODE_3_ARGS(
    TryStatement,
    Statement,
    NodePtr,
    block,
    false,
    NodePtr,
    handler,
    true,
    NodePtr,
    finalizer,
    true)

ESTREE_NODE_3_ARGS(
    IfStatement,
    Statement,
    NodePtr,
    test,
    false,
    NodePtr,
    consequent,
    false,
    NodePtr,
    alternate,
    true)

ESTREE_LAST(Statement)

ESTREE_NODE_0_ARGS(NullLiteral, Base)
ESTREE_NODE_1_ARGS(BooleanLiteral, Base, NodeBoolean, value, false)
ESTREE_NODE_1_ARGS(StringLiteral, Base, NodeString, value, false)
ESTREE_NODE_1_ARGS(NumericLiteral, Base, NodeNumber, value, false)
ESTREE_NODE_2_ARGS(
    RegExpLiteral,
    Base,
    NodeLabel,
    pattern,
    false,
    NodeLabel,
    flags,
    false)
ESTREE_NODE_1_ARGS(
    BigIntLiteral, Base,
    NodeLabel, bigint, false)

ESTREE_NODE_0_ARGS(ThisExpression, Base)
ESTREE_NODE_0_ARGS(Super, Base)
ESTREE_NODE_1_ARGS(SequenceExpression, Base, NodeList, expressions, false)
ESTREE_NODE_1_ARGS(ObjectExpression, Base, NodeList, properties, false)
ESTREE_NODE_2_ARGS(ArrayExpression, Base,
    NodeList, elements, false,
    NodeBoolean, trailingComma, false)

ESTREE_NODE_1_ARGS(
    SpreadElement, Base,
    NodePtr, argument, false)

ESTREE_NODE_3_ARGS(
    NewExpression, Base,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(NewExpression, typeArguments)
ESTREE_NODE_2_ARGS(
    YieldExpression, Base,
    NodePtr, argument, true,
    NodeBoolean, delegate, true)
ESTREE_NODE_1_ARGS(
    AwaitExpression, Base,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    ImportExpression, Base,
    NodePtr, source, false,
    NodePtr, attributes, true)

ESTREE_FIRST(CallExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    CallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(CallExpression, typeArguments)

ESTREE_NODE_4_ARGS(
    OptionalCallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(OptionalCallExpression, typeArguments)
ESTREE_LAST(CallExpressionLike)

ESTREE_NODE_3_ARGS(
    AssignmentExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false)

ESTREE_NODE_3_ARGS(
    UnaryExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_NODE_3_ARGS(
    UpdateExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_FIRST(MemberExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    MemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false)

ESTREE_NODE_4_ARGS(
    OptionalMemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false,
    NodeBoolean, optional, false)
ESTREE_LAST(MemberExpressionLike)

ESTREE_NODE_3_ARGS(
    LogicalExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_3_ARGS(
    ConditionalExpression,
    Base,
    NodePtr,
    test,
    false,
    NodePtr,
    alternate,
    false,
    NodePtr,
    consequent,
    false)

ESTREE_NODE_3_ARGS(
    BinaryExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_1_ARGS(Directive, Base, NodePtr, value, false)
ESTREE_NODE_1_ARGS(DirectiveLiteral, Base, NodeString, value, false)

ESTREE_NODE_3_ARGS(
    Identifier, Base,
    NodeLabel, name, false,
    NodePtr, typeAnnotation, true,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(Identifier, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(Identifier, optional)

ESTREE_NODE_1_ARGS(
    PrivateName, Base,
    NodePtr, id, false)

ESTREE_NODE_2_ARGS(
    MetaProperty,
    Base,
    NodePtr,
    meta,
    false,
    NodePtr,
    property,
    false)

ESTREE_NODE_2_ARGS(
    SwitchCase,
    Base,
    NodePtr,
    test,
    true,
    NodeList,
    consequent,
    false)

ESTREE_NODE_2_ARGS(
    CatchClause,
    Base,
    NodePtr,
    param,
    true,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclarator,
    Base,
    NodePtr,
    init,
    true,
    NodePtr,
    id,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclaration,
    Base,
    NodeLabel,
    kind,
    false,
    NodeList,
    declarations,
    false)

ESTREE_NODE_2_ARGS(TemplateLiteral, Base,
                   NodeList, quasis, false,
                   NodeList, expressions, false)

ESTREE_NODE_2_ARGS(TaggedTemplateExpression, Base,
                   NodePtr, tag, false,
                   NodePtr, quasi, false)

// In ESTree, it is defined as {tail : boolean,
//                              value : {cooked : string, raw : string}},
// we flatten the value field.
// If the template literal is tagged and the text has an invalid escape,
// cooked will be null.
ESTREE_NODE_3_ARGS(TemplateElement, Base,
                   NodeBoolean, tail, false,
                   NodeString, cooked, true,
                   NodeLabel, raw, false)

ESTREE_NODE_6_ARGS(
    Property, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, method, false,
    NodeBoolean, shorthand, false)

ESTREE_NODE_7_ARGS(
    ClassDeclaration, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, implements)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, decorators)

ESTREE_NODE_7_ARGS(
    ClassExpression, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, implements)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, decorators)

ESTREE_NODE_1_ARGS(
    ClassBody, Base,
    NodeList, body, false)

ESTREE_NODE_9_ARGS(
    ClassProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, computed, false,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, tsModifiers)

ESTREE_NODE_8_ARGS(
    ClassPrivateProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, tsModifiers)

ESTREE_NODE_5_ARGS(
    MethodDefinition, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, static, false)

// Imports ========================================

ESTREE_NODE_4_ARGS(
    ImportDeclaration, Base,
    NodeList, specifiers, false,
    NodePtr, source, false,
    NodeList, assertions, true,
    NodeLabel, importKind, false)

ESTREE_NODE_3_ARGS(
    ImportSpecifier, Base,
    NodePtr, imported, false,
    NodePtr, local, false,
    NodeLabel, importKind, false)
ESTREE_NODE_1_ARGS(
    ImportDefaultSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ImportNamespaceSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_2_ARGS(
    ImportAttribute, Base,
    NodePtr, key, false,
    NodePtr, value, false)


// ================================================

// Exports ========================================

ESTREE_NODE_4_ARGS(
    ExportNamedDeclaration, Base,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeLabel, exportKind, false)

ESTREE_NODE_2_ARGS(
    ExportSpecifier, Base,
    NodePtr, exported, false,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ExportNamespaceSpecifier, Base,
    NodePtr, exported, false)
ESTREE_NODE_1_ARGS(
    ExportDefaultDeclaration, Base,
    NodePtr, declaration, false)
ESTREE_NODE_2_ARGS(
    ExportAllDeclaration, Base,
    NodePtr, source, false,
    NodeLabel, exportKind, false)

// ================================================

// Patterns =======================================
ESTREE_FIRST(Pattern, Base)

ESTREE_NODE_2_ARGS(
    ObjectPattern, Pattern,
    NodeList, properties, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ObjectPattern, typeAnnotation)

ESTREE_NODE_2_ARGS(
    ArrayPattern, Pattern,
    NodeList, elements, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ArrayPattern, typeAnnotation)

ESTREE_NODE_1_ARGS(
    RestElement, Pattern,
    NodePtr, argument, false)

ESTREE_NODE_2_ARGS(
    AssignmentPattern, Pattern,
    NodePtr, left, false,          // Pattern
    NodePtr, right, false)         // Expression

ESTREE_LAST(Pattern)
// ================================================

// JSX ============================================

#if HERMES_PARSE_JSX

ESTREE_FIRST(JSX, Base)

ESTREE_NODE_1_ARGS(
    JSXIdentifier, JSX,
    NodeLabel, name, false)
ESTREE_NODE_2_ARGS(
    JSXMemberExpression, JSX,
    NodePtr, object, false,
    NodePtr, property, false)
ESTREE_NODE_2_ARGS(
    JSXNamespacedName, JSX,
    NodePtr, namespace, false,
    NodePtr, name, false)

ESTREE_NODE_0_ARGS(
    JSXEmptyExpression, JSX)
ESTREE_NODE_1_ARGS(
    JSXExpressionContainer, JSX,
    NodePtr, expression, false)
ESTREE_NODE_1_ARGS(
    JSXSpreadChild, JSX,
    NodePtr, expression, false)

ESTREE_NODE_4_ARGS(
    JSXOpeningElement, JSX,
    NodePtr, name, false,
    NodeList, attributes, false,
    NodeBoolean, selfClosing, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(JSXOpeningElement, typeArguments)
ESTREE_NODE_1_ARGS(
    JSXClosingElement, JSX,
    NodePtr, name, false)

ESTREE_NODE_2_ARGS(
    JSXAttribute, JSX,
    NodePtr, name, false,
    NodePtr, value, true)
ESTREE_NODE_1_ARGS(
    JSXSpreadAttribute, JSX,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    JSXStringLiteral, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_2_ARGS(
    JSXText, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_3_ARGS(
    JSXElement, JSX,
    NodePtr, openingElement, false,
    NodeList, children, false,
    NodePtr, closingElement, true)

ESTREE_NODE_3_ARGS(
    JSXFragment, JSX,
    NodePtr, openingFragment, false,
    NodeList, children, false,
    NodePtr, closingFragment, false)
ESTREE_NODE_0_ARGS(
    JSXOpeningFragment, JSX)
ESTREE_NODE_0_ARGS(
    JSXClosingFragment, JSX)

ESTREE_LAST(JSX)

#endif

// ================================================

// Types ==========================================

#if HERMES_PARSE_FLOW

ESTREE_FIRST(Flow, Base)

ESTREE_NODE_0_ARGS(ExistsTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(EmptyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(StringTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(NumberTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    StringLiteralTypeAnnotation, Flow,
    NodeString, value, false,
    NodeString, raw, false)
ESTREE_NODE_2_ARGS(
    NumberLiteralTypeAnnotation, Flow,
    NodeNumber, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_1_ARGS(
    BigIntLiteralTypeAnnotation, Flow,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(BooleanTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    BooleanLiteralTypeAnnotation, Flow,
    NodeBoolean, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(NullLiteralTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(SymbolTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(AnyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(MixedTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(BigIntTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(VoidTypeAnnotation, Flow)
ESTREE_NODE_5_ARGS(
    FunctionTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, this, true,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_4_ARGS(
    HookTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    FunctionTypeParam, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ComponentTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_3_ARGS(
    ComponentTypeParameter, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_1_ARGS(
    NullableTypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TypeofTypeAnnotation, Flow,
    NodePtr, argument, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(TypeofTypeAnnotation, typeArguments)
ESTREE_NODE_1_ARGS(
    KeyofTypeAnnotation, Flow,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    TypeOperator, Flow,
    NodeLabel, operator, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeofIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TupleTypeAnnotation, Flow,
    NodeList, types, false,
    NodeBoolean, inexact, false)
ESTREE_NODE_2_ARGS(
    TupleTypeSpreadElement, Flow,
    NodePtr, label, true,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_4_ARGS(
    TupleTypeLabeledElement, Flow,
    NodePtr, label, false,
    NodePtr, elementType, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true)
ESTREE_NODE_1_ARGS(
    ArrayTypeAnnotation, Flow,
    NodePtr, elementType, false)
ESTREE_NODE_1_ARGS(
    InferTypeAnnotation, Flow,
    NodePtr, typeParameter, false)
ESTREE_NODE_1_ARGS(
    UnionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    IntersectionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_2_ARGS(
    GenericTypeAnnotation, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    IndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_3_ARGS(
    OptionalIndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ConditionalTypeAnnotation, Flow,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)
ESTREE_NODE_3_ARGS(
    TypePredicate, Flow,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, true,
    NodeString, kind, true)

ESTREE_NODE_2_ARGS(
    InterfaceTypeAnnotation, Flow,
    NodeList, extends, false,
    NodePtr, body, true)

ESTREE_NODE_3_ARGS(
    TypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    OpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, false,
    NodePtr, supertype, true)

ESTREE_NODE_4_ARGS(
    InterfaceDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    DeclareTypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    DeclareOpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, true,
    NodePtr, supertype, true)
ESTREE_NODE_4_ARGS(
    DeclareInterface, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)
ESTREE_NODE_6_ARGS(
    DeclareClass, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodeList, implements, false,
    NodeList, mixins, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareFunction, Flow,
    NodePtr, id, false,
    NodePtr, predicate, true)
ESTREE_NODE_1_ARGS(
    DeclareHook, Flow,
    NodePtr, id, false)
ESTREE_NODE_5_ARGS(
    DeclareComponent, Flow,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_2_ARGS(
    DeclareVariable, Flow,
    NodePtr, id, false,
    NodeLabel, kind, false)
ESTREE_NODE_2_ARGS(
    DeclareEnum, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_4_ARGS(
    DeclareExportDeclaration, Flow,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeBoolean, default, false)
ESTREE_NODE_1_ARGS(
    DeclareExportAllDeclaration, Flow,
    NodePtr, source, false)
ESTREE_NODE_2_ARGS(
    DeclareModule, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareNamespace, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    DeclareModuleExports, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_2_ARGS(
    InterfaceExtends, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_2_ARGS(
    ClassImplements, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_1_ARGS(
    TypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_6_ARGS(
    ObjectTypeAnnotation, Flow,
    NodeList, properties, false,
    NodeList, indexers, false,
    NodeList, callProperties, false,
    NodeList, internalSlots, false,
    NodeBoolean, inexact, false,
    NodeBoolean, exact, false)
ESTREE_NODE_8_ARGS(
    ObjectTypeProperty, Flow,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, method, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, proto, false,
    NodePtr, variance, true,
    NodeLabel, kind, false)
ESTREE_NODE_1_ARGS(
    ObjectTypeSpreadProperty, Flow,
    NodePtr, argument, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeInternalSlot, Flow,
    NodePtr, id, false,
    NodePtr, value, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, method, false)
ESTREE_NODE_2_ARGS(
    ObjectTypeCallProperty, Flow,
    NodePtr, value, false,
    NodeBoolean, static, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeIndexer, Flow,
    NodePtr, id, true,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, static, false,
    NodePtr, variance, true)
ESTREE_NODE_5_ARGS(
    ObjectTypeMappedTypeProperty, Flow,
    NodePtr, keyTparam, false,
    NodePtr, propType, false,
    NodePtr, sourceType, false,
    NodePtr, variance, true,
    NodeString, optional, true)

ESTREE_NODE_1_ARGS(
    Variance, Flow,
    NodeLabel, kind, false)

ESTREE_NODE_1_ARGS(
    TypeParameterDeclaration, Flow,
    NodeList, params, false)
ESTREE_NODE_5_ARGS(
    TypeParameter, Flow,
    NodeLabel, name, false,
    NodePtr, bound, true,
    NodePtr, variance, true,
    NodePtr, default, true,
    NodeBoolean, usesExtendsBound, false)
ESTREE_IGNORE_IF_EMPTY(TypeParameter, usesExtendsBound)
ESTREE_NODE_1_ARGS(
    TypeParameterInstantiation, Flow,
    NodeList, params, false)

ESTREE_NODE_2_ARGS(
    TypeCastExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    AsExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_1_ARGS(
    AsConstExpression, Flow,
    NodePtr, expression, false)

ESTREE_NODE_0_ARGS(InferredPredicate, Flow)
ESTREE_NODE_1_ARGS(
    DeclaredPredicate, Flow,
    NodePtr, value, false)

ESTREE_NODE_2_ARGS(
    EnumDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    EnumStringBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumNumberBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBigIntBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBooleanBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_2_ARGS(
    EnumSymbolBody, Flow,
    NodeList, members, false,
    NodeBoolean, hasUnknownMembers, false)

ESTREE_NODE_1_ARGS(
    EnumDefaultedMember, Flow,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    EnumStringMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumNumberMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBigIntMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBooleanMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_3_ARGS(
    ComponentParameter, Flow,
    NodePtr, name, false,
    NodePtr, local, false,
    NodeBoolean, shorthand, false)

ESTREE_LAST(Flow)

#endif

#if HERMES_PARSE_TS

ESTREE_FIRST(TS, Base)

ESTREE_NODE_1_ARGS(
    TSTypeAnnotation, TS,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_0_ARGS(TSAnyKeyword, TS)
ESTREE_NODE_0_ARGS(TSNumberKeyword, TS)
ESTREE_NODE_0_ARGS(TSBooleanKeyword, TS)
ESTREE_NODE_0_ARGS(TSStringKeyword, TS)
ESTREE_NODE_0_ARGS(TSSymbolKeyword, TS)
ESTREE_NODE_0_ARGS(TSVoidKeyword, TS)
ESTREE_NODE_0_ARGS(TSUndefinedKeyword, TS)
ESTREE_NODE_0_ARGS(TSUnknownKeyword, TS)
ESTREE_NODE_0_ARGS(TSNeverKeyword, TS)
ESTREE_NODE_0_ARGS(TSBigIntKeyword, TS)
ESTREE_NODE_0_ARGS(TSThisType, TS)
ESTREE_NODE_1_ARGS(
    TSLiteralType, TS,
    NodePtr, literal, false)
ESTREE_NODE_2_ARGS(
    TSIndexedAccessType, TS,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_1_ARGS(
    TSArrayType, TS,
    NodePtr, elementType, false)
ESTREE_NODE_2_ARGS(
    TSTypeReference, TS,
    NodePtr, typeName, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSQualifiedName, TS,
    NodePtr, left, false,
    NodePtr, right, true)

ESTREE_NODE_3_ARGS(
    TSFunctionType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    TSConstructorType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSTypePredicate, TS,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_1_ARGS(
    TSTupleType, TS,
    NodeList, elementTypes, false)

ESTREE_NODE_2_ARGS(
    TSTypeAssertion, TS,
    NodePtr, typeAnnotation, false,
    NodePtr, expression, false)
ESTREE_NODE_2_ARGS(
    TSAsExpression, TS,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_5_ARGS(
    TSParameterProperty, TS,
    NodePtr, parameter, false,
    NodeLabel, accessibility, true,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)

ESTREE_NODE_3_ARGS(
    TSTypeAliasDeclaration, TS,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_4_ARGS(
    TSInterfaceDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false,
    NodeList, extends, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSInterfaceHeritage, TS,
    NodePtr, expression, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_1_ARGS(
    TSInterfaceBody, TS,
    NodeList, body, false)

ESTREE_NODE_2_ARGS(
    TSEnumDeclaration, TS,
    NodePtr, id, false,
    NodeList, members, false)
ESTREE_NODE_2_ARGS(
    TSEnumMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_2_ARGS(
    TSModuleDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    TSModuleBlock, TS,
    NodeList, body, false)
ESTREE_NODE_2_ARGS(
    TSModuleMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterDeclaration, TS,
    NodeList, params, false)
ESTREE_NODE_3_ARGS(
    TSTypeParameter, TS,
    NodePtr, name, false,
    NodePtr, constraint, true,
    NodePtr, default, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterInstantiation, TS,
    NodeList, params, false)

ESTREE_NODE_1_ARGS(
    TSUnionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSIntersectionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSTypeQuery, TS,
    NodePtr, exprName, false)
ESTREE_NODE_4_ARGS(
    TSConditionalType, TS,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)

ESTREE_NODE_1_ARGS(
    TSTypeLiteral, TS,
    NodeList, members, false)
ESTREE_NODE_8_ARGS(
    TSPropertySignature, TS,
    NodePtr, key, false,
    NodePtr, typeAnnotation, true,
    NodePtr, initializer, true,
    NodeBoolean, optional, false,
    NodeBoolean, computed, false,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)
ESTREE_NODE_4_ARGS(
    TSMethodSignature, TS,
    NodePtr, key, false,
    NodeList, params, false,
    NodePtr, returnType, true,
    NodeBoolean, computed, false)
ESTREE_NODE_2_ARGS(
    TSIndexSignature, TS,
    NodeList, parameters, false,
    NodePtr, typeAnnotation, true)
ESTREE_NODE_2_ARGS(
    TSCallSignatureDeclaration, TS,
    NodeList, params, false,
    NodePtr, returnType, true)

ESTREE_NODE_2_ARGS(
    TSModifiers, TS,
    NodeLabel, accessibility, false,
    NodeBoolean, readonly, false)

ESTREE_LAST(TS)

#endif

// ================================================

#ifndef ESTREE_DEFINE_COVER_NODES

ESTREE_FIRST(Cover, Base)

// CoverParenthesizedExpressionAndArrowParameterList: "(" ")"
ESTREE_NODE_0_ARGS(CoverEmptyArgs, Cover)

// CoverParenthesizedExpressionAndArrowParameterList:
//      "(" Expression "," ")"
// This is the dummy "empty expression" for the last comma inside a
// SequenceExpression.
ESTREE_NODE_0_ARGS(CoverTrailingComma, Cover)

// CoverInitializer
// This is used for destructuring object assignment with initializers. It
// will be the value node of a Property.
ESTREE_NODE_1_ARGS(
    CoverInitializer, Cover,
    NodePtr, init, false)

// CoverRestElement
// This is used for parsing "...elem" in "()" and in SequenceExpression, so it
// can later be reparsed as an arrow function rest parameter. "rest" will point
// to the actual RestElement.
ESTREE_NODE_1_ARGS(
    CoverRestElement, Cover,
    NodePtr, rest, false)

// CoverTypedIdentifier
// This is used for parsing "ident: type" as either a type cast expression
// or a typed parameter in the parameters list of an arrow function.
// 'left' is the identifier which is typed.
// 'right' is the type which is either the cast target or the type annotation,
//   which may be null if the identifier was simply given a '?' and no ':'
//   with a type annotation.
ESTREE_NODE_3_ARGS(
    CoverTypedIdentifier, Cover,
    NodePtr, left, false,
    NodePtr, right, true,
    NodeBoolean, optional, false)

ESTREE_LAST(Cover)

#endif

#undef ESTREE_FIRST
#undef ESTREE_LAST
#undef ESTREE_WRAP
#undef ESTREE_IGNORE_IF_EMPTY

#undef ESTREE_NODE_0_ARGS
#undef ESTREE_NODE_1_ARGS
#undef ESTREE_NODE_2_ARGS
#undef ESTREE_NODE_3_ARGS
#undef ESTREE_NODE_4_ARGS
#undef ESTREE_NODE_5_ARGS
#undef ESTREE_NODE_6_ARGS
#undef ESTREE_NODE_7_ARGS
#undef ESTREE_NODE_8_ARGS
#undef ESTREE_NODE_9_ARGS

/// An enum to track the "strictness" of a function and whether it has been
/// initialized.
enum class Strictness {
  NotSet,
  NonStrictMode,
  StrictMode,
};

/// \return true if the strictness is set to \c StrictMode. Assert if it hasn't
/// been set.
inline bool isStrict(Strictness strictness) {
  assert(strictness != Strictness::NotSet && "strictness hasn't been set");
  return strictness == Strictness::StrictMode;
}

/// \return \c Strictness::StrictNode or \c Strictness::NonStrictMode depending
///   on the value of \p strictMode.
inline Strictness makeStrictness(bool strictMode) {
  return strictMode ? Strictness::StrictMode : Strictness::NonStrictMode;
}

/// Decoration for all function-like nodes.
class FunctionLikeDecoration {
  sem::FunctionInfo *semInfo_{};

 public:
  Strictness strictness{Strictness::NotSet};
  SourceVisibility sourceVisibility{SourceVisibility::Default};

  /// Whether this function was a method definition rather than using
  /// 'function'. Note that getters and setters are also considered method
  /// definitions, as they do not use the keyword 'function'.
  /// This is used for lazy reparsing of the function.
  bool isMethodDefinition{false};

  void setSemInfo(sem::FunctionInfo *semInfo) {
    assert(semInfo && "setting semInfo to null");
    assert(!semInfo_ && "semInfo is already set");
    semInfo_ = semInfo;
  }

  sem::FunctionInfo *getSemInfo() const {
    assert(semInfo_ && "semInfo is not set!");
    return semInfo_;
  }
};

class ProgramDecoration {
 public:
  // An empty parameter list which we need for compatibility with functions.
  NodeList dummyParamList;
};

/// A decoration describing a label.
class LabelDecorationBase {
  static constexpr unsigned INVALID_LABEL = ~0u;
  unsigned labelIndex_ = INVALID_LABEL;

 public:
  bool isLabelIndexSet() const {
    return labelIndex_ != INVALID_LABEL;
  }

  unsigned getLabelIndex() const {
    assert(isLabelIndexSet() && "labelIndex is not set");
    return labelIndex_;
  }

  void setLabelIndex(unsigned labelIndex) {
    assert(labelIndex != INVALID_LABEL && "setting labelIndex to invalid");
    assert(!isLabelIndexSet() && "labelIndex is already set");
    labelIndex_ = labelIndex;
  }
};

/// A decoration for a break/continue statement.
class GotoDecorationBase : public LabelDecorationBase {};

/// Decoration for all statements.
/// NOTE: This decoration is required by the Statement base node, so we need to
/// provide it even if it is empty.
class StatementDecoration {};

/// Decoration for all loop statements.
/// NOTE: This decoration is required by the LoopStatement base node, so we need
/// to  provide it even if it is empty.
/// It contains an optional label, if it has been referenced by a contained
/// break/continue.
class LoopStatementDecoration : public LabelDecorationBase {};

class SwitchStatementDecoration : public LabelDecorationBase {};

class BreakStatementDecoration : public GotoDecorationBase {};
class ContinueStatementDecoration : public GotoDecorationBase {};

class LabeledStatementDecoration : public LabelDecorationBase {};

class BlockStatementDecoration {
 public:
  /// The source buffer id in which this block was found (see \p SourceMgr ).
  uint32_t bufferId;
  /// True if this is a function body that was pruned while pre-parsing.
  bool isLazyFunctionBody{false};
  /// If this is a lazy block, the Yield param to restore when eagerly parsing.
  bool paramYield{false};
  /// If this is a lazy block, the Await param to restore when eagerly parsing.
  bool paramAwait{false};
};

class JSXDecoration {};
class FlowDecoration {};
class TSDecoration {};
class PatternDecoration {};
class CoverDecoration {};

class CallExpressionLikeDecoration {};
class MemberExpressionLikeDecoration {};

namespace detail {
/// We need to to be able customize some ESTree types when passing them through
/// a constructor, so we create a simple template type mapper. Specifically, a
/// NodeList has to be passed by RValue-reference and moved into place.
/// In the default case, the type is unmodified.
template <class T>
struct ParamTrait {
  using Type = T;
};

/// NodeList is mapped to NodeList &&.
template <>
struct ParamTrait<NodeList> {
  using Type = NodeList &&;
};

/// All nodes derrive from this empty decorator class by default, unless
/// explicitly overwritten by specializing DecoratorTrait for the node class.
class EmptyDecoration {};

/// This template determines the decorator for each node. It must be specialized
/// as necessary for each node.
template <class T>
struct DecoratorTrait {
  using Type = EmptyDecoration;
};

template <>
struct DecoratorTrait<BlockStatementNode> {
  using Type = BlockStatementDecoration;
};
template <>
struct DecoratorTrait<BreakStatementNode> {
  using Type = BreakStatementDecoration;
};
template <>
struct DecoratorTrait<ContinueStatementNode> {
  using Type = ContinueStatementDecoration;
};
template <>
struct DecoratorTrait<SwitchStatementNode> {
  using Type = SwitchStatementDecoration;
};
template <>
struct DecoratorTrait<LabeledStatementNode> {
  using Type = LabeledStatementDecoration;
};
template <>
struct DecoratorTrait<ProgramNode> {
  using Type = ProgramDecoration;
};

} // namespace detail

/// A convenince alias for the base node.
using BaseNode = Node;

#define ESTREE_FIRST(NAME, BASE)                                  \
  class NAME##Node : public BASE##Node, public NAME##Decoration { \
   public:                                                        \
    explicit NAME##Node(NodeKind kind) : BASE##Node(kind) {}      \
    static bool classof(const Node *V) {                          \
      auto kind = V->getKind();                                   \
      return NodeKind::_##NAME##_First < kind &&                  \
          kind < NodeKind::_##NAME##_Last;                        \
    }                                                             \
  };

#define ESTREE_NODE_0_ARGS(NAME, BASE)                                 \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    explicit NAME##Node() : BASE##Node(NodeKind::NAME) {}              \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      V.leave(this);                                                   \
    }                                                                  \
  };

#define ESTREE_NODE_1_ARGS(NAME, BASE, ARG0TY, ARG0NM, ARG0OPT)          \
  class NAME##Node : public BASE##Node,                                  \
                     public detail::DecoratorTrait<NAME##Node>::Type {   \
   public:                                                               \
    ARG0TY _##ARG0NM;                                                    \
    explicit NAME##Node(detail::ParamTrait<ARG0TY>::Type ARG0NM##_)      \
        : BASE##Node(NodeKind::NAME), _##ARG0NM(std::move(ARG0NM##_)) {} \
    template <class Visitor>                                             \
    void visit(Visitor &V) {                                             \
      if (!V.shouldVisit(this)) {                                        \
        return;                                                          \
      }                                                                  \
      V.enter(this);                                                     \
      ESTreeVisit(V, _##ARG0NM);                                         \
      V.leave(this);                                                     \
    }                                                                    \
    static bool classof(const Node *V) {                                 \
      return V->getKind() == NodeKind::NAME;                             \
    }                                                                    \
  };

#define ESTREE_NODE_2_ARGS(                                            \
    NAME, BASE, ARG0TY, ARG0NM, ARG0OPT, ARG1TY, ARG1NM, ARG1OPT)      \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_3_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_4_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT,                                                           \
    ARG3TY,                                                            \
    ARG3NM,                                                            \
    ARG3OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    ARG3TY _##ARG3NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_,                    \
        detail::ParamTrait<ARG3TY>::Type ARG3NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)),                             \
          _##ARG3NM(std::move(ARG3NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      ESTreeVisit(V, _##ARG3NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
                                                                       \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_5_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT,                                                           \
    ARG3TY,                                                            \
    ARG3NM,                                                            \
    ARG3OPT,                                                           \
    ARG4TY,                                                            \
    ARG4NM,                                                            \
    ARG4OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    ARG3TY _##ARG3NM;                                                  \
    ARG4TY _##ARG4NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_,                    \
        detail::ParamTrait<ARG3TY>::Type ARG3NM##_,                    \
        detail::ParamTrait<ARG4TY>::Type ARG4NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)),                             \
          _##ARG3NM(std::move(ARG3NM##_)),                             \
          _##ARG4NM(std::move(ARG4NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      ESTreeVisit(V, _##ARG3NM);                                       \
      ESTreeVisit(V, _##ARG4NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
                                                                       \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_6_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT,                                                           \
    ARG3TY,                                                            \
    ARG3NM,                                                            \
    ARG3OPT,                                                           \
    ARG4TY,                                                            \
    ARG4NM,                                                            \
    ARG4OPT,                                                           \
    ARG5TY,                                                            \
    ARG5NM,                                                            \
    ARG5OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    ARG3TY _##ARG3NM;                                                  \
    ARG4TY _##ARG4NM;                                                  \
    ARG5TY _##ARG5NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_,                    \
        detail::ParamTrait<ARG3TY>::Type ARG3NM##_,                    \
        detail::ParamTrait<ARG4TY>::Type ARG4NM##_,                    \
        detail::ParamTrait<ARG5TY>::Type ARG5NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)),                             \
          _##ARG3NM(std::move(ARG3NM##_)),                             \
          _##ARG4NM(std::move(ARG4NM##_)),                             \
          _##ARG5NM(std::move(ARG5NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      ESTreeVisit(V, _##ARG3NM);                                       \
      ESTreeVisit(V, _##ARG4NM);                                       \
      ESTreeVisit(V, _##ARG5NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
                                                                       \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_7_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT,                                                           \
    ARG3TY,                                                            \
    ARG3NM,                                                            \
    ARG3OPT,                                                           \
    ARG4TY,                                                            \
    ARG4NM,                                                            \
    ARG4OPT,                                                           \
    ARG5TY,                                                            \
    ARG5NM,                                                            \
    ARG5OPT,                                                           \
    ARG6TY,                                                            \
    ARG6NM,                                                            \
    ARG6OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    ARG3TY _##ARG3NM;                                                  \
    ARG4TY _##ARG4NM;                                                  \
    ARG5TY _##ARG5NM;                                                  \
    ARG6TY _##ARG6NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_,                    \
        detail::ParamTrait<ARG3TY>::Type ARG3NM##_,                    \
        detail::ParamTrait<ARG4TY>::Type ARG4NM##_,                    \
        detail::ParamTrait<ARG5TY>::Type ARG5NM##_,                    \
        detail::ParamTrait<ARG6TY>::Type ARG6NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)),                             \
          _##ARG3NM(std::move(ARG3NM##_)),                             \
          _##ARG4NM(std::move(ARG4NM##_)),                             \
          _##ARG5NM(std::move(ARG5NM##_)),                             \
          _##ARG6NM(std::move(ARG6NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      ESTreeVisit(V, _##ARG3NM);                                       \
      ESTreeVisit(V, _##ARG4NM);                                       \
      ESTreeVisit(V, _##ARG5NM);                                       \
      ESTreeVisit(V, _##ARG6NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
                                                                       \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_8_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT,                                                           \
    ARG3TY,                                                            \
    ARG3NM,                                                            \
    ARG3OPT,                                                           \
    ARG4TY,                                                            \
    ARG4NM,                                                            \
    ARG4OPT,                                                           \
    ARG5TY,                                                            \
    ARG5NM,                                                            \
    ARG5OPT,                                                           \
    ARG6TY,                                                            \
    ARG6NM,                                                            \
    ARG6OPT,                                                           \
    ARG7TY,                                                            \
    ARG7NM,                                                            \
    ARG7OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    ARG3TY _##ARG3NM;                                                  \
    ARG4TY _##ARG4NM;                                                  \
    ARG5TY _##ARG5NM;                                                  \
    ARG6TY _##ARG6NM;                                                  \
    ARG7TY _##ARG7NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_,                    \
        detail::ParamTrait<ARG3TY>::Type ARG3NM##_,                    \
        detail::ParamTrait<ARG4TY>::Type ARG4NM##_,                    \
        detail::ParamTrait<ARG5TY>::Type ARG5NM##_,                    \
        detail::ParamTrait<ARG6TY>::Type ARG6NM##_,                    \
        detail::ParamTrait<ARG7TY>::Type ARG7NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)),                             \
          _##ARG3NM(std::move(ARG3NM##_)),                             \
          _##ARG4NM(std::move(ARG4NM##_)),                             \
          _##ARG5NM(std::move(ARG5NM##_)),                             \
          _##ARG6NM(std::move(ARG6NM##_)),                             \
          _##ARG7NM(std::move(ARG7NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      ESTreeVisit(V, _##ARG3NM);                                       \
      ESTreeVisit(V, _##ARG4NM);                                       \
      ESTreeVisit(V, _##ARG5NM);                                       \
      ESTreeVisit(V, _##ARG6NM);                                       \
      ESTreeVisit(V, _##ARG7NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
                                                                       \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#define ESTREE_NODE_9_ARGS(                                            \
    NAME,                                                              \
    BASE,                                                              \
    ARG0TY,                                                            \
    ARG0NM,                                                            \
    ARG0OPT,                                                           \
    ARG1TY,                                                            \
    ARG1NM,                                                            \
    ARG1OPT,                                                           \
    ARG2TY,                                                            \
    ARG2NM,                                                            \
    ARG2OPT,                                                           \
    ARG3TY,                                                            \
    ARG3NM,                                                            \
    ARG3OPT,                                                           \
    ARG4TY,                                                            \
    ARG4NM,                                                            \
    ARG4OPT,                                                           \
    ARG5TY,                                                            \
    ARG5NM,                                                            \
    ARG5OPT,                                                           \
    ARG6TY,                                                            \
    ARG6NM,                                                            \
    ARG6OPT,                                                           \
    ARG7TY,                                                            \
    ARG7NM,                                                            \
    ARG7OPT,                                                           \
    ARG8TY,                                                            \
    ARG8NM,                                                            \
    ARG8OPT)                                                           \
  class NAME##Node : public BASE##Node,                                \
                     public detail::DecoratorTrait<NAME##Node>::Type { \
   public:                                                             \
    ARG0TY _##ARG0NM;                                                  \
    ARG1TY _##ARG1NM;                                                  \
    ARG2TY _##ARG2NM;                                                  \
    ARG3TY _##ARG3NM;                                                  \
    ARG4TY _##ARG4NM;                                                  \
    ARG5TY _##ARG5NM;                                                  \
    ARG6TY _##ARG6NM;                                                  \
    ARG7TY _##ARG7NM;                                                  \
    ARG8TY _##ARG8NM;                                                  \
    explicit NAME##Node(                                               \
        detail::ParamTrait<ARG0TY>::Type ARG0NM##_,                    \
        detail::ParamTrait<ARG1TY>::Type ARG1NM##_,                    \
        detail::ParamTrait<ARG2TY>::Type ARG2NM##_,                    \
        detail::ParamTrait<ARG3TY>::Type ARG3NM##_,                    \
        detail::ParamTrait<ARG4TY>::Type ARG4NM##_,                    \
        detail::ParamTrait<ARG5TY>::Type ARG5NM##_,                    \
        detail::ParamTrait<ARG6TY>::Type ARG6NM##_,                    \
        detail::ParamTrait<ARG7TY>::Type ARG7NM##_,                    \
        detail::ParamTrait<ARG8TY>::Type ARG8NM##_)                    \
        : BASE##Node(NodeKind::NAME),                                  \
          _##ARG0NM(std::move(ARG0NM##_)),                             \
          _##ARG1NM(std::move(ARG1NM##_)),                             \
          _##ARG2NM(std::move(ARG2NM##_)),                             \
          _##ARG3NM(std::move(ARG3NM##_)),                             \
          _##ARG4NM(std::move(ARG4NM##_)),                             \
          _##ARG5NM(std::move(ARG5NM##_)),                             \
          _##ARG6NM(std::move(ARG6NM##_)),                             \
          _##ARG7NM(std::move(ARG7NM##_)),                             \
          _##ARG8NM(std::move(ARG8NM##_)) {}                           \
    template <class Visitor>                                           \
    void visit(Visitor &V) {                                           \
      if (!V.shouldVisit(this)) {                                      \
        return;                                                        \
      }                                                                \
      V.enter(this);                                                   \
      ESTreeVisit(V, _##ARG0NM);                                       \
      ESTreeVisit(V, _##ARG1NM);                                       \
      ESTreeVisit(V, _##ARG2NM);                                       \
      ESTreeVisit(V, _##ARG3NM);                                       \
      ESTreeVisit(V, _##ARG4NM);                                       \
      ESTreeVisit(V, _##ARG5NM);                                       \
      ESTreeVisit(V, _##ARG6NM);                                       \
      ESTreeVisit(V, _##ARG7NM);                                       \
      ESTreeVisit(V, _##ARG8NM);                                       \
      V.leave(this);                                                   \
    }                                                                  \
                                                                       \
    static bool classof(const Node *V) {                               \
      return V->getKind() == NodeKind::NAME;                           \
    }                                                                  \
  };

#ifndef HERMES_PARSER_CONFIG_H
#define HERMES_PARSER_CONFIG_H

#if !defined(HERMES_PARSE_JSX)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_JSX 0
#else
#define HERMES_PARSE_JSX 1
#endif
#endif

#if !defined(HERMES_PARSE_FLOW)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_FLOW 0
#else
#define HERMES_PARSE_FLOW 1
#endif
#endif

#if !defined(HERMES_PARSE_TS)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_TS 0
#else
#define HERMES_PARSE_TS 1
#endif
#endif

#endif

// clang-format off

// Defines the start of range of nodes with the same base
#ifndef ESTREE_FIRST
#define ESTREE_FIRST(NAME, BASE)
#endif

// Defines the end of range of nodes with the same base
#ifndef ESTREE_LAST
#define ESTREE_LAST(NAME)
#endif

// Ignores the given field if it is "empty" (e.g. nullptr, empty list).
#ifndef ESTREE_IGNORE_IF_EMPTY
#define ESTREE_IGNORE_IF_EMPTY(NODE, FIELD)
#endif

ESTREE_NODE_0_ARGS(Empty, Base)
ESTREE_NODE_0_ARGS(Metadata, Base)

ESTREE_FIRST(FunctionLike, Base)
ESTREE_NODE_1_ARGS(Program, FunctionLike,
    NodeList, body, false)
ESTREE_NODE_8_ARGS(
    FunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    ArrowFunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, expression, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    FunctionDeclaration, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, predicate)

#if HERMES_PARSE_FLOW

ESTREE_NODE_5_ARGS(
    ComponentDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, rendersType)

ESTREE_NODE_5_ARGS(
    HookDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, returnType)

#endif

ESTREE_LAST(FunctionLike)

ESTREE_FIRST(Statement, Base)

ESTREE_FIRST(LoopStatement, Statement)
ESTREE_NODE_2_ARGS(
    WhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_2_ARGS(
    DoWhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_3_ARGS(
    ForInStatement,
    LoopStatement,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodePtr,
    body,
    false)
ESTREE_NODE_4_ARGS(
    ForOfStatement, LoopStatement,
    NodePtr, left, false,
    NodePtr, right, false,
    NodePtr, body, false,
    NodeBoolean, await, false)
ESTREE_NODE_4_ARGS(
    ForStatement,
    LoopStatement,
    NodePtr,
    init,
    true,
    NodePtr,
    test,
    true,
    NodePtr,
    update,
    true,
    NodePtr,
    body,
    false)
ESTREE_LAST(LoopStatement)

ESTREE_NODE_0_ARGS(DebuggerStatement, Statement)
ESTREE_NODE_0_ARGS(EmptyStatement, Statement)
ESTREE_NODE_1_ARGS(BlockStatement, Statement, NodeList, body, false)
ESTREE_NODE_1_ARGS(BreakStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ContinueStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ThrowStatement, Statement, NodePtr, argument, false)
ESTREE_NODE_1_ARGS(ReturnStatement, Statement, NodePtr, argument, true)
ESTREE_NODE_2_ARGS(
    WithStatement,
    Statement,
    NodePtr,
    object,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    SwitchStatement,
    Statement,
    NodePtr,
    discriminant,
    false,
    NodeList,
    cases,
    false)

ESTREE_NODE_2_ARGS(
    LabeledStatement,
    Statement,
    NodePtr,
    label,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    ExpressionStatement,
    Statement,
    NodePtr,
    expression,
    false,
    NodeString,
    directive,
    true)

ESTREE_NODE_3_ARGS(
    TryStatement,
    Statement,
    NodePtr,
    block,
    false,
    NodePtr,
    handler,
    true,
    NodePtr,
    finalizer,
    true)

ESTREE_NODE_3_ARGS(
    IfStatement,
    Statement,
    NodePtr,
    test,
    false,
    NodePtr,
    consequent,
    false,
    NodePtr,
    alternate,
    true)

ESTREE_LAST(Statement)

ESTREE_NODE_0_ARGS(NullLiteral, Base)
ESTREE_NODE_1_ARGS(BooleanLiteral, Base, NodeBoolean, value, false)
ESTREE_NODE_1_ARGS(StringLiteral, Base, NodeString, value, false)
ESTREE_NODE_1_ARGS(NumericLiteral, Base, NodeNumber, value, false)
ESTREE_NODE_2_ARGS(
    RegExpLiteral,
    Base,
    NodeLabel,
    pattern,
    false,
    NodeLabel,
    flags,
    false)
ESTREE_NODE_1_ARGS(
    BigIntLiteral, Base,
    NodeLabel, bigint, false)

ESTREE_NODE_0_ARGS(ThisExpression, Base)
ESTREE_NODE_0_ARGS(Super, Base)
ESTREE_NODE_1_ARGS(SequenceExpression, Base, NodeList, expressions, false)
ESTREE_NODE_1_ARGS(ObjectExpression, Base, NodeList, properties, false)
ESTREE_NODE_2_ARGS(ArrayExpression, Base,
    NodeList, elements, false,
    NodeBoolean, trailingComma, false)

ESTREE_NODE_1_ARGS(
    SpreadElement, Base,
    NodePtr, argument, false)

ESTREE_NODE_3_ARGS(
    NewExpression, Base,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(NewExpression, typeArguments)
ESTREE_NODE_2_ARGS(
    YieldExpression, Base,
    NodePtr, argument, true,
    NodeBoolean, delegate, true)
ESTREE_NODE_1_ARGS(
    AwaitExpression, Base,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    ImportExpression, Base,
    NodePtr, source, false,
    NodePtr, attributes, true)

ESTREE_FIRST(CallExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    CallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(CallExpression, typeArguments)

ESTREE_NODE_4_ARGS(
    OptionalCallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(OptionalCallExpression, typeArguments)
ESTREE_LAST(CallExpressionLike)

ESTREE_NODE_3_ARGS(
    AssignmentExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false)

ESTREE_NODE_3_ARGS(
    UnaryExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_NODE_3_ARGS(
    UpdateExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_FIRST(MemberExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    MemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false)

ESTREE_NODE_4_ARGS(
    OptionalMemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false,
    NodeBoolean, optional, false)
ESTREE_LAST(MemberExpressionLike)

ESTREE_NODE_3_ARGS(
    LogicalExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_3_ARGS(
    ConditionalExpression,
    Base,
    NodePtr,
    test,
    false,
    NodePtr,
    alternate,
    false,
    NodePtr,
    consequent,
    false)

ESTREE_NODE_3_ARGS(
    BinaryExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_1_ARGS(Directive, Base, NodePtr, value, false)
ESTREE_NODE_1_ARGS(DirectiveLiteral, Base, NodeString, value, false)

ESTREE_NODE_3_ARGS(
    Identifier, Base,
    NodeLabel, name, false,
    NodePtr, typeAnnotation, true,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(Identifier, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(Identifier, optional)

ESTREE_NODE_1_ARGS(
    PrivateName, Base,
    NodePtr, id, false)

ESTREE_NODE_2_ARGS(
    MetaProperty,
    Base,
    NodePtr,
    meta,
    false,
    NodePtr,
    property,
    false)

ESTREE_NODE_2_ARGS(
    SwitchCase,
    Base,
    NodePtr,
    test,
    true,
    NodeList,
    consequent,
    false)

ESTREE_NODE_2_ARGS(
    CatchClause,
    Base,
    NodePtr,
    param,
    true,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclarator,
    Base,
    NodePtr,
    init,
    true,
    NodePtr,
    id,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclaration,
    Base,
    NodeLabel,
    kind,
    false,
    NodeList,
    declarations,
    false)

ESTREE_NODE_2_ARGS(TemplateLiteral, Base,
                   NodeList, quasis, false,
                   NodeList, expressions, false)

ESTREE_NODE_2_ARGS(TaggedTemplateExpression, Base,
                   NodePtr, tag, false,
                   NodePtr, quasi, false)

// In ESTree, it is defined as {tail : boolean,
//                              value : {cooked : string, raw : string}},
// we flatten the value field.
// If the template literal is tagged and the text has an invalid escape,
// cooked will be null.
ESTREE_NODE_3_ARGS(TemplateElement, Base,
                   NodeBoolean, tail, false,
                   NodeString, cooked, true,
                   NodeLabel, raw, false)

ESTREE_NODE_6_ARGS(
    Property, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, method, false,
    NodeBoolean, shorthand, false)

ESTREE_NODE_7_ARGS(
    ClassDeclaration, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, implements)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, decorators)

ESTREE_NODE_7_ARGS(
    ClassExpression, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, implements)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, decorators)

ESTREE_NODE_1_ARGS(
    ClassBody, Base,
    NodeList, body, false)

ESTREE_NODE_9_ARGS(
    ClassProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, computed, false,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, tsModifiers)

ESTREE_NODE_8_ARGS(
    ClassPrivateProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, tsModifiers)

ESTREE_NODE_5_ARGS(
    MethodDefinition, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, static, false)

// Imports ========================================

ESTREE_NODE_4_ARGS(
    ImportDeclaration, Base,
    NodeList, specifiers, false,
    NodePtr, source, false,
    NodeList, assertions, true,
    NodeLabel, importKind, false)

ESTREE_NODE_3_ARGS(
    ImportSpecifier, Base,
    NodePtr, imported, false,
    NodePtr, local, false,
    NodeLabel, importKind, false)
ESTREE_NODE_1_ARGS(
    ImportDefaultSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ImportNamespaceSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_2_ARGS(
    ImportAttribute, Base,
    NodePtr, key, false,
    NodePtr, value, false)


// ================================================

// Exports ========================================

ESTREE_NODE_4_ARGS(
    ExportNamedDeclaration, Base,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeLabel, exportKind, false)

ESTREE_NODE_2_ARGS(
    ExportSpecifier, Base,
    NodePtr, exported, false,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ExportNamespaceSpecifier, Base,
    NodePtr, exported, false)
ESTREE_NODE_1_ARGS(
    ExportDefaultDeclaration, Base,
    NodePtr, declaration, false)
ESTREE_NODE_2_ARGS(
    ExportAllDeclaration, Base,
    NodePtr, source, false,
    NodeLabel, exportKind, false)

// ================================================

// Patterns =======================================
ESTREE_FIRST(Pattern, Base)

ESTREE_NODE_2_ARGS(
    ObjectPattern, Pattern,
    NodeList, properties, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ObjectPattern, typeAnnotation)

ESTREE_NODE_2_ARGS(
    ArrayPattern, Pattern,
    NodeList, elements, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ArrayPattern, typeAnnotation)

ESTREE_NODE_1_ARGS(
    RestElement, Pattern,
    NodePtr, argument, false)

ESTREE_NODE_2_ARGS(
    AssignmentPattern, Pattern,
    NodePtr, left, false,          // Pattern
    NodePtr, right, false)         // Expression

ESTREE_LAST(Pattern)
// ================================================

// JSX ============================================

#if HERMES_PARSE_JSX

ESTREE_FIRST(JSX, Base)

ESTREE_NODE_1_ARGS(
    JSXIdentifier, JSX,
    NodeLabel, name, false)
ESTREE_NODE_2_ARGS(
    JSXMemberExpression, JSX,
    NodePtr, object, false,
    NodePtr, property, false)
ESTREE_NODE_2_ARGS(
    JSXNamespacedName, JSX,
    NodePtr, namespace, false,
    NodePtr, name, false)

ESTREE_NODE_0_ARGS(
    JSXEmptyExpression, JSX)
ESTREE_NODE_1_ARGS(
    JSXExpressionContainer, JSX,
    NodePtr, expression, false)
ESTREE_NODE_1_ARGS(
    JSXSpreadChild, JSX,
    NodePtr, expression, false)

ESTREE_NODE_4_ARGS(
    JSXOpeningElement, JSX,
    NodePtr, name, false,
    NodeList, attributes, false,
    NodeBoolean, selfClosing, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(JSXOpeningElement, typeArguments)
ESTREE_NODE_1_ARGS(
    JSXClosingElement, JSX,
    NodePtr, name, false)

ESTREE_NODE_2_ARGS(
    JSXAttribute, JSX,
    NodePtr, name, false,
    NodePtr, value, true)
ESTREE_NODE_1_ARGS(
    JSXSpreadAttribute, JSX,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    JSXStringLiteral, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_2_ARGS(
    JSXText, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_3_ARGS(
    JSXElement, JSX,
    NodePtr, openingElement, false,
    NodeList, children, false,
    NodePtr, closingElement, true)

ESTREE_NODE_3_ARGS(
    JSXFragment, JSX,
    NodePtr, openingFragment, false,
    NodeList, children, false,
    NodePtr, closingFragment, false)
ESTREE_NODE_0_ARGS(
    JSXOpeningFragment, JSX)
ESTREE_NODE_0_ARGS(
    JSXClosingFragment, JSX)

ESTREE_LAST(JSX)

#endif

// ================================================

// Types ==========================================

#if HERMES_PARSE_FLOW

ESTREE_FIRST(Flow, Base)

ESTREE_NODE_0_ARGS(ExistsTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(EmptyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(StringTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(NumberTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    StringLiteralTypeAnnotation, Flow,
    NodeString, value, false,
    NodeString, raw, false)
ESTREE_NODE_2_ARGS(
    NumberLiteralTypeAnnotation, Flow,
    NodeNumber, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_1_ARGS(
    BigIntLiteralTypeAnnotation, Flow,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(BooleanTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    BooleanLiteralTypeAnnotation, Flow,
    NodeBoolean, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(NullLiteralTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(SymbolTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(AnyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(MixedTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(BigIntTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(VoidTypeAnnotation, Flow)
ESTREE_NODE_5_ARGS(
    FunctionTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, this, true,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_4_ARGS(
    HookTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    FunctionTypeParam, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ComponentTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_3_ARGS(
    ComponentTypeParameter, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_1_ARGS(
    NullableTypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TypeofTypeAnnotation, Flow,
    NodePtr, argument, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(TypeofTypeAnnotation, typeArguments)
ESTREE_NODE_1_ARGS(
    KeyofTypeAnnotation, Flow,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    TypeOperator, Flow,
    NodeLabel, operator, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeofIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TupleTypeAnnotation, Flow,
    NodeList, types, false,
    NodeBoolean, inexact, false)
ESTREE_NODE_2_ARGS(
    TupleTypeSpreadElement, Flow,
    NodePtr, label, true,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_4_ARGS(
    TupleTypeLabeledElement, Flow,
    NodePtr, label, false,
    NodePtr, elementType, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true)
ESTREE_NODE_1_ARGS(
    ArrayTypeAnnotation, Flow,
    NodePtr, elementType, false)
ESTREE_NODE_1_ARGS(
    InferTypeAnnotation, Flow,
    NodePtr, typeParameter, false)
ESTREE_NODE_1_ARGS(
    UnionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    IntersectionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_2_ARGS(
    GenericTypeAnnotation, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    IndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_3_ARGS(
    OptionalIndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ConditionalTypeAnnotation, Flow,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)
ESTREE_NODE_3_ARGS(
    TypePredicate, Flow,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, true,
    NodeString, kind, true)

ESTREE_NODE_2_ARGS(
    InterfaceTypeAnnotation, Flow,
    NodeList, extends, false,
    NodePtr, body, true)

ESTREE_NODE_3_ARGS(
    TypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    OpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, false,
    NodePtr, supertype, true)

ESTREE_NODE_4_ARGS(
    InterfaceDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    DeclareTypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    DeclareOpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, true,
    NodePtr, supertype, true)
ESTREE_NODE_4_ARGS(
    DeclareInterface, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)
ESTREE_NODE_6_ARGS(
    DeclareClass, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodeList, implements, false,
    NodeList, mixins, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareFunction, Flow,
    NodePtr, id, false,
    NodePtr, predicate, true)
ESTREE_NODE_1_ARGS(
    DeclareHook, Flow,
    NodePtr, id, false)
ESTREE_NODE_5_ARGS(
    DeclareComponent, Flow,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_2_ARGS(
    DeclareVariable, Flow,
    NodePtr, id, false,
    NodeLabel, kind, false)
ESTREE_NODE_2_ARGS(
    DeclareEnum, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_4_ARGS(
    DeclareExportDeclaration, Flow,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeBoolean, default, false)
ESTREE_NODE_1_ARGS(
    DeclareExportAllDeclaration, Flow,
    NodePtr, source, false)
ESTREE_NODE_2_ARGS(
    DeclareModule, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareNamespace, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    DeclareModuleExports, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_2_ARGS(
    InterfaceExtends, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_2_ARGS(
    ClassImplements, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_1_ARGS(
    TypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_6_ARGS(
    ObjectTypeAnnotation, Flow,
    NodeList, properties, false,
    NodeList, indexers, false,
    NodeList, callProperties, false,
    NodeList, internalSlots, false,
    NodeBoolean, inexact, false,
    NodeBoolean, exact, false)
ESTREE_NODE_8_ARGS(
    ObjectTypeProperty, Flow,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, method, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, proto, false,
    NodePtr, variance, true,
    NodeLabel, kind, false)
ESTREE_NODE_1_ARGS(
    ObjectTypeSpreadProperty, Flow,
    NodePtr, argument, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeInternalSlot, Flow,
    NodePtr, id, false,
    NodePtr, value, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, method, false)
ESTREE_NODE_2_ARGS(
    ObjectTypeCallProperty, Flow,
    NodePtr, value, false,
    NodeBoolean, static, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeIndexer, Flow,
    NodePtr, id, true,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, static, false,
    NodePtr, variance, true)
ESTREE_NODE_5_ARGS(
    ObjectTypeMappedTypeProperty, Flow,
    NodePtr, keyTparam, false,
    NodePtr, propType, false,
    NodePtr, sourceType, false,
    NodePtr, variance, true,
    NodeString, optional, true)

ESTREE_NODE_1_ARGS(
    Variance, Flow,
    NodeLabel, kind, false)

ESTREE_NODE_1_ARGS(
    TypeParameterDeclaration, Flow,
    NodeList, params, false)
ESTREE_NODE_5_ARGS(
    TypeParameter, Flow,
    NodeLabel, name, false,
    NodePtr, bound, true,
    NodePtr, variance, true,
    NodePtr, default, true,
    NodeBoolean, usesExtendsBound, false)
ESTREE_IGNORE_IF_EMPTY(TypeParameter, usesExtendsBound)
ESTREE_NODE_1_ARGS(
    TypeParameterInstantiation, Flow,
    NodeList, params, false)

ESTREE_NODE_2_ARGS(
    TypeCastExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    AsExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_1_ARGS(
    AsConstExpression, Flow,
    NodePtr, expression, false)

ESTREE_NODE_0_ARGS(InferredPredicate, Flow)
ESTREE_NODE_1_ARGS(
    DeclaredPredicate, Flow,
    NodePtr, value, false)

ESTREE_NODE_2_ARGS(
    EnumDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    EnumStringBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumNumberBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBigIntBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBooleanBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_2_ARGS(
    EnumSymbolBody, Flow,
    NodeList, members, false,
    NodeBoolean, hasUnknownMembers, false)

ESTREE_NODE_1_ARGS(
    EnumDefaultedMember, Flow,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    EnumStringMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumNumberMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBigIntMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBooleanMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_3_ARGS(
    ComponentParameter, Flow,
    NodePtr, name, false,
    NodePtr, local, false,
    NodeBoolean, shorthand, false)

ESTREE_LAST(Flow)

#endif

#if HERMES_PARSE_TS

ESTREE_FIRST(TS, Base)

ESTREE_NODE_1_ARGS(
    TSTypeAnnotation, TS,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_0_ARGS(TSAnyKeyword, TS)
ESTREE_NODE_0_ARGS(TSNumberKeyword, TS)
ESTREE_NODE_0_ARGS(TSBooleanKeyword, TS)
ESTREE_NODE_0_ARGS(TSStringKeyword, TS)
ESTREE_NODE_0_ARGS(TSSymbolKeyword, TS)
ESTREE_NODE_0_ARGS(TSVoidKeyword, TS)
ESTREE_NODE_0_ARGS(TSUndefinedKeyword, TS)
ESTREE_NODE_0_ARGS(TSUnknownKeyword, TS)
ESTREE_NODE_0_ARGS(TSNeverKeyword, TS)
ESTREE_NODE_0_ARGS(TSBigIntKeyword, TS)
ESTREE_NODE_0_ARGS(TSThisType, TS)
ESTREE_NODE_1_ARGS(
    TSLiteralType, TS,
    NodePtr, literal, false)
ESTREE_NODE_2_ARGS(
    TSIndexedAccessType, TS,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_1_ARGS(
    TSArrayType, TS,
    NodePtr, elementType, false)
ESTREE_NODE_2_ARGS(
    TSTypeReference, TS,
    NodePtr, typeName, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSQualifiedName, TS,
    NodePtr, left, false,
    NodePtr, right, true)

ESTREE_NODE_3_ARGS(
    TSFunctionType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    TSConstructorType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSTypePredicate, TS,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_1_ARGS(
    TSTupleType, TS,
    NodeList, elementTypes, false)

ESTREE_NODE_2_ARGS(
    TSTypeAssertion, TS,
    NodePtr, typeAnnotation, false,
    NodePtr, expression, false)
ESTREE_NODE_2_ARGS(
    TSAsExpression, TS,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_5_ARGS(
    TSParameterProperty, TS,
    NodePtr, parameter, false,
    NodeLabel, accessibility, true,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)

ESTREE_NODE_3_ARGS(
    TSTypeAliasDeclaration, TS,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_4_ARGS(
    TSInterfaceDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false,
    NodeList, extends, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSInterfaceHeritage, TS,
    NodePtr, expression, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_1_ARGS(
    TSInterfaceBody, TS,
    NodeList, body, false)

ESTREE_NODE_2_ARGS(
    TSEnumDeclaration, TS,
    NodePtr, id, false,
    NodeList, members, false)
ESTREE_NODE_2_ARGS(
    TSEnumMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_2_ARGS(
    TSModuleDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    TSModuleBlock, TS,
    NodeList, body, false)
ESTREE_NODE_2_ARGS(
    TSModuleMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterDeclaration, TS,
    NodeList, params, false)
ESTREE_NODE_3_ARGS(
    TSTypeParameter, TS,
    NodePtr, name, false,
    NodePtr, constraint, true,
    NodePtr, default, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterInstantiation, TS,
    NodeList, params, false)

ESTREE_NODE_1_ARGS(
    TSUnionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSIntersectionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSTypeQuery, TS,
    NodePtr, exprName, false)
ESTREE_NODE_4_ARGS(
    TSConditionalType, TS,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)

ESTREE_NODE_1_ARGS(
    TSTypeLiteral, TS,
    NodeList, members, false)
ESTREE_NODE_8_ARGS(
    TSPropertySignature, TS,
    NodePtr, key, false,
    NodePtr, typeAnnotation, true,
    NodePtr, initializer, true,
    NodeBoolean, optional, false,
    NodeBoolean, computed, false,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)
ESTREE_NODE_4_ARGS(
    TSMethodSignature, TS,
    NodePtr, key, false,
    NodeList, params, false,
    NodePtr, returnType, true,
    NodeBoolean, computed, false)
ESTREE_NODE_2_ARGS(
    TSIndexSignature, TS,
    NodeList, parameters, false,
    NodePtr, typeAnnotation, true)
ESTREE_NODE_2_ARGS(
    TSCallSignatureDeclaration, TS,
    NodeList, params, false,
    NodePtr, returnType, true)

ESTREE_NODE_2_ARGS(
    TSModifiers, TS,
    NodeLabel, accessibility, false,
    NodeBoolean, readonly, false)

ESTREE_LAST(TS)

#endif

// ================================================

#ifndef ESTREE_DEFINE_COVER_NODES

ESTREE_FIRST(Cover, Base)

// CoverParenthesizedExpressionAndArrowParameterList: "(" ")"
ESTREE_NODE_0_ARGS(CoverEmptyArgs, Cover)

// CoverParenthesizedExpressionAndArrowParameterList:
//      "(" Expression "," ")"
// This is the dummy "empty expression" for the last comma inside a
// SequenceExpression.
ESTREE_NODE_0_ARGS(CoverTrailingComma, Cover)

// CoverInitializer
// This is used for destructuring object assignment with initializers. It
// will be the value node of a Property.
ESTREE_NODE_1_ARGS(
    CoverInitializer, Cover,
    NodePtr, init, false)

// CoverRestElement
// This is used for parsing "...elem" in "()" and in SequenceExpression, so it
// can later be reparsed as an arrow function rest parameter. "rest" will point
// to the actual RestElement.
ESTREE_NODE_1_ARGS(
    CoverRestElement, Cover,
    NodePtr, rest, false)

// CoverTypedIdentifier
// This is used for parsing "ident: type" as either a type cast expression
// or a typed parameter in the parameters list of an arrow function.
// 'left' is the identifier which is typed.
// 'right' is the type which is either the cast target or the type annotation,
//   which may be null if the identifier was simply given a '?' and no ':'
//   with a type annotation.
ESTREE_NODE_3_ARGS(
    CoverTypedIdentifier, Cover,
    NodePtr, left, false,
    NodePtr, right, true,
    NodeBoolean, optional, false)

ESTREE_LAST(Cover)

#endif

#undef ESTREE_FIRST
#undef ESTREE_LAST
#undef ESTREE_WRAP
#undef ESTREE_IGNORE_IF_EMPTY

#undef ESTREE_NODE_0_ARGS
#undef ESTREE_NODE_1_ARGS
#undef ESTREE_NODE_2_ARGS
#undef ESTREE_NODE_3_ARGS
#undef ESTREE_NODE_4_ARGS
#undef ESTREE_NODE_5_ARGS
#undef ESTREE_NODE_6_ARGS
#undef ESTREE_NODE_7_ARGS
#undef ESTREE_NODE_8_ARGS
#undef ESTREE_NODE_9_ARGS

// Visit nodes.
template <class Visitor>
void ESTreeVisit(Visitor &V, NodePtr Node) {
  if (!Node) {
    return;
  }

  switch (Node->getKind()) {
    default:
      llvm_unreachable("invalid node kind");

#define ESTREE_NODE_0_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_1_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_2_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_3_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_4_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_5_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_6_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_7_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_8_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);
#define ESTREE_NODE_9_ARGS(NAME, ...) \
  case NodeKind::NAME:                \
    return cast<NAME##Node>(Node)->visit(V);

#ifndef HERMES_PARSER_CONFIG_H
#define HERMES_PARSER_CONFIG_H

#if !defined(HERMES_PARSE_JSX)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_JSX 0
#else
#define HERMES_PARSE_JSX 1
#endif
#endif

#if !defined(HERMES_PARSE_FLOW)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_FLOW 0
#else
#define HERMES_PARSE_FLOW 1
#endif
#endif

#if !defined(HERMES_PARSE_TS)
#if defined(HERMES_IS_MOBILE_BUILD)
#define HERMES_PARSE_TS 0
#else
#define HERMES_PARSE_TS 1
#endif
#endif

#endif

// clang-format off

// Defines the start of range of nodes with the same base
#ifndef ESTREE_FIRST
#define ESTREE_FIRST(NAME, BASE)
#endif

// Defines the end of range of nodes with the same base
#ifndef ESTREE_LAST
#define ESTREE_LAST(NAME)
#endif

// Ignores the given field if it is "empty" (e.g. nullptr, empty list).
#ifndef ESTREE_IGNORE_IF_EMPTY
#define ESTREE_IGNORE_IF_EMPTY(NODE, FIELD)
#endif

ESTREE_NODE_0_ARGS(Empty, Base)
ESTREE_NODE_0_ARGS(Metadata, Base)

ESTREE_FIRST(FunctionLike, Base)
ESTREE_NODE_1_ARGS(Program, FunctionLike,
    NodeList, body, false)
ESTREE_NODE_8_ARGS(
    FunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    ArrowFunctionExpression, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, expression, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, returnType)
ESTREE_IGNORE_IF_EMPTY(ArrowFunctionExpression, predicate)
ESTREE_NODE_8_ARGS(
    FunctionDeclaration, FunctionLike,
    NodePtr, id, true,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true,
    NodePtr, predicate, true,
    NodeBoolean, generator, false,
    NodeBoolean, async, false)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, returnType)
ESTREE_IGNORE_IF_EMPTY(FunctionDeclaration, predicate)

#if HERMES_PARSE_FLOW

ESTREE_NODE_5_ARGS(
    ComponentDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ComponentDeclaration, rendersType)

ESTREE_NODE_5_ARGS(
    HookDeclaration, FunctionLike,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, body, false,
    NodePtr, typeParameters, true,
    NodePtr, returnType, true)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(HookDeclaration, returnType)

#endif

ESTREE_LAST(FunctionLike)

ESTREE_FIRST(Statement, Base)

ESTREE_FIRST(LoopStatement, Statement)
ESTREE_NODE_2_ARGS(
    WhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_2_ARGS(
    DoWhileStatement,
    LoopStatement,
    NodePtr,
    body,
    false,
    NodePtr,
    test,
    false)
ESTREE_NODE_3_ARGS(
    ForInStatement,
    LoopStatement,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodePtr,
    body,
    false)
ESTREE_NODE_4_ARGS(
    ForOfStatement, LoopStatement,
    NodePtr, left, false,
    NodePtr, right, false,
    NodePtr, body, false,
    NodeBoolean, await, false)
ESTREE_NODE_4_ARGS(
    ForStatement,
    LoopStatement,
    NodePtr,
    init,
    true,
    NodePtr,
    test,
    true,
    NodePtr,
    update,
    true,
    NodePtr,
    body,
    false)
ESTREE_LAST(LoopStatement)

ESTREE_NODE_0_ARGS(DebuggerStatement, Statement)
ESTREE_NODE_0_ARGS(EmptyStatement, Statement)
ESTREE_NODE_1_ARGS(BlockStatement, Statement, NodeList, body, false)
ESTREE_NODE_1_ARGS(BreakStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ContinueStatement, Statement, NodePtr, label, true)
ESTREE_NODE_1_ARGS(ThrowStatement, Statement, NodePtr, argument, false)
ESTREE_NODE_1_ARGS(ReturnStatement, Statement, NodePtr, argument, true)
ESTREE_NODE_2_ARGS(
    WithStatement,
    Statement,
    NodePtr,
    object,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    SwitchStatement,
    Statement,
    NodePtr,
    discriminant,
    false,
    NodeList,
    cases,
    false)

ESTREE_NODE_2_ARGS(
    LabeledStatement,
    Statement,
    NodePtr,
    label,
    false,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    ExpressionStatement,
    Statement,
    NodePtr,
    expression,
    false,
    NodeString,
    directive,
    true)

ESTREE_NODE_3_ARGS(
    TryStatement,
    Statement,
    NodePtr,
    block,
    false,
    NodePtr,
    handler,
    true,
    NodePtr,
    finalizer,
    true)

ESTREE_NODE_3_ARGS(
    IfStatement,
    Statement,
    NodePtr,
    test,
    false,
    NodePtr,
    consequent,
    false,
    NodePtr,
    alternate,
    true)

ESTREE_LAST(Statement)

ESTREE_NODE_0_ARGS(NullLiteral, Base)
ESTREE_NODE_1_ARGS(BooleanLiteral, Base, NodeBoolean, value, false)
ESTREE_NODE_1_ARGS(StringLiteral, Base, NodeString, value, false)
ESTREE_NODE_1_ARGS(NumericLiteral, Base, NodeNumber, value, false)
ESTREE_NODE_2_ARGS(
    RegExpLiteral,
    Base,
    NodeLabel,
    pattern,
    false,
    NodeLabel,
    flags,
    false)
ESTREE_NODE_1_ARGS(
    BigIntLiteral, Base,
    NodeLabel, bigint, false)

ESTREE_NODE_0_ARGS(ThisExpression, Base)
ESTREE_NODE_0_ARGS(Super, Base)
ESTREE_NODE_1_ARGS(SequenceExpression, Base, NodeList, expressions, false)
ESTREE_NODE_1_ARGS(ObjectExpression, Base, NodeList, properties, false)
ESTREE_NODE_2_ARGS(ArrayExpression, Base,
    NodeList, elements, false,
    NodeBoolean, trailingComma, false)

ESTREE_NODE_1_ARGS(
    SpreadElement, Base,
    NodePtr, argument, false)

ESTREE_NODE_3_ARGS(
    NewExpression, Base,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(NewExpression, typeArguments)
ESTREE_NODE_2_ARGS(
    YieldExpression, Base,
    NodePtr, argument, true,
    NodeBoolean, delegate, true)
ESTREE_NODE_1_ARGS(
    AwaitExpression, Base,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    ImportExpression, Base,
    NodePtr, source, false,
    NodePtr, attributes, true)

ESTREE_FIRST(CallExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    CallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false)
ESTREE_IGNORE_IF_EMPTY(CallExpression, typeArguments)

ESTREE_NODE_4_ARGS(
    OptionalCallExpression, CallExpressionLike,
    NodePtr, callee, false,
    NodePtr, typeArguments, true,
    NodeList, arguments, false,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(OptionalCallExpression, typeArguments)
ESTREE_LAST(CallExpressionLike)

ESTREE_NODE_3_ARGS(
    AssignmentExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false)

ESTREE_NODE_3_ARGS(
    UnaryExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_NODE_3_ARGS(
    UpdateExpression,
    Base,
    NodeLabel,
    operator,
    false,
    NodePtr,
    argument,
    false,
    NodeBoolean,
    prefix,
    false)

ESTREE_FIRST(MemberExpressionLike, Base)
ESTREE_NODE_3_ARGS(
    MemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false)

ESTREE_NODE_4_ARGS(
    OptionalMemberExpression, MemberExpressionLike,
    NodePtr, object, false,
    NodePtr, property, false,
    NodeBoolean, computed, false,
    NodeBoolean, optional, false)
ESTREE_LAST(MemberExpressionLike)

ESTREE_NODE_3_ARGS(
    LogicalExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_3_ARGS(
    ConditionalExpression,
    Base,
    NodePtr,
    test,
    false,
    NodePtr,
    alternate,
    false,
    NodePtr,
    consequent,
    false)

ESTREE_NODE_3_ARGS(
    BinaryExpression,
    Base,
    NodePtr,
    left,
    false,
    NodePtr,
    right,
    false,
    NodeLabel,
    operator,
    false)

ESTREE_NODE_1_ARGS(Directive, Base, NodePtr, value, false)
ESTREE_NODE_1_ARGS(DirectiveLiteral, Base, NodeString, value, false)

ESTREE_NODE_3_ARGS(
    Identifier, Base,
    NodeLabel, name, false,
    NodePtr, typeAnnotation, true,
    NodeBoolean, optional, false)
ESTREE_IGNORE_IF_EMPTY(Identifier, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(Identifier, optional)

ESTREE_NODE_1_ARGS(
    PrivateName, Base,
    NodePtr, id, false)

ESTREE_NODE_2_ARGS(
    MetaProperty,
    Base,
    NodePtr,
    meta,
    false,
    NodePtr,
    property,
    false)

ESTREE_NODE_2_ARGS(
    SwitchCase,
    Base,
    NodePtr,
    test,
    true,
    NodeList,
    consequent,
    false)

ESTREE_NODE_2_ARGS(
    CatchClause,
    Base,
    NodePtr,
    param,
    true,
    NodePtr,
    body,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclarator,
    Base,
    NodePtr,
    init,
    true,
    NodePtr,
    id,
    false)

ESTREE_NODE_2_ARGS(
    VariableDeclaration,
    Base,
    NodeLabel,
    kind,
    false,
    NodeList,
    declarations,
    false)

ESTREE_NODE_2_ARGS(TemplateLiteral, Base,
                   NodeList, quasis, false,
                   NodeList, expressions, false)

ESTREE_NODE_2_ARGS(TaggedTemplateExpression, Base,
                   NodePtr, tag, false,
                   NodePtr, quasi, false)

// In ESTree, it is defined as {tail : boolean,
//                              value : {cooked : string, raw : string}},
// we flatten the value field.
// If the template literal is tagged and the text has an invalid escape,
// cooked will be null.
ESTREE_NODE_3_ARGS(TemplateElement, Base,
                   NodeBoolean, tail, false,
                   NodeString, cooked, true,
                   NodeLabel, raw, false)

ESTREE_NODE_6_ARGS(
    Property, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, method, false,
    NodeBoolean, shorthand, false)

ESTREE_NODE_7_ARGS(
    ClassDeclaration, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, implements)
ESTREE_IGNORE_IF_EMPTY(ClassDeclaration, decorators)

ESTREE_NODE_7_ARGS(
    ClassExpression, Base,
    NodePtr, id, true,
    NodePtr, typeParameters, true,
    NodePtr, superClass, true,
    NodePtr, superTypeParameters, true,
    NodeList, implements, false,
    NodeList, decorators, false,
    NodePtr, body, false)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, typeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, superTypeParameters)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, implements)
ESTREE_IGNORE_IF_EMPTY(ClassExpression, decorators)

ESTREE_NODE_1_ARGS(
    ClassBody, Base,
    NodeList, body, false)

ESTREE_NODE_9_ARGS(
    ClassProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, computed, false,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassProperty, tsModifiers)

ESTREE_NODE_8_ARGS(
    ClassPrivateProperty, Base,
    NodePtr, key, false,
    NodePtr, value, true,
    NodeBoolean, static, false,
    NodeBoolean, declare, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true,
    NodePtr, typeAnnotation, true,
    NodePtr, tsModifiers, true)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, variance)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, optional)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, typeAnnotation)
ESTREE_IGNORE_IF_EMPTY(ClassPrivateProperty, tsModifiers)

ESTREE_NODE_5_ARGS(
    MethodDefinition, Base,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeLabel, kind, false,
    NodeBoolean, computed, false,
    NodeBoolean, static, false)

// Imports ========================================

ESTREE_NODE_4_ARGS(
    ImportDeclaration, Base,
    NodeList, specifiers, false,
    NodePtr, source, false,
    NodeList, assertions, true,
    NodeLabel, importKind, false)

ESTREE_NODE_3_ARGS(
    ImportSpecifier, Base,
    NodePtr, imported, false,
    NodePtr, local, false,
    NodeLabel, importKind, false)
ESTREE_NODE_1_ARGS(
    ImportDefaultSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ImportNamespaceSpecifier, Base,
    NodePtr, local, false)
ESTREE_NODE_2_ARGS(
    ImportAttribute, Base,
    NodePtr, key, false,
    NodePtr, value, false)


// ================================================

// Exports ========================================

ESTREE_NODE_4_ARGS(
    ExportNamedDeclaration, Base,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeLabel, exportKind, false)

ESTREE_NODE_2_ARGS(
    ExportSpecifier, Base,
    NodePtr, exported, false,
    NodePtr, local, false)
ESTREE_NODE_1_ARGS(
    ExportNamespaceSpecifier, Base,
    NodePtr, exported, false)
ESTREE_NODE_1_ARGS(
    ExportDefaultDeclaration, Base,
    NodePtr, declaration, false)
ESTREE_NODE_2_ARGS(
    ExportAllDeclaration, Base,
    NodePtr, source, false,
    NodeLabel, exportKind, false)

// ================================================

// Patterns =======================================
ESTREE_FIRST(Pattern, Base)

ESTREE_NODE_2_ARGS(
    ObjectPattern, Pattern,
    NodeList, properties, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ObjectPattern, typeAnnotation)

ESTREE_NODE_2_ARGS(
    ArrayPattern, Pattern,
    NodeList, elements, false,
    NodePtr, typeAnnotation, true)
ESTREE_IGNORE_IF_EMPTY(ArrayPattern, typeAnnotation)

ESTREE_NODE_1_ARGS(
    RestElement, Pattern,
    NodePtr, argument, false)

ESTREE_NODE_2_ARGS(
    AssignmentPattern, Pattern,
    NodePtr, left, false,          // Pattern
    NodePtr, right, false)         // Expression

ESTREE_LAST(Pattern)
// ================================================

// JSX ============================================

#if HERMES_PARSE_JSX

ESTREE_FIRST(JSX, Base)

ESTREE_NODE_1_ARGS(
    JSXIdentifier, JSX,
    NodeLabel, name, false)
ESTREE_NODE_2_ARGS(
    JSXMemberExpression, JSX,
    NodePtr, object, false,
    NodePtr, property, false)
ESTREE_NODE_2_ARGS(
    JSXNamespacedName, JSX,
    NodePtr, namespace, false,
    NodePtr, name, false)

ESTREE_NODE_0_ARGS(
    JSXEmptyExpression, JSX)
ESTREE_NODE_1_ARGS(
    JSXExpressionContainer, JSX,
    NodePtr, expression, false)
ESTREE_NODE_1_ARGS(
    JSXSpreadChild, JSX,
    NodePtr, expression, false)

ESTREE_NODE_4_ARGS(
    JSXOpeningElement, JSX,
    NodePtr, name, false,
    NodeList, attributes, false,
    NodeBoolean, selfClosing, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(JSXOpeningElement, typeArguments)
ESTREE_NODE_1_ARGS(
    JSXClosingElement, JSX,
    NodePtr, name, false)

ESTREE_NODE_2_ARGS(
    JSXAttribute, JSX,
    NodePtr, name, false,
    NodePtr, value, true)
ESTREE_NODE_1_ARGS(
    JSXSpreadAttribute, JSX,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    JSXStringLiteral, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_2_ARGS(
    JSXText, JSX,
    NodeString, value, false,
    NodeLabel, raw, false)

ESTREE_NODE_3_ARGS(
    JSXElement, JSX,
    NodePtr, openingElement, false,
    NodeList, children, false,
    NodePtr, closingElement, true)

ESTREE_NODE_3_ARGS(
    JSXFragment, JSX,
    NodePtr, openingFragment, false,
    NodeList, children, false,
    NodePtr, closingFragment, false)
ESTREE_NODE_0_ARGS(
    JSXOpeningFragment, JSX)
ESTREE_NODE_0_ARGS(
    JSXClosingFragment, JSX)

ESTREE_LAST(JSX)

#endif

// ================================================

// Types ==========================================

#if HERMES_PARSE_FLOW

ESTREE_FIRST(Flow, Base)

ESTREE_NODE_0_ARGS(ExistsTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(EmptyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(StringTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(NumberTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    StringLiteralTypeAnnotation, Flow,
    NodeString, value, false,
    NodeString, raw, false)
ESTREE_NODE_2_ARGS(
    NumberLiteralTypeAnnotation, Flow,
    NodeNumber, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_1_ARGS(
    BigIntLiteralTypeAnnotation, Flow,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(BooleanTypeAnnotation, Flow)
ESTREE_NODE_2_ARGS(
    BooleanLiteralTypeAnnotation, Flow,
    NodeBoolean, value, false,
    NodeLabel, raw, false)
ESTREE_NODE_0_ARGS(NullLiteralTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(SymbolTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(AnyTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(MixedTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(BigIntTypeAnnotation, Flow)
ESTREE_NODE_0_ARGS(VoidTypeAnnotation, Flow)
ESTREE_NODE_5_ARGS(
    FunctionTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, this, true,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_4_ARGS(
    HookTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    FunctionTypeParam, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ComponentTypeAnnotation, Flow,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_3_ARGS(
    ComponentTypeParameter, Flow,
    NodePtr, name, true,
    NodePtr, typeAnnotation, false,
    NodeBoolean, optional, false)
ESTREE_NODE_1_ARGS(
    NullableTypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TypeofTypeAnnotation, Flow,
    NodePtr, argument, false,
    NodePtr, typeArguments, true)
ESTREE_IGNORE_IF_EMPTY(TypeofTypeAnnotation, typeArguments)
ESTREE_NODE_1_ARGS(
    KeyofTypeAnnotation, Flow,
    NodePtr, argument, false)
ESTREE_NODE_2_ARGS(
    TypeOperator, Flow,
    NodeLabel, operator, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    QualifiedTypeofIdentifier, Flow,
    NodePtr, qualification, false,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    TupleTypeAnnotation, Flow,
    NodeList, types, false,
    NodeBoolean, inexact, false)
ESTREE_NODE_2_ARGS(
    TupleTypeSpreadElement, Flow,
    NodePtr, label, true,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_4_ARGS(
    TupleTypeLabeledElement, Flow,
    NodePtr, label, false,
    NodePtr, elementType, false,
    NodeBoolean, optional, false,
    NodePtr, variance, true)
ESTREE_NODE_1_ARGS(
    ArrayTypeAnnotation, Flow,
    NodePtr, elementType, false)
ESTREE_NODE_1_ARGS(
    InferTypeAnnotation, Flow,
    NodePtr, typeParameter, false)
ESTREE_NODE_1_ARGS(
    UnionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    IntersectionTypeAnnotation, Flow,
    NodeList, types, false)
ESTREE_NODE_2_ARGS(
    GenericTypeAnnotation, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    IndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_3_ARGS(
    OptionalIndexedAccessType, Flow,
    NodePtr, objectType, false,
    NodePtr, indexType, false,
    NodeBoolean, optional, false)
ESTREE_NODE_4_ARGS(
    ConditionalTypeAnnotation, Flow,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)
ESTREE_NODE_3_ARGS(
    TypePredicate, Flow,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, true,
    NodeString, kind, true)

ESTREE_NODE_2_ARGS(
    InterfaceTypeAnnotation, Flow,
    NodeList, extends, false,
    NodePtr, body, true)

ESTREE_NODE_3_ARGS(
    TypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    OpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, false,
    NodePtr, supertype, true)

ESTREE_NODE_4_ARGS(
    InterfaceDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    DeclareTypeAlias, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, right, false)
ESTREE_NODE_4_ARGS(
    DeclareOpaqueType, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, impltype, true,
    NodePtr, supertype, true)
ESTREE_NODE_4_ARGS(
    DeclareInterface, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodePtr, body, false)
ESTREE_NODE_6_ARGS(
    DeclareClass, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodeList, extends, false,
    NodeList, implements, false,
    NodeList, mixins, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareFunction, Flow,
    NodePtr, id, false,
    NodePtr, predicate, true)
ESTREE_NODE_1_ARGS(
    DeclareHook, Flow,
    NodePtr, id, false)
ESTREE_NODE_5_ARGS(
    DeclareComponent, Flow,
    NodePtr, id, false,
    NodeList, params, false,
    NodePtr, rest, true,
    NodePtr, typeParameters, true,
    NodePtr, rendersType, true)
ESTREE_NODE_2_ARGS(
    DeclareVariable, Flow,
    NodePtr, id, false,
    NodeLabel, kind, false)
ESTREE_NODE_2_ARGS(
    DeclareEnum, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_4_ARGS(
    DeclareExportDeclaration, Flow,
    NodePtr, declaration, true,
    NodeList, specifiers, false,
    NodePtr, source, true,
    NodeBoolean, default, false)
ESTREE_NODE_1_ARGS(
    DeclareExportAllDeclaration, Flow,
    NodePtr, source, false)
ESTREE_NODE_2_ARGS(
    DeclareModule, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_2_ARGS(
    DeclareNamespace, Flow,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    DeclareModuleExports, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_2_ARGS(
    InterfaceExtends, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_2_ARGS(
    ClassImplements, Flow,
    NodePtr, id, false,
    NodePtr, typeParameters, true)

ESTREE_NODE_1_ARGS(
    TypeAnnotation, Flow,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_6_ARGS(
    ObjectTypeAnnotation, Flow,
    NodeList, properties, false,
    NodeList, indexers, false,
    NodeList, callProperties, false,
    NodeList, internalSlots, false,
    NodeBoolean, inexact, false,
    NodeBoolean, exact, false)
ESTREE_NODE_8_ARGS(
    ObjectTypeProperty, Flow,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, method, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, proto, false,
    NodePtr, variance, true,
    NodeLabel, kind, false)
ESTREE_NODE_1_ARGS(
    ObjectTypeSpreadProperty, Flow,
    NodePtr, argument, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeInternalSlot, Flow,
    NodePtr, id, false,
    NodePtr, value, false,
    NodeBoolean, optional, false,
    NodeBoolean, static, false,
    NodeBoolean, method, false)
ESTREE_NODE_2_ARGS(
    ObjectTypeCallProperty, Flow,
    NodePtr, value, false,
    NodeBoolean, static, false)
ESTREE_NODE_5_ARGS(
    ObjectTypeIndexer, Flow,
    NodePtr, id, true,
    NodePtr, key, false,
    NodePtr, value, false,
    NodeBoolean, static, false,
    NodePtr, variance, true)
ESTREE_NODE_5_ARGS(
    ObjectTypeMappedTypeProperty, Flow,
    NodePtr, keyTparam, false,
    NodePtr, propType, false,
    NodePtr, sourceType, false,
    NodePtr, variance, true,
    NodeString, optional, true)

ESTREE_NODE_1_ARGS(
    Variance, Flow,
    NodeLabel, kind, false)

ESTREE_NODE_1_ARGS(
    TypeParameterDeclaration, Flow,
    NodeList, params, false)
ESTREE_NODE_5_ARGS(
    TypeParameter, Flow,
    NodeLabel, name, false,
    NodePtr, bound, true,
    NodePtr, variance, true,
    NodePtr, default, true,
    NodeBoolean, usesExtendsBound, false)
ESTREE_IGNORE_IF_EMPTY(TypeParameter, usesExtendsBound)
ESTREE_NODE_1_ARGS(
    TypeParameterInstantiation, Flow,
    NodeList, params, false)

ESTREE_NODE_2_ARGS(
    TypeCastExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_2_ARGS(
    AsExpression, Flow,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)
ESTREE_NODE_1_ARGS(
    AsConstExpression, Flow,
    NodePtr, expression, false)

ESTREE_NODE_0_ARGS(InferredPredicate, Flow)
ESTREE_NODE_1_ARGS(
    DeclaredPredicate, Flow,
    NodePtr, value, false)

ESTREE_NODE_2_ARGS(
    EnumDeclaration, Flow,
    NodePtr, id, false,
    NodePtr, body, false)

ESTREE_NODE_3_ARGS(
    EnumStringBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumNumberBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBigIntBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_3_ARGS(
    EnumBooleanBody, Flow,
    NodeList, members, false,
    NodeBoolean, explicitType, false,
    NodeBoolean, hasUnknownMembers, false)
ESTREE_NODE_2_ARGS(
    EnumSymbolBody, Flow,
    NodeList, members, false,
    NodeBoolean, hasUnknownMembers, false)

ESTREE_NODE_1_ARGS(
    EnumDefaultedMember, Flow,
    NodePtr, id, false)
ESTREE_NODE_2_ARGS(
    EnumStringMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumNumberMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBigIntMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_2_ARGS(
    EnumBooleanMember, Flow,
    NodePtr, id, false,
    NodePtr, init, false)
ESTREE_NODE_3_ARGS(
    ComponentParameter, Flow,
    NodePtr, name, false,
    NodePtr, local, false,
    NodeBoolean, shorthand, false)

ESTREE_LAST(Flow)

#endif

#if HERMES_PARSE_TS

ESTREE_FIRST(TS, Base)

ESTREE_NODE_1_ARGS(
    TSTypeAnnotation, TS,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_0_ARGS(TSAnyKeyword, TS)
ESTREE_NODE_0_ARGS(TSNumberKeyword, TS)
ESTREE_NODE_0_ARGS(TSBooleanKeyword, TS)
ESTREE_NODE_0_ARGS(TSStringKeyword, TS)
ESTREE_NODE_0_ARGS(TSSymbolKeyword, TS)
ESTREE_NODE_0_ARGS(TSVoidKeyword, TS)
ESTREE_NODE_0_ARGS(TSUndefinedKeyword, TS)
ESTREE_NODE_0_ARGS(TSUnknownKeyword, TS)
ESTREE_NODE_0_ARGS(TSNeverKeyword, TS)
ESTREE_NODE_0_ARGS(TSBigIntKeyword, TS)
ESTREE_NODE_0_ARGS(TSThisType, TS)
ESTREE_NODE_1_ARGS(
    TSLiteralType, TS,
    NodePtr, literal, false)
ESTREE_NODE_2_ARGS(
    TSIndexedAccessType, TS,
    NodePtr, objectType, false,
    NodePtr, indexType, false)
ESTREE_NODE_1_ARGS(
    TSArrayType, TS,
    NodePtr, elementType, false)
ESTREE_NODE_2_ARGS(
    TSTypeReference, TS,
    NodePtr, typeName, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSQualifiedName, TS,
    NodePtr, left, false,
    NodePtr, right, true)

ESTREE_NODE_3_ARGS(
    TSFunctionType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_3_ARGS(
    TSConstructorType, TS,
    NodeList, params, false,
    NodePtr, returnType, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSTypePredicate, TS,
    NodePtr, parameterName, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_1_ARGS(
    TSTupleType, TS,
    NodeList, elementTypes, false)

ESTREE_NODE_2_ARGS(
    TSTypeAssertion, TS,
    NodePtr, typeAnnotation, false,
    NodePtr, expression, false)
ESTREE_NODE_2_ARGS(
    TSAsExpression, TS,
    NodePtr, expression, false,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_5_ARGS(
    TSParameterProperty, TS,
    NodePtr, parameter, false,
    NodeLabel, accessibility, true,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)

ESTREE_NODE_3_ARGS(
    TSTypeAliasDeclaration, TS,
    NodePtr, id, false,
    NodePtr, typeParameters, true,
    NodePtr, typeAnnotation, false)

ESTREE_NODE_4_ARGS(
    TSInterfaceDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false,
    NodeList, extends, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_2_ARGS(
    TSInterfaceHeritage, TS,
    NodePtr, expression, false,
    NodePtr, typeParameters, true)
ESTREE_NODE_1_ARGS(
    TSInterfaceBody, TS,
    NodeList, body, false)

ESTREE_NODE_2_ARGS(
    TSEnumDeclaration, TS,
    NodePtr, id, false,
    NodeList, members, false)
ESTREE_NODE_2_ARGS(
    TSEnumMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_2_ARGS(
    TSModuleDeclaration, TS,
    NodePtr, id, false,
    NodePtr, body, false)
ESTREE_NODE_1_ARGS(
    TSModuleBlock, TS,
    NodeList, body, false)
ESTREE_NODE_2_ARGS(
    TSModuleMember, TS,
    NodePtr, id, false,
    NodePtr, initializer, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterDeclaration, TS,
    NodeList, params, false)
ESTREE_NODE_3_ARGS(
    TSTypeParameter, TS,
    NodePtr, name, false,
    NodePtr, constraint, true,
    NodePtr, default, true)

ESTREE_NODE_1_ARGS(
    TSTypeParameterInstantiation, TS,
    NodeList, params, false)

ESTREE_NODE_1_ARGS(
    TSUnionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSIntersectionType, TS,
    NodeList, types, false)
ESTREE_NODE_1_ARGS(
    TSTypeQuery, TS,
    NodePtr, exprName, false)
ESTREE_NODE_4_ARGS(
    TSConditionalType, TS,
    NodePtr, checkType, false,
    NodePtr, extendsType, false,
    NodePtr, trueType, false,
    NodePtr, falseType, false)

ESTREE_NODE_1_ARGS(
    TSTypeLiteral, TS,
    NodeList, members, false)
ESTREE_NODE_8_ARGS(
    TSPropertySignature, TS,
    NodePtr, key, false,
    NodePtr, typeAnnotation, true,
    NodePtr, initializer, true,
    NodeBoolean, optional, false,
    NodeBoolean, computed, false,
    NodeBoolean, readonly, false,
    NodeBoolean, static, false,
    NodeBoolean, export, false)
ESTREE_NODE_4_ARGS(
    TSMethodSignature, TS,
    NodePtr, key, false,
    NodeList, params, false,
    NodePtr, returnType, true,
    NodeBoolean, computed, false)
ESTREE_NODE_2_ARGS(
    TSIndexSignature, TS,
    NodeList, parameters, false,
    NodePtr, typeAnnotation, true)
ESTREE_NODE_2_ARGS(
    TSCallSignatureDeclaration, TS,
    NodeList, params, false,
    NodePtr, returnType, true)

ESTREE_NODE_2_ARGS(
    TSModifiers, TS,
    NodeLabel, accessibility, false,
    NodeBoolean, readonly, false)

ESTREE_LAST(TS)

#endif

// ================================================

#ifndef ESTREE_DEFINE_COVER_NODES

ESTREE_FIRST(Cover, Base)

// CoverParenthesizedExpressionAndArrowParameterList: "(" ")"
ESTREE_NODE_0_ARGS(CoverEmptyArgs, Cover)

// CoverParenthesizedExpressionAndArrowParameterList:
//      "(" Expression "," ")"
// This is the dummy "empty expression" for the last comma inside a
// SequenceExpression.
ESTREE_NODE_0_ARGS(CoverTrailingComma, Cover)

// CoverInitializer
// This is used for destructuring object assignment with initializers. It
// will be the value node of a Property.
ESTREE_NODE_1_ARGS(
    CoverInitializer, Cover,
    NodePtr, init, false)

// CoverRestElement
// This is used for parsing "...elem" in "()" and in SequenceExpression, so it
// can later be reparsed as an arrow function rest parameter. "rest" will point
// to the actual RestElement.
ESTREE_NODE_1_ARGS(
    CoverRestElement, Cover,
    NodePtr, rest, false)

// CoverTypedIdentifier
// This is used for parsing "ident: type" as either a type cast expression
// or a typed parameter in the parameters list of an arrow function.
// 'left' is the identifier which is typed.
// 'right' is the type which is either the cast target or the type annotation,
//   which may be null if the identifier was simply given a '?' and no ':'
//   with a type annotation.
ESTREE_NODE_3_ARGS(
    CoverTypedIdentifier, Cover,
    NodePtr, left, false,
    NodePtr, right, true,
    NodeBoolean, optional, false)

ESTREE_LAST(Cover)

#endif

#undef ESTREE_FIRST
#undef ESTREE_LAST
#undef ESTREE_WRAP
#undef ESTREE_IGNORE_IF_EMPTY

#undef ESTREE_NODE_0_ARGS
#undef ESTREE_NODE_1_ARGS
#undef ESTREE_NODE_2_ARGS
#undef ESTREE_NODE_3_ARGS
#undef ESTREE_NODE_4_ARGS
#undef ESTREE_NODE_5_ARGS
#undef ESTREE_NODE_6_ARGS
#undef ESTREE_NODE_7_ARGS
#undef ESTREE_NODE_8_ARGS
#undef ESTREE_NODE_9_ARGS
  }
}

/// Return a reference to the parameter list of a FunctionLikeNode.
NodeList &getParams(FunctionLikeNode *node);

/// If the body of the function-like node is a block statement, return it,
/// otherwise return nullptr.
/// ProgramNode doesn't have a block statement body, as well as some arrow
/// functions.
BlockStatementNode *getBlockStatement(FunctionLikeNode *node);

/// \return the object of the member expression node.
Node *getObject(MemberExpressionLikeNode *node);

/// \return the property of the member expression node.
Node *getProperty(MemberExpressionLikeNode *node);

/// \return whether the member expression node is computed.
NodeBoolean getComputed(MemberExpressionLikeNode *node);

/// \return the callee of the call.
Node *getCallee(CallExpressionLikeNode *node);

/// \return the arguments list of the call.
NodeList &getArguments(CallExpressionLikeNode *node);

/// \return true when \p node has simple params, i.e. no destructuring and no
/// initializers.
bool hasSimpleParams(FunctionLikeNode *node);

/// \return true when \p node has parameter expressions.
bool hasParamExpressions(FunctionLikeNode *node);

/// \return true when \p node is a generator function.
bool isGenerator(FunctionLikeNode *node);

/// \return true when \p node is an async function.
bool isAsync(FunctionLikeNode *node);

/// Allow using \p NodeKind in \p llvh::DenseMaps.
struct NodeKindInfo : llvh::DenseMapInfo<NodeKind> {
  static inline NodeKind getEmptyKey() {
    return (NodeKind)(-1);
  }
  static inline NodeKind getTombstoneKey() {
    return (NodeKind)(-2);
  }
  static inline bool isEqual(const NodeKind &a, const NodeKind &b) {
    return a == b;
  }
  static unsigned getHashValue(const NodeKind &Val) {
    return (unsigned)Val;
  }
};

using NodeKindSet = llvh::DenseSet<ESTree::NodeKind, NodeKindInfo>;

/// An arbitrary limit to nested assignments. We handle them non-recursively, so
/// this can be very large, but we don't want to let it consume all our memory.
constexpr unsigned MAX_NESTED_ASSIGNMENTS = 30000;

/// An arbitrary limit to nested "+/-" binary expressions. We handle them
/// non-recursively, so this can be very large, but we don't want to let it
/// consume all our memory.
constexpr unsigned MAX_NESTED_BINARY = 30000;

/// Check if an AST node is of the specified type and its `_operator`
/// attribute is within the set of allowed operators.
template <class N>
static N *checkExprOperator(
    ESTree::Node *e,
    llvh::ArrayRef<llvh::StringRef> ops) {
  if (auto *n = llvh::dyn_cast<N>(e)) {
    if (std::find(ops.begin(), ops.end(), n->_operator->str()) != ops.end())
      return n;
  }
  return nullptr;
}

/// Convert a recursive expression of the form ((a + b) + c) + d) into a list
/// `a, b, c, d`. This description of the list is for exposition purposes, but
/// the actual list contains pointers to each binop node:
///    `list = [(a + b), (list[0] + c), (list[1] + d)`.
/// Note that the list is only three elements long and the first element is
/// accessible through the `_left` pointer of `list[0]`.
///
/// \param ops - the acceptable values for the `_operator` attribute of the
///     expression. Ideally it should contain all operators with the same
///     precedence: ["+", "-"] or ["*", "/", "%"], etc.
template <class N>
static llvh::SmallVector<N *, 1> linearizeLeft(
    N *e,
    llvh::ArrayRef<llvh::StringRef> ops) {
  llvh::SmallVector<N *, 1> vec;

  vec.push_back(e);
  while (auto *left = checkExprOperator<N>(e->_left, ops)) {
    e = left;
    vec.push_back(e);
  }

  std::reverse(vec.begin(), vec.end());
  return vec;
}

/// Convert a recursive expression of the form (a = (b = (c = d))) into a list
/// `a, b, c, d`. This description of the list is for exposition purposes, but
/// the actual list contains pointers to each node:
///    `list = [(a = list[1]), (b = list[2]), (c = d)]`.
/// Note that the list is only three elements long and the last element is
/// accessible through the `_right` pointer of `list[2]`.
///
/// \param ops - the acceptable values for the `_operator` attribute of the
///     expression. Ideally it should contain all operators with the same
///     precedence, but can also be a single operator like ["="], if the caller
///     doesn't want to deal with the complexity.
template <class N>
static llvh::SmallVector<N *, 1> linearizeRight(
    N *e,
    llvh::ArrayRef<llvh::StringRef> ops) {
  llvh::SmallVector<N *, 1> vec;

  vec.push_back(e);
  while (auto *right = checkExprOperator<N>(e->_right, ops)) {
    e = right;
    vec.push_back(e);
  }

  return vec;
}

} // namespace ESTree
} // namespace hermes

#endif
