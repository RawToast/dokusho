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

type mainState = {
  readingData: day,

  selectedEntry: pageType
};

type action = 
  | AddEntry(pageType, int)
  | ChangeSelection(pageType);