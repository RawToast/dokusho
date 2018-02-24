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

    let pageTypes = [
            {name: "Book", pageType: Book}, 
            {name: "News", pageType: News}, 
            {name: "Manga", pageType: Manga}, 
            {name: "Net", pageType: Net}, 
            {name: "Lyric", pageType: Lyric}];
    
  }
  