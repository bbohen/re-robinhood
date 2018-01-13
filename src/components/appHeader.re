let component = ReasonReact.statelessComponent("AppHeader");

let make = (~onThemeToggle, ~isDarkTheme, _children) => {
  ...component,
  render: (_self) => {
    let seperatorContent = isDarkTheme ? "[  >]" : "[<  ]";
    <div className="app-header no-select">
      <span id="app-title"> (ReasonReact.stringToElement("reason-react-robinhood")) </span>
      <span onClick=onThemeToggle>
        <span> (ReasonReact.stringToElement("Light ")) </span>
        <span> (ReasonReact.stringToElement(seperatorContent)) </span>
        <span> (ReasonReact.stringToElement(" Dark")) </span>
      </span>
    </div>
  }
};