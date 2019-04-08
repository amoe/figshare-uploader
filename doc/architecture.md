# Architecture

We attempt to follow MVP -- model-view-presenter.

The only thing that the view will do is calling a presenter method every time
there is a user action (a button click for example).

The presenter is responsible to act as the middleman between view and model. It
retrieves data from the model and returns it formatted to the view

Also, unlike the typical MVC, it decides what happens when you interact with the
view. So it will have a method for each possible action the user can do.

This means the view can be fully mocked out.

The `ViewImpl` is a `QWidget`, so nonlocal control can be effected by emitting
signals from child components to slots on the view.

Sometimes we connect signals directly to methods on the presenter using
`SlotAdapter`.  This is just a shorthand for creating simple delegation methods
on the `View`.


The top-level view can set up connections through accessors?

Passive View: The View is as dumb as possible and contains almost zero
logic. The Presenter is a middle man that talks to the View and the Model. The
View and Model are completely shielded from one another. 


 In Passive
View there is no direct data binding, instead the View exposes setter properties
which the Presenter uses to set the data. All state is managed in the Presenter
and not the View.

    Pro: maximum testability surface; clean separation of the View and Model
    Con: more work (for example all the setter properties) as you are doing all the data binding yourself.

No events? -- 

The Model does not need to raise events because it can only be changed through
calls from the Presenter anyway.  So the Presenter always knows when an event
has happened.

The controller then updates the model, and then handles the reloading of the
view from the model.  So you do NOT need events to be emitted by the model,
although Android implementations sometimes to this.

The wiring is always explicit and always passes through those layers.

