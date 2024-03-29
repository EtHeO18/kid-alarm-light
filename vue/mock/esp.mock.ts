export default [
  {
    url: '/program',
    method: 'get',
    response: ({ query }) => {
        return [
            {"weekday": 1, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
            {"weekday": 1, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
            {"weekday": 2, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
            {"weekday": 2, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
            {"weekday": 3, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
            {"weekday": 3, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
            {"weekday": 4, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
            {"weekday": 4, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255}
        ];

    },
  },

  {
    url: '/program',
    method: 'post',
    response: ({query}) => {
      return "";
    },
  }
];