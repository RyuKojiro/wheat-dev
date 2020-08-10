$fn = 60;

difference() {
	cube([2+2+37+2+2,10, 1]);

	/*
	 * Wheat mounting posts
	 * 
	 * These are the posts on the corner with the DC input. The posts are 37mm
	 * apart, and the holes are 4mm.
	 */
	translate([4,4,0]) {
		cylinder(r=2);
		translate ([37,0,0]) cylinder(r=2);
	}
}
