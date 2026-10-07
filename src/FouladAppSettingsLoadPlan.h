#pragma once

// Pure decision logic for FouladAppSettings::loadFromFile()'s migration
// choice, split out of FouladAppSettings.cpp so it's host-testable without any
// HalStorage/ArduinoJson dependency -- see test/foulad_app_settings_load_plan/.
// The actual file I/O lives in FouladAppSettings.cpp; this function only
// decides what to do given three already-known facts about its outcome.
enum class FouladAppSettingsLoadPlan {
  UseOwnFile,     // own file existed and loaded successfully
  ReportCorrupt,  // own file exists but failed to load -- must NOT migrate
  Migrate,        // own file doesn't exist, legacy settings.json does
  FreshDefaults,  // own file doesn't exist, neither does legacy -- new device
};

FouladAppSettingsLoadPlan planFouladAppSettingsLoad(bool ownFileExists, bool ownFileLoadedOk, bool legacyFileExists);
