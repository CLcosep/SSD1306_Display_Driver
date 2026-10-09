### SSD1306 Display_Driver

A from scratch SSD1306 OLED Display Driver written for the STM32F103C8T6 "Blue Pill" using ST's HAL I2C functions for communincation. Framebuffer logic, pixel drawing, and SSD1306 initialization sequence are all hand written and cross referenced against the official Solomon Systech SSD1306 datasheet and the u8g2 reference driver.

#### Features: 
- 128x64 monochrome framebuffer
- Pixel-level set/get
- Bitmap drawing from row-major, MSB-frist packed bitmap data
- Full SSD1306 initialization sequence, built from datasheet command tables
- Framebuffer-to-display flush over I2C


__Status__
- Currently text rendering is disabled 
- Will attempt to implement a GIF rendering capability (done)