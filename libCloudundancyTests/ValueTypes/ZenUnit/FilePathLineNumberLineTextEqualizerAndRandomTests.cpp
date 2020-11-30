#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FilePathLineNumberLineTextEqualizerAndRandom.h"

TESTS(FilePathLineNumberLineTextEqualizerTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
AFACT(TestableRandomFilePathLineNumberLineText_ReturnsFilePathLineNumberLineTextWithAllRandomFields)
AFACT(ZenUnitRandomFilePathLineNumberLineText_DoesNotThrowException)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(FilePathLineNumberLineText);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, filePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineNumber, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineText, ZenUnit::Random<string>());
}

TEST(TestableRandomFilePathLineNumberLineText_ReturnsFilePathLineNumberLineTextWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   const fs::path filePath = randomGeneratorMock.FilesystemPathMock.ReturnRandom();
   const size_t lineNumber = randomGeneratorMock.SizeTMock.ReturnRandom();
   const string lineText = randomGeneratorMock.StringMock.ReturnRandom();
   //
   const FilePathLineNumberLineText randomFilePathLineNumberLineText =
      ZenUnit::TestableRandomFilePathLineNumberLineText(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.FilesystemPathMock.CalledOnce());
   METALMOCK(randomGeneratorMock.SizeTMock.CalledOnce());
   METALMOCK(randomGeneratorMock.StringMock.CalledOnce());
   FilePathLineNumberLineText expectedRandomFilePathLineNumberLineText;
   expectedRandomFilePathLineNumberLineText.filePath = filePath;
   expectedRandomFilePathLineNumberLineText.lineNumber = lineNumber;
   expectedRandomFilePathLineNumberLineText.lineText = lineText;
   ARE_EQUAL(expectedRandomFilePathLineNumberLineText, randomFilePathLineNumberLineText);
}

TEST(ZenUnitRandomFilePathLineNumberLineText_DoesNotThrowException)
{
   ZenUnit::Random<FilePathLineNumberLineText>();
}

RUN_TESTS(FilePathLineNumberLineTextEqualizerTests)
