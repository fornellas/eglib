coordinate_t x, y;

x = 50 - 14;
y = 30 + 14 / 2;

eglib_SetIndexColor(&eglib, 0, 0, 0, 128);
eglib_DrawLine(&eglib, 0, y, 100, y);
eglib_DrawLine(&eglib, 0, y * 2, 100, y * 2);
eglib_DrawLine(&eglib, x, 0, x, 100);

eglib_SetFont(&eglib, &font_Liberation_SansRegular_20px);
eglib_SetIndexColor(&eglib, 0, 255, 255, 255);

eglib_DrawGlyph(&eglib, x, y, eglib_GetGlyph(&eglib, 'A'));
eglib_DrawGlyph(&eglib, x, y * 2, NULL);