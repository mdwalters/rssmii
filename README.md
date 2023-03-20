# RSSMii
RSSMii allows you to get updates from RSS feeds straight to your Wii. You will get the updates on your Wii Message Board.

It reads a `feeds.xml` file on your SD Card root to subscribe you to each feed listed. So you can update it at any time, then launch RSSMii again and it'll update your subscriptions. You can change the interval in which updates are checked inside the program on a per-feed basis.

## Installation
1. Grab the ZIP from the [releases page](https://github.com/RiiConnect24/RSSMii/releases)
2. Extract it to the root of your SD card, so that you have the path `sd://apps/rssmii/boot.dol`
3. Create a `feeds.xml` on the root of your SD card (see below)
4. Run the homebrew through the homebrew channel and follow the on-screen instructions

To remove everything, just run the RSSMii Remover. You can also check out the instructions on [wii.guide](https://wii.guide/rssmii).

### feeds.xml
You can create a feeds.xml with the [Feeds.xml Creator](https://github.com/RiiConnect24/rssmii/releases).
```xml
<?xml version="1.0" encoding="utf-8"?>
<rss>
    <feed name="RC24 Medium">https://medium.com/feed/riiconnect24</feed>
    <feed name="Nintendo UK">https://www.nintendo.co.uk/news.xml</feed>
</rss>
```

NOTE: For special characters you need to use a CDATA tag:
```xml
<feed name="Example-Feed"><![CDATA[http://example.com/rss-feed&someparam=true]]></feed>
```

## Compilation
1. Run `make` and `make install` in [this libwc24 fork](https://github.com/WiiDatabase/wmb-asm/tree/master/libwc24/libwc24)
2. Install mxml from the devkitPro Pacman repository
3. Run `make` in this repository

## TODO
- [ ] Change server URL through feeds.xml

## Credits
* Modified by [Brawl345](https://github.com/WiiDatabase/RSSMii) of WiiDatabase.de and the RiiConnect24 team
* Original written by [main()](https://github.com/Gamer125/rssmii/tree/master/rssmii)
