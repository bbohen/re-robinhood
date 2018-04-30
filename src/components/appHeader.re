let component = ReasonReact.statelessComponent("AppHeader");

let make = (~onThemeToggle, ~isDarkTheme, _children) => {
  ...component,
  render: (_self) => {
    let seperatorContent = isDarkTheme ? "[  >]" : "[<  ]";
    <div className="app-header no-select">
      <span id="app-title"> (ReasonReact.string("re-robinhood")) </span>
      <span onClick=onThemeToggle>
        <span> (ReasonReact.string("Light ")) </span>
        <span> (ReasonReact.string(seperatorContent)) </span>
        <span> (ReasonReact.string(" Dark")) </span>
      </span>
    </div>
  }
};