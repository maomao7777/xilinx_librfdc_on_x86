#include "xrfdc.h"

u32 XRFdc_ReadReg(XRFdc *InstancePtr, u32 BaseAddress. int RegOffset)
{
    int fd = open("/dev/mmrfdc", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open /dev/mmrfdc");
        return -1;
    }
    struct {
        uint32_t offset; // Offset from the base address
        uint32_t value;  // Value to write or placeholder for read
        uint8_t size;    // Access size: 16 or 32 bits
        uint8_t op_type; // 0 for read, 1 for write
        uint8_t cell;
    } write_data;
    write_data.offset = BaseAddress+RegOffset;
    write_data.size = 32;
    write_data.op_type = 0;
    write_data.cell =0;
    if (write(fd, &write_data, sizeof(write_data)) < 0) {
        perror("Write failed");
    }
    close(fd);
    return write_data.value;
}
void XRFdc_WriteReg(XRFdc *InstancePtr, u32 BaseAddress, int RegOffset, u32 RegisterValue)
{
    int fd = open("/dev/mmrfdc", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open /dev/mmrfdc");
        return -1;
    }
    struct {
        uint32_t offset; // Offset from the base address
        uint32_t value;  // Value to write or placeholder for read
        uint8_t size;    // Access size: 16 or 32 bits
        uint8_t op_type; // 0 for read, 1 for write
        uint8_t cell;
    } write_data;
    write_data.offset = BaseAddress+RegOffset;
    write_data.size = 32;
    write_data.op_type = 1;
    write_data.cell  = 0;
    write_data.value = RegisterValue;
    if (write(fd, &write_data, sizeof(write_data)) < 0) {
        perror("Write failed");
    }
    close(fd);
    return;
}
u16 XRFdc_ReadReg16(XRFdc *InstancePtr, u32 BaseAddress. int RegOffset)
{
    int fd = open("/dev/mmrfdc", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open /dev/mmrfdc");
        return -1;
    }
    struct {
        uint32_t offset; // Offset from the base address
        uint32_t value;  // Value to write or placeholder for read
        uint8_t size;    // Access size: 16 or 32 bits
        uint8_t op_type; // 0 for read, 1 for write
        uint8_t cell;
    } write_data;
    write_data.offset = BaseAddress+RegOffset;
    write_data.size = 16;
    write_data.op_type = 0;
    write_data.cell =0;
    if (write(fd, &write_data, sizeof(write_data)) < 0) {
        perror("Write failed");
    }
    close(fd);
    return (u16)write_data.value;
}
void XRFdc_WriteReg16(XRFdc *InstancePtr, u32 BaseAddress, int RegOffset, u16 RegisterValue)
{
    int fd = open("/dev/mmrfdc", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open /dev/mmrfdc");
        return -1;
    }
    struct {
        uint32_t offset; // Offset from the base address
        uint32_t value;  // Value to write or placeholder for read
        uint8_t size;    // Access size: 16 or 32 bits
        uint8_t op_type; // 0 for read, 1 for write
        uint8_t cell;
    } write_data;
    write_data.offset = BaseAddress+RegOffset;
    write_data.size = 16;
    write_data.op_type = 1;
    write_data.cell  = 0;
    write_data.value = RegisterValue;
    if (write(fd, &write_data, sizeof(write_data)) < 0) {
        perror("Write failed");
    }
    close(fd);
    return;
}