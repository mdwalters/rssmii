<?php
require getcwd() . '/vendor/autoload.php'; // Composer

header("Last-Modified: " . gmdate('D, d M Y H:i:s') . " GMT");
header("Content-Type: text/plain; charset=ISO-8859-1");

$feed = new SimplePie();
$feed->set_feed_url(str_replace("]]", "", str_replace("![CDATA[", "", $_REQUEST["feedurl"])));
$feed->init();
$feed->handle_content_type();

$wc24mimebounary = "BoundaryForDL" . date("YmdHi") . "/" . rand(1000000, 9999999);

echo "--".$wc24mimebounary."\r\n";
echo "Content-Type: text/plain\r\n\r\n";
echo "This part is ignored.\r\n\r\n\r\n";

echo $wc24mimebounary . "\r\n".
"Content-Type: text/plain\r\n\r\n".
"Date: " . gmdate('D, d M Y H:i:s') . " +0000 (UTC)\r\n".
"From: w9999999900000000@wii.com\r\n".
"To: allusers@wii.com\r\n".
"Subject: \r\n".
"MIME-Version: 1.0\r\n".
"Content-Type: text/plain; charset=ISO-8859-1\r\n".
"Content-Transfer-Encoding: 7bit\r\n".
"X-Wii-AltName: AFIAUwBTAE0AaQBpACAAVQBwAGQAYQB0AGU=\r\n".
"X-Wii-MB-NoReply: 1\r\n\r\n";

$feed_num = 0;
$link_num = 0;

foreach($feed->get_items() as $item)
{
	$feed_num++;
	echo $item->get_title() . "\r\n\r\n".
	$item->get_description() . " ".
	"[" . (string) $feed_num . "]" . "\r\n\r\n";
}

foreach($feed->get_items() as $item)
{
	$link_num++;
	echo "[" . (string) $link_num . "]".
	" " . $item->get_link() . "\r\n";
}
?>
