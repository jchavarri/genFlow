/***
 * Copyright 2004-present Facebook. All Rights Reserved.
 */

let root =
  Filename.(
    Sys.executable_name |> dirname |> dirname |> dirname |> dirname |> dirname
  );

let project = Filename.concat(root, "sample-project");

let outputDir =
  Filename.(List.fold_left(concat, project, ["src", "__generated_flow__"]));

let outputDirLib =
  Filename.(
    List.fold_left(concat, root, ["lib", "bs", "js", "__generated_flow__"])
  );

let createModulesMap = modulesMapFile =>
  switch (modulesMapFile) {
  | None => GenFlowMain.StringMap.empty
  | Some(filePath) =>
    let s = GenFlowMain.GeneratedReFiles.readFile(filePath);
    Str.split(Str.regexp("\n"), s)
    |> List.fold_left(
         (map, nextPairStr) =>
           if (nextPairStr != "") {
             let fromTo =
               Str.split(Str.regexp("="), nextPairStr) |> Array.of_list;
             assert(Array.length(fromTo) === 2);
             let k: string = fromTo[0];
             let v: string = fromTo[1];
             GenFlowMain.StringMap.add(k, v, map);
           } else {
             map;
           },
         GenFlowMain.StringMap.empty,
       );
  };

let findCmtFiles = (): list(string) => {
  open Filename;
  let src = ["lib", "bs", "src"] |> List.fold_left(concat, project);
  ["Index.cmt", "Component1.cmt", "Component2.cmt"] |> List.map(concat(src));
};

let fileHeader =
  BuckleScriptPostProcessLib.Patterns.generatedHeaderPrefix ++ "\n\n";

let signFile = s => s;

let buildSourceFiles = () => ();
/* TODO */

let buildGeneratedFiles = () => ();
/* TODO */

let modulesMap = ref(None);
let cli = () => {
  let setModulesMap = s => modulesMap := Some(s);
  let speclist = [
    (
      "--modulesMap",
      Arg.String(setModulesMap),
      "Specify map file to override the JS module resolution for dependencies that would"
      ++ " normally be generated by genFlow but are not available for whatever reason."
      ++ " Example(--modulesMap map.txt) where each line is of the form 'ModuleFlow.bs=SomeShim'. "
      ++ "E.g. 'ReasonReactFlow.bs=ReasonReactShim'.",
    ),
  ];
  let usage = "genFlow";
  Arg.parse(speclist, print_endline, usage);
  let modulesMap = createModulesMap(modulesMap^);
  GenFlowMain.run(
    ~outputDir,
    ~fileHeader,
    ~signFile,
    ~modulesMap,
    ~findCmtFiles,
    ~buildSourceFiles,
    ~buildGeneratedFiles,
  );
};

cli();