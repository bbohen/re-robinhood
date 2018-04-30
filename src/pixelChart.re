type pixelCharts = (array(int), int, string) => unit;

[@bs.module "pixel-charts"] external pixelCharts : pixelCharts = "default";

let component = ReasonReact.statelessComponent("PixelChart");

let make = (~chartId: string, ~values, _children) => {
  ...component,
  didUpdate: _self => {
    /* TODO: This is bad, but the usage of raw doesnt work without the log :| */
    Js.log(pixelCharts);
    let hackyWrapper = [%raw
      {|
        function(values, chartId) {
          PixelCharts.default(values, 6000, 10, chartId)
        }
      |}
    ];
    hackyWrapper(values, chartId);
  },
  render: _self => <div id=chartId className="pixel-chart line-chart" />,
};
