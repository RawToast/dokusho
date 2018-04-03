open Jest;

describe("Auth", () =>
  ExpectJs.(
    Auth.(
      describe("Auth.regex", () => {
        let idToken = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ik5VSkZRMEpCUkRsR09EWXlNMEl6TnpoQlJFSkRRVFExUWtSQlFqVTJOelEyTmpBek5UbEdOZyJ9.eyJpc3MiOiJodHRwczovL2Rva3VzaG8uZXUuYXV0aDAuY29tLyIsInN1YiI6ImF1dGgwfDVhYmZhY2ZjODBhMTBhMzMwZDc0NzA3YiIsImF1ZCI6Im1hbDEzclExS1lKU3BBalRCdnM3MmlvYTh4aG5xOHdoIiwiaWF0IjoxNTIyNjE3ODcwLCJleHAiOjE1MjI2NTM4NzAsImF0X2hhc2giOiJTN2NyZTBIT3BGWkVaT1B1MnFNTnlRIiwibm9uY2UiOiJPOThudERmNklIblA4Rmc5VFl3YnhSUGZnYkZ3UjlVUSJ9.LX0epkkF51NGxh6e4teTcor_GCGy-4GwUT9Ov3gWC8In9zPFoknJJ_V9KUAHdm8SMp8DJQ4DJFdum-h9w2QjYfsvcA6mHzkEWBZrltTKaHN9jNFAxeqDB4hmvt2R3qqiJqzT3_cOVp2todyVnkmKR5KQNt-MfaU3niU1uZ4gK7OuvnVlr4dRBXBmQZkGxa0DMRqcI0hSmKzNzMKvOEazjWn7xvcf-fpxvYUXk27xnI62WpP_JZVedKYmoJycwgsDsxMRKrAY9JBSPhj-H1rERKN_D16OIEHQhdWZ_wSJRGbSte7CMlgsU7Zxc_t2G9OPcXmmI27CLVKVkakgqG3HVQ";
        let accessToken = "BKzbH5QlKMvCKOIo7g254bydKuCDBX9e";

        let url: ReasonReact.Router.url = {
          path: ["callback"],
          hash:
            "access_token="
            ++ accessToken
            ++ "&expires_in=7200&token_type=Bearer&state=AHLX8g.M9jl6uf7F46Oysm2A7rqHUu5U&id_token="
            ++ idToken,
          search: "abc"
        };

        test("can parses an access token from a url", () => {
          let result = Auth.resolveRegex(Auth.matchAccessToken, url.hash);
          expect(result) |> toBe(accessToken);
        });

        test("can parses an Id token from a url", () => {
          let result = Auth.resolveRegex(Auth.matchIdToken, url.hash);
          expect(result) |> toBe(idToken);
        });

        test("can parses the token expiry from a url", () => {
          let expiresIn = Auth.resolveRegex(Auth.matchExpiresIn, url.hash);
          expect(expiresIn) |> toBe("7200");
        });
      })
    )
  )
);