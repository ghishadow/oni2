open Oni_Core;
open Oni_UI;
open BenchFramework;

open Revery.UI;

let rootNode = (new node)();

let setup = () => ();

/* Create a state with some editor size */
let simpleState =
  Reducer.reduce(
    State.create(),
    Actions.SetEditorSize(
      Types.EditorSize.create(~pixelWidth=1600, ~pixelHeight=1200, ()),
    ),
  );
let simpleState =
  Reducer.reduce(
    simpleState,
    Actions.SetEditorFont(
      Types.EditorFont.create(
        ~fontFile="dummy",
        ~fontSize=14,
        ~measuredWidth=14,
        ~measuredHeight=14,
        (),
      ),
    ),
  );

let thousandLines =
  Array.make(1000, "This is a buffer with a thousand lines!") |> Array.to_list;

let thousandLineState =
  Reducer.reduce(
    simpleState,
    Actions.BufferUpdate(
      Types.BufferUpdate.create(
        ~startLine=0,
        ~endLine=1,
        ~lines=thousandLines,
        ~version=1,
        (),
      ),
    ),
  );

let hundredThousandLines =
  Array.make(100000, "This is a buffer with a hundred thousand lines!")
  |> Array.to_list;
let hundredThousandLineState =
  Reducer.reduce(
    simpleState,
    Actions.BufferUpdate(
      Types.BufferUpdate.create(
        ~startLine=0,
        ~endLine=1,
        ~lines=hundredThousandLines,
        ~version=1,
        (),
      ),
    ),
  );

let editorSurfaceMinimalState = () => {
  let _ =
    React.RenderedElement.render(
      rootNode,
      <EditorSurface state=simpleState />,
    );
  ();
};

let editorSurfaceThousandLineState = () => {
  let _ =
    React.RenderedElement.render(
      rootNode,
      <EditorSurface state=thousandLineState />,
    );
  ();
};

let editorSurfaceHundredThousandLineState = () => {
  let _ =
    React.RenderedElement.render(
      rootNode,
      <EditorSurface state=hundredThousandLineState />,
    );
  ();
};

let options = Reperf.Options.create(~iterations=10, ());

bench(
  ~name="EditorSurface: Minimal state",
  ~options,
  ~setup,
  ~f=editorSurfaceMinimalState,
  (),
);
bench(
  ~name="EditorSurface: 1000 Lines state",
  ~options,
  ~setup,
  ~f=editorSurfaceThousandLineState,
  (),
);
bench(
  ~name="EditorSurface: 100000 Lines state",
  ~options,
  ~setup,
  ~f=editorSurfaceHundredThousandLineState,
  (),
);
