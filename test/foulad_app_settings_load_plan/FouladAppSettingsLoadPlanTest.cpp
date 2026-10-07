#include <gtest/gtest.h>

#include "FouladAppSettingsLoadPlan.h"

// The exact distinction FouladAppSettings::loadFromFile() must preserve: a
// missing own file is a normal, expected migration trigger, but a corrupt
// own file must never fall back to legacy settings.json -- see
// FouladAppSettingsLoadPlan.h's comment for why.

TEST(FouladAppSettingsLoadPlan, OwnFileLoadsSuccessfully) {
  EXPECT_EQ(planFouladAppSettingsLoad(/*ownFileExists=*/true, /*ownFileLoadedOk=*/true, /*legacyFileExists=*/true),
            FouladAppSettingsLoadPlan::UseOwnFile);
  EXPECT_EQ(planFouladAppSettingsLoad(/*ownFileExists=*/true, /*ownFileLoadedOk=*/true, /*legacyFileExists=*/false),
            FouladAppSettingsLoadPlan::UseOwnFile);
}

TEST(FouladAppSettingsLoadPlan, OwnFileExistsButCorruptDoesNotMigrate) {
  // The regression this test guards against: treating "own file present but
  // failed to parse" the same as "own file absent" would silently resurrect
  // stale legacy values behind a torn write, regardless of whether a legacy
  // file happens to exist.
  EXPECT_EQ(planFouladAppSettingsLoad(/*ownFileExists=*/true, /*ownFileLoadedOk=*/false, /*legacyFileExists=*/true),
            FouladAppSettingsLoadPlan::ReportCorrupt);
  EXPECT_EQ(planFouladAppSettingsLoad(/*ownFileExists=*/true, /*ownFileLoadedOk=*/false, /*legacyFileExists=*/false),
            FouladAppSettingsLoadPlan::ReportCorrupt);
}

TEST(FouladAppSettingsLoadPlan, MissingOwnFileWithLegacyMigrates) {
  EXPECT_EQ(planFouladAppSettingsLoad(/*ownFileExists=*/false, /*ownFileLoadedOk=*/false, /*legacyFileExists=*/true),
            FouladAppSettingsLoadPlan::Migrate);
}

TEST(FouladAppSettingsLoadPlan, MissingOwnFileNoLegacyUsesDefaults) {
  EXPECT_EQ(planFouladAppSettingsLoad(/*ownFileExists=*/false, /*ownFileLoadedOk=*/false, /*legacyFileExists=*/false),
            FouladAppSettingsLoadPlan::FreshDefaults);
}
