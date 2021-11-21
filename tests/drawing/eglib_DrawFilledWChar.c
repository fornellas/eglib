coordinate_t x, y;

x = 50 - 14;
y = 50;

eglib_SetIndexColor(&eglib, 0, 0, 0, 128);
eglib_DrawLine(&eglib, 0, y, 100, y);
eglib_DrawLine(&eglib, x, 0, x, 100);

eglib_SetFont(&eglib, &font_Liberation_SansRegular_20px);
eglib_SetIndexColor(&eglib, 0, 255, 255, 255);
eglib_SetIndexColor(&eglib, 1, 64, 64, 64);
eglib_DrawFilledWChar(&eglib, x, y, '!');