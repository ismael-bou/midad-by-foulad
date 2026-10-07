#include "FouladAppSettingsLoadPlan.h"

FouladAppSettingsLoadPlan planFouladAppSettingsLoad(const bool ownFileExists, const bool ownFileLoadedOk,
                                                  const bool legacyFileExists) {
  if (ownFileExists) {
    // Migrating from legacy settings.json is only ever correct the very
    // first time. A corrupt own file later must NOT fall back to legacy --
    // that would let a torn write on foulad_apps.json silently resurrect
    // stale pre-migration values instead of surfacing the failure.
    return ownFileLoadedOk ? FouladAppSettingsLoadPlan::UseOwnFile : FouladAppSettingsLoadPlan::ReportCorrupt;
  }
  return legacyFileExists ? FouladAppSettingsLoadPlan::Migrate : FouladAppSettingsLoadPlan::FreshDefaults;
}
