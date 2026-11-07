#ifndef GUARD_BERRY_POWDER_H
#define GUARD_BERRY_POWDER_H

void SetBerryPowder(u32 *powder, u32 amount);
void ApplyNewEncryptionKeyToBerryPowder(u32 encryptionKey);
bool8 GiveBerryPowder(u32 amountToAdd);
bool8 HasEnoughBerryPowder(void);
bool8 TakeBerryPowder(void);
u32 GetBerryPowder(void);
void DisplayBerryPowderVendorMenu(void);
void RemoveBerryPowderVendorMenu(void);

#endif // GUARD_BERRY_POWDER_H
