# re-robinhood

![screenshot](/docs/screenshot.png)

A web app for tracking stocks made with the following:

* ReasonML
* reason-react
* bucklescript
* apollo-client
* robinhood-graph
* CSS grid
* parcel

## Setup

First set up [robinhood-graph](https://github.com/bbohen/robinhood-graph) locally for data.

```shell
# /robinhood-graph
npm start
```

After cloning this repository run the following.

```shell
# /re-robinhood
npm install

# Build with BSB
npm start

# In a seperate tab, kick off parcel dev server
npm run dev

# View the app at http://localhost:1234
```
