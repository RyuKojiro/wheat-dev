$fn = 60;

module pcb() {
	translate([3, 10, 0])
	difference() {
		//color("Blue")
		cube([40, 50, 1.5]);
		translate([2.5,2.5,0]) {
			cylinder(r=1.5, h=2);
			translate([35,0,0]) cylinder(r=1.5, h=2);
		}
	}
}

%pcb();

mount_peg_dist = 37;
mount_hole_r = 2;
mount_margin_xy = 2;
mount_thickness = 1;
difference() {
	translate([mount_margin_xy+mount_hole_r, mount_margin_xy+mount_hole_r, 0])
	hull() {
		cylinder(r=mount_margin_xy+mount_hole_r);
		translate([mount_peg_dist, 0, 0]) cylinder(r=mount_margin_xy+mount_hole_r);
	}

	/*
	 * Wheat mounting posts
	 * 
	 * These are the posts on the corner with the DC input. The posts are 37mm
	 * apart, and the holes are 4mm.
	 */
	translate([4,4,0]) {
		cylinder(r=2);
		translate ([mount_peg_dist,0,0]) cylinder(r=2);
	}
}
