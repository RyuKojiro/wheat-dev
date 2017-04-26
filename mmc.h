
#define MMCIF_BASE 0xffe60000

#define MMCIF_CMDR0   (*(volatile uint8_t  *)(MMCIF_BASE + 0x00)) /* Command Register 0 */
#define MMCIF_CMDR1   (*(volatile uint8_t  *)(MMCIF_BASE + 0x01)) /* Command Register 1 */
#define MMCIF_CMDR2   (*(volatile uint8_t  *)(MMCIF_BASE + 0x02)) /* Command Register 2 */
#define MMCIF_CMDR3   (*(volatile uint8_t  *)(MMCIF_BASE + 0x03)) /* Command Register 3 */
#define MMCIF_CMDR4   (*(volatile uint8_t  *)(MMCIF_BASE + 0x04)) /* Command Register 4 */
#define MMCIF_CMDR5   (*(volatile uint8_t  *)(MMCIF_BASE + 0x05)) /* Command Register 5 */
#define MMCIF_CMDSTRT (*(volatile uint8_t  *)(MMCIF_BASE + 0x06)) /* Command Start Register */
#define MMCIF_OPCR    (*(volatile uint8_t  *)(MMCIF_BASE + 0x0a)) /* Operation Control Register */
#define MMCIF_CSTR    (*(volatile uint8_t  *)(MMCIF_BASE + 0x0b)) /* Card Status Register */
#define MMCIF_INTCR0  (*(volatile uint8_t  *)(MMCIF_BASE + 0x0c)) /* Interrupt Control Register 0 */
#define MMCIF_INTCR1  (*(volatile uint8_t  *)(MMCIF_BASE + 0x0d)) /* Interrupt Control Register 1 */
#define MMCIF_INTSTR0 (*(volatile uint8_t  *)(MMCIF_BASE + 0x0e)) /* Interrupt Status Register 0 */
#define MMCIF_INTSTR1 (*(volatile uint8_t  *)(MMCIF_BASE + 0x0f)) /* Interrupt Status Register 1 */
#define MMCIF_CLKON   (*(volatile uint8_t  *)(MMCIF_BASE + 0x10)) /* Transfer Clock Control Register */
#define MMCIF_CTOCR   (*(volatile uint8_t  *)(MMCIF_BASE + 0x11)) /* Command Timeout Control Register */
#define MMCIF_TBCR    (*(volatile uint8_t  *)(MMCIF_BASE + 0x14)) /* Transfer Byte Number Count Register */
#define MMCIF_MODER   (*(volatile uint8_t  *)(MMCIF_BASE + 0x16)) /* Mode Register */
#define MMCIF_CMDTYR  (*(volatile uint8_t  *)(MMCIF_BASE + 0x18)) /* Command Type Register */
#define MMCIF_RSPTYR  (*(volatile uint8_t  *)(MMCIF_BASE + 0x19)) /* Response Type Register */
#define MMCIF_TBNCR   (*(volatile uint16_t *)(MMCIF_BASE + 0x1a)) /* Transfer Block Number Counter */
#define MMCIF_RSPR0   (*(volatile uint8_t  *)(MMCIF_BASE + 0x20)) /* Response Register 0 */
#define MMCIF_RSPR1   (*(volatile uint8_t  *)(MMCIF_BASE + 0x21)) /* Response Register 1 */
#define MMCIF_RSPR2   (*(volatile uint8_t  *)(MMCIF_BASE + 0x22)) /* Response Register 2 */
#define MMCIF_RSPR3   (*(volatile uint8_t  *)(MMCIF_BASE + 0x23)) /* Response Register 3 */
#define MMCIF_RSPR4   (*(volatile uint8_t  *)(MMCIF_BASE + 0x24)) /* Response Register 4 */
#define MMCIF_RSPR5   (*(volatile uint8_t  *)(MMCIF_BASE + 0x25)) /* Response Register 5 */
#define MMCIF_RSPR6   (*(volatile uint8_t  *)(MMCIF_BASE + 0x26)) /* Response Register 6 */
#define MMCIF_RSPR7   (*(volatile uint8_t  *)(MMCIF_BASE + 0x27)) /* Response Register 7 */
#define MMCIF_RSPR8   (*(volatile uint8_t  *)(MMCIF_BASE + 0x28)) /* Response Register 8 */
#define MMCIF_RSPR9   (*(volatile uint8_t  *)(MMCIF_BASE + 0x29)) /* Response Register 9 */
#define MMCIF_RSPR10  (*(volatile uint8_t  *)(MMCIF_BASE + 0x2a)) /* Response Register 10 */
#define MMCIF_RSPR11  (*(volatile uint8_t  *)(MMCIF_BASE + 0x2b)) /* Response Register 11 */
#define MMCIF_RSPR12  (*(volatile uint8_t  *)(MMCIF_BASE + 0x2c)) /* Response Register 12 */
#define MMCIF_RSPR13  (*(volatile uint8_t  *)(MMCIF_BASE + 0x2d)) /* Response Register 13 */
#define MMCIF_RSPR14  (*(volatile uint8_t  *)(MMCIF_BASE + 0x2e)) /* Response Register 14 */
#define MMCIF_RSPR15  (*(volatile uint8_t  *)(MMCIF_BASE + 0x2f)) /* Response Register 15 */
#define MMCIF_RSPR16  (*(volatile uint8_t  *)(MMCIF_BASE + 0x30)) /* Response Register 16 */
#define MMCIF_RSPRD   (*(volatile uint8_t  *)(MMCIF_BASE + 0x31)) /* CRC Status Register */
#define MMCIF_DTOUTR  (*(volatile uint16_t *)(MMCIF_BASE + 0x32)) /* Data Timeout Register */
#define MMCIF_DR      (*(volatile uint16_t *)(MMCIF_BASE + 0x40)) /* Data Register */
#define MMCIF_FIFOCLR (*(volatile uint8_t  *)(MMCIF_BASE + 0x42)) /* FIFO Pointer Clear Register */
#define MMCIF_DMACR   (*(volatile uint8_t  *)(MMCIF_BASE + 0x44)) /* DMA Control Register */
#define MMCIF_INTCR2  (*(volatile uint8_t  *)(MMCIF_BASE + 0x46)) /* Interrupt Control Register 2 */
#define MMCIF_INTSTR2 (*(volatile uint8_t  *)(MMCIF_BASE + 0x48)) /* Interrupt Status Register 2 */
