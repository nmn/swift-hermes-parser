// swift-tools-version: 6.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-cpp-hermes",
    platforms: [
        .macOS(.v15),
    ],
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "swift-cpp-hermes",
            targets: ["swift-cpp-hermes"]
        ),
    ],
    dependencies: [],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.

        .target(
            name: "cxxHermesForSwift",
            path: "Sources/cxxHermesForSwift",
            sources: ["Greeter.cpp"],
            publicHeadersPath: "include",
            cxxSettings: [
                .unsafeFlags(["-std=c++17"]),
                .headerSearchPath("include"), // maybe?
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),

        .target(
            name: "swift-cpp-hermes",
            dependencies: [
                "cxxHermesForSwift",
            ],
            path: "Sources/swift-cpp-hermes",
            cxxSettings: [
                .unsafeFlags(["-std=c++17"]),
                .headerSearchPath("include"), // maybe?
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),

        .testTarget(
            name: "swift-cpp-hermesTests",
            dependencies: ["swift-cpp-hermes"]
        ),
    ]
)
