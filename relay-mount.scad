$fn = 60;
padding = .1;

pcb_hole_dist = 35;
pcb_hole_r = 1.5;
pcb_w = 40;
module pcb_holes() {
	translate([2.5,2.5,-padding]) {
		cylinder(r=pcb_hole_r, h=2);
		translate([pcb_hole_dist,0,0]) cylinder(r=pcb_hole_r, h=2);
	}
}

module pcb() {
	difference() {
		//color("Blue")
		cube([pcb_w, 50, 1.5]);
		pcb_holes();
	}
}

%translate([(mount_peg_dist+((mount_margin_xy+mount_hole_r)*2)-pcb_w)/2,10,mount_thickness]) pcb();

mount_peg_dist = 37;
mount_hole_r = 2;
mount_margin_xy = 2;
mount_thickness = 1;
difference() {
	translate([mount_margin_xy+mount_hole_r, mount_margin_xy+mount_hole_r, 0])
	hull() {
		// Mounting Side
		cylinder(r=mount_margin_xy+mount_hole_r);
		translate([mount_peg_dist, 0, 0]) cylinder(r=mount_margin_xy+mount_hole_r);

		// PCB side
		translate([1,10-pcb_hole_r,0]) {
			cylinder(r=mount_margin_xy+pcb_hole_r);
			translate([pcb_hole_dist, 0, 0]) cylinder(r=mount_margin_xy+pcb_hole_r);
		}
	}

	translate([(mount_peg_dist+((mount_margin_xy+mount_hole_r)*2)-pcb_w)/2,10,0]) pcb_holes();

	/*
	 * Wheat mounting posts
	 * 
	 * These are the posts on the corner with the DC input. The posts are 37mm
	 * apart, and the holes are 4mm.
	 */
	translate([4,4,-padding]) {
		cylinder(r=2, h=mount_thickness+(padding*2));
		translate ([mount_peg_dist,0,0]) cylinder(r=2, h=mount_thickness+(padding*2));
	}
}
