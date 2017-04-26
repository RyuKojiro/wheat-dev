
#define MMCIF_BASE 0xFFE60000

#define MMCIF_CMDR0	  (*(volatile uint8_t  *)(MMCIF_BASE + 0x00)) /* Command Register 0 */
#define MMCIF_CMDR1	  (*(volatile uint8_t  *)(MMCIF_BASE + 0x01)) /* Command Register 1 */
#define MMCIF_CMDR2	  (*(volatile uint8_t  *)(MMCIF_BASE + 0x02)) /* Command Register 2 */
#define MMCIF_CMDR3	  (*(volatile uint8_t  *)(MMCIF_BASE + 0x03)) /* Command Register 3 */
#define MMCIF_CMDR4	  (*(volatile uint8_t  *)(MMCIF_BASE + 0x04)) /* Command Register 4 */
#define MMCIF_CMDR5	  (*(volatile uint8_t  *)(MMCIF_BASE + 0x05)) /* Command Register 5 */
#define MMCIF_CMDSTRT (*(volatile uint8_t  *)(MMCIF_BASE + 0x06)) /* Command Start Register */
#define MMCIF_OPCR    (*(volatile uint8_t  *)(MMCIF_BASE + 0x0A)) /* Operation Control Register */
#define MMCIF_CSTR    (*(volatile uint8_t  *)(MMCIF_BASE + 0x0B)) /* Card Status Register */
#define MMCIF_INTCR0  (*(volatile uint8_t  *)(MMCIF_BASE + 0x0C)) /* Interrupt Control Register 0 */
#define MMCIF_INTCR1  (*(volatile uint8_t  *)(MMCIF_BASE + 0x0D)) /* Interrupt Control Register 1 */
#define MMCIF_INTSTR0 (*(volatile uint8_t  *)(MMCIF_BASE + 0x0E)) /* Interrupt Status Register 0 */
#define MMCIF_INTSTR1 (*(volatile uint8_t  *)(MMCIF_BASE + 0x0F)) /* Interrupt Status Register 1 */
#define MMCIF_CLKON   (*(volatile uint8_t  *)(MMCIF_BASE + 0x10)) /* Transfer Clock Control Register */
#define MMCIF_CTOCR   (*(volatile uint8_t  *)(MMCIF_BASE + 0x11)) /* Command Timeout Control Register */
#define MMCIF_TBCR    (*(volatile uint8_t  *)(MMCIF_BASE + 0x14)) /* Transfer Byte Number Count Register */
#define MMCIF_MODER   (*(volatile uint8_t  *)(MMCIF_BASE + 0x16)) /* Mode Register */
#define MMCIF_CMDTYR  (*(volatile uint8_t  *)(MMCIF_BASE + 0x18)) /* Command Type Register */
#define MMCIF_RSPTYR  (*(volatile uint8_t  *)(MMCIF_BASE + 0x19)) /* Response Type Register */
#define MMCIF_TBNCR   (*(volatile uint16_t *)(MMCIF_BASE + 0x1A)) /* Transfer Block Number Counter */
#define MMCIF_RSPR0   (*(volatile uint8_t  *)(MMCIF_BASE + 0x20)) /* Response Register 0 */
