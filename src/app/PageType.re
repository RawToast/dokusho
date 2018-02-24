open Store;

module PageType{

    type content = { name: string, pageType: Store.pageType};

    let pageScore = (pt: Store.pageType) => { 
        switch pt {
        | Manga => 0.2
        | News => 1.0
        | Book => 1.0
        | Lyric => 0.8
        | Net => 1.0
        };
    };

    let toString = (pt: Store.pageType) => {
        switch pt {
            | Manga => "Manga"
            | News => "News"
            | Book => "Book"
            | Lyric => "Lyric"
            | Net => "Net"
            };
    };

    let findOptType: string => option(Store.pageType) = (str) => {
        switch str {
            | "Manga" => Some(Manga)
            | "News" => Some(News)
            | "Book" => Some(Book)
            | "Lyric" => Some(Lyric)
            | "Net" => Some(Net)
            | _ => None
            };
        };
        

    let pageTypes = [
            {name: "Book", pageType: Book}, 
            {name: "News", pageType: News}, 
            {name: "Manga", pageType: Manga}, 
            {name: "Net", pageType: Net}, 
            {name: "Lyric", pageType: Lyric}];
    
  }
  