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

wheat_mount_peg_dist = 37;
wheat_mount_hole_r = 2;
wheat_mount_margin_xy = 2;
wheat_mount_thickness = 1;
difference() {
	translate([wheat_mount_margin_xy+wheat_mount_hole_r, wheat_mount_margin_xy+wheat_mount_hole_r, 0])
	hull() {
		cylinder(r=wheat_mount_margin_xy+wheat_mount_hole_r);
		translate([wheat_mount_peg_dist, 0, 0]) cylinder(r=wheat_mount_margin_xy+wheat_mount_hole_r);
	}

	/*
	 * Wheat mounting posts
	 * 
	 * These are the posts on the corner with the DC input. The posts are 37mm
	 * apart, and the holes are 4mm.
	 */
	translate([4,4,0]) {
		cylinder(r=2);
		translate ([wheat_mount_peg_dist,0,0]) cylinder(r=2);
	}
}
