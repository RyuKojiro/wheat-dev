#include "mmc.h"

static void mmcif_execute(const uint8_t command[5]) {
	/* Populate Command */
	MMCIF_CMDR0 = command[0];
	MMCIF_CMDR1 = command[1];
	MMCIF_CMDR2 = command[2];
	MMCIF_CMDR3 = command[3];
	MMCIF_CMDR4 = command[4];
	/* TODO: Should we check the CRC for sanity? */

	/* Start Command */
	MMCIF_CMDSTRT = 1;
}

void mmcif_readblock(void *out, uint8_t len, uint16_t addr) {
	uint8_t cmd[5] = {0};

	/* Clear FIFO */
	MMCIF_FIFOCLR = 1;

	/* Set block size */
	MMCIF_TBCR = len;

	/* Execute CMD16 */
	cmd[0] = 16;
	mmcif_execute(cmd);

	/* Execute CMD17*/
	cmd[0] = 17;
	mmcif_execute(cmd);
}
