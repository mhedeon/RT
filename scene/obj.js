{
	"camera" : [
		{
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
			"reflaction" :
			"specular" :
			"slice" : {
				"point" : [0, 1, 2],
				"axis" : [0, 1, 1],
				"type" : "own" / "real"
			}
		},
		{
			"type" : "bocal",
			"center" : [0, 0, 20],
			"size" : 1,
			"color" : [255, 0, 255],
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
			"type" : "ambient",
			"intensity" : 0.8
		},
		{
			"type" : "point",
			"intensity" : 0.8,
			"position" : [-2, 5, 20]
		},
		{
			"type" : "parallel",
			"intensity" : 0.8,
			"rotation" : [0, 0, 1],  
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
