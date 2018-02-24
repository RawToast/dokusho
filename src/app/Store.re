module Store {

    type pageType = Manga | News | Book | Lyric | Net;

    type entry = {
        id: int,
        kind: pageType,
        value: int
    };

    type readingData = {
        days: list(day) /* Perhaps a map instead */
    } and
    day = {
        date: string,
        entries: list(entry)
    };
};