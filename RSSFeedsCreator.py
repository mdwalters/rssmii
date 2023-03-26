file = open("feeds.xml", "a")

file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<rss>\n")

print("Welcome to RSS Feeds Creator! In this program you can create file feed.xml that contains info about your RSS Feeds!")
print("")

try:
    while(True):
        rss_url = input("Please type in the URL for the RSS feed: ")
        rss_name = input("Please type in the name for the RSS feed: ")
        file.write(f"    <feed name=\"{rss_name}\"><![CDATA[{rss_url}]]></feed>\n")
        print("")
except KeyboardInterrupt:
    print("\nDone!")
    file.write(f"</rss>")
    file.close()
