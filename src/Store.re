module Store {

    type pageType = Manga | News | Book | Lyric | Net;

    type entry = {
        kind: pageType,
        value: int
    };

    type simpleReadingData = {
        entries: list(entry)
    };

    type readingData = {
        days: list(day) /* Perhaps a map instead */
    } and
    day = {
        date: string,
        entries: list(entry)
    };
};