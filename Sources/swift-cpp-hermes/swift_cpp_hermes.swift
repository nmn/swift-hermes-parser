// The Swift Programming Language
// https://docs.swift.org/swift-book

import cxxHermesForSwift
import Foundation

struct Greet {
    let name: String
    let greeting: String
    let greeter: Greeter

    init(name: String, greeting: String) {
        self.name = name
        self.greeting = greeting
        greeter = Greeter(std.__1.string(name))

        var codeGenSettings = hermes.CodeGenerationSettings()
        codeGenSettings.dumpAfter = hermes.CodeGenerationSettings_DumpSettings()

        let jsParser = hermes.parser.JSParser()
    }

    func greet() -> String {
        return String(greeter.greet())
    }
}
