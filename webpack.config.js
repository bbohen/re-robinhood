const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  entry: "./src/root.bs.js",
  output: {
    path: path.join(__dirname, "build"),
    filename: "index.js"
  },
  plugins: [
    new HtmlWebpackPlugin({
      title: "Reason Apollo Robinhood",
      template: "template.html"
    })
  ],
  devServer: {
    contentBase: path.join(__dirname, "build"),
    compress: true,
    port: 9000
  }
};
