type pageType = Manga | News | Book | Lyric | Net;

type content = { name: string, pageType: pageType};

type entry = {
    id: int,
    kind: pageType,
    value: int
};

type readingData = {
  entries: list(entry)
};

type day = {
  date: string,
  entries: list(entry)
};

type otherReadingData = {
    days: day
};

type mainState = {
  readingData: readingData,

  selectedEntry: pageType
};

type action = 
  | AddEntry(pageType, int)
  | ChangeSelection(pageType);