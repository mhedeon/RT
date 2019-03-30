{
  "camera" : [
    {
      "origin" : [0,0,0],
      "direction" : [0, 0, 0],
	    "position" : [-4, 7, -15],
	    "angle_y" : 20,
	    "angle_x" : -10
    }
  ],
  "objects" : [
    {
      "type" : "sphere",
      "origin" : [0, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 255],
      "texture" : "chessboard"
    },
    {
      "type" : "sphere",
      "origin" : [-2, -2, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "perlin"
    }
  ],
  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, 5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, -5, 20]
    },
    {
      "type" : "direct",
      "intensity" : 0.8,
      "position" : [-2, 0, -20],
	    "rotation" : [0, 0, 1],
	    "angle" : 0.1
    }
  ]
}