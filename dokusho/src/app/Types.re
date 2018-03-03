type pageType = Manga | News | Book | Lyric | Net;

type content = { name: string, pageType: pageType};

type entry = {
    id: int,
    kind: pageType,
    value: int
};

type day = {
  date: string,
  entries: list(entry)
};

type readingHistory = {
  days: list(day)
};

type mainState = {
  readingData: readingHistory,

  selectedEntry: pageType
};

type action = 
  | AddEntry(pageType, int)
  | ChangeSelection(pageType);