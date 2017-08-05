#pragma once

#define meters(pixels) ((pixels) * (0.02f))
#define pixels(meters) ((meters) * (50.f))
#define rad(deg) (b2_pi * (deg) / 180.0f)
#define degrees(rad) ((rad) * (180.0f / b2_pi))