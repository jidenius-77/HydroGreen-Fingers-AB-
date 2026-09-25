#pragma once

inline unsigned long fakeMillis = 0;

inline unsigned long millis() {
    return fakeMillis;
}
