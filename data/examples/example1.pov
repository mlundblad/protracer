// Params : -x 240 -y 240 -w 1 -z 1
// Infile : v1ex1.pov
// Outfile: v1ex1.ppm

background { color rgb <0.27, 0.27, 0.27> }

camera {
	location <-30, 50, 50>
	sky <0, 1, 0>
	look_at <0, -5, 116>
}

light_source { <-30, 50, 50> }

sphere {
	<0, -5, 116>, 12
	pigment { 
		color rgb <0.6, 0.23, 0.23>
	}
}

sphere {
	<-10, 7, 118>, 8
	pigment { color rgb <0.04, 0.62, 0.04> }
}

sphere {
	<10, 7, 118>, 8
	pigment { color rgb <0.04, 0.62, 0.04> }
}

sphere {
	<4, -2, 105>, 1.5
	pigment { color rgb <0.16, 0.16, 0.16> }
}

sphere {
	<-4, -2, 105>, 1.5
	pigment { color rgb <0.16, 0.16, 0.16> }
}

sphere {
	<0, -5, 104>, 2.5
	pigment { color rgb <0.35, 0.16, 0.16> }
}

sphere {
	<-6, -9, 105>, 0.5
	pigment { color rgb <0, 0, 0> }
}

sphere {
	<6, -9, 105>, 0.5
	pigment { color rgb <0, 0, 0> }
}

sphere {
	<0, -11, 105>, 0.5
	pigment { color rgb <0, 0, 0> }
}
