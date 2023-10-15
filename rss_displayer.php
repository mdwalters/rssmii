<?php
require getcwd() . "/vendor/autoload.php"; // Composer

header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Content-Type: text/plain; charset=utf-8");

$httpModSince = !empty($_SERVER["HTTP_IF_MODIFIED_SINCE"])
    ? strtotime($_SERVER["HTTP_IF_MODIFIED_SINCE"])
    : 0;

$feed = new SimplePie();
$feed->set_feed_url(
    str_replace("]]", "", str_replace("![CDATA[", "", $_REQUEST["feedurl"]))
);
$feed->enable_cache(false);
$feed->init();
$feed->handle_content_type();

use DataDog\DogStatsd;
$statsd = new DogStatsd();

$wc24mimebounary =
    "BoundaryForDL" . date("YmdHi") . "/" . rand(1000000, 9999999);

echo "--" . $wc24mimebounary . "\r\n";
echo "Content-Type: text/plain\r\n\r\n";
echo "This part is ignored.\r\n\r\n\r\n";

$i = 0;

foreach ($feed->get_items() as $item) {
    $i += 1;

    if (strtotime($item->get_date()) - $httpModSince < 0) {
        continue;
    }

    /* Create the main body text. */

    echo "--" .
        $wc24mimebounary .
        "\r\n" .
        "Content-Type: text/plain\r\n\r\n" .
        "Date: " .
        gmdate("D, d M Y H:i:s") .
        " +0000 (UTC)\r\n" .
        "From: w9999999900000000@rc24.xyz\r\n" .
        "To: allusers@rc24.xyz\r\n" .
        "Subject: \r\n" .
        "MIME-Version: 1.0\r\n" .
        "Content-Type: multipart/mixed; boundary=\"----=Content_";
        $i .
        "\"\r\n" .
        "Content-Transfer-Encoding: 7bit\r\n" .
        "X-Wii-AltName: " .
        base64_encode(
            mb_convert_encoding($_REQUEST["title"], "UTF-16", "auto")
        ) .
        "\r\n" .
        "X-Wii-MB-NoReply: 1\r\n\r\n" .
        "------=Content_" .
        $i .
        "\r\n" .
        "Content-Type: text/plain; charset=utf-8\r\n" .
        "Content-Transfer-Encoding: 7bit\r\n\r\n" .
        ($raw_description = \Soundasleep\Html2Text::convert(
            $item->get_content(),
            ["drop_links" => true]
        ));

    $description =
        mb_convert_encoding($item->get_title(), "UTF-8", "auto") . "\r\n";
    $description .= "-- " . $item->get_link() . "\r\n\r\n";
    $description .= mb_convert_encoding($raw_description, "UTF-8", "auto");

    // Message text can't be longer than ~3000 characters
    $description =
        strlen($description) > 2900
            ? substr($description, 0, 2900) . "[...]"
            : $description;

    echo "\r\n\r\n" .
        $description .
        "\r\n\r\n" .
        "------=Content_" .
        $i .
        "\r\n" .
        "Content-Type: application/x-wii-msgboard;\r\n" .
        " name=rss.arc\r\n" .
        "Content-Transfer-Encoding: base64\r\n" .
        "Content-Disposition: attachment;\r\n" .
        " filename=rss.arc\r\n\r\n" .
        "Vao4LQAAACAAAAAqAAAAYMzMzMzMzMzMzMzMzMzMzMwBAAAAAAAAAAAAAAIAAAABAAAAYAAABygA\r\n" .
        "dGh1bWJuYWlsX0xaLmJpbgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEKAbAABVqjgtAAAAIKIAAzoA\r\n" .
        "B2DMzLABAdoAHEACAwALUA4DADMFgBAvAAAbQABpbQBnAG15X0xldAB0ZXJTX2IudCNwbFA3IK8w\r\n" .
        "AF8QRlEMAGcUIE5gAJAAc14OAHdAcF4gW4BuMHj9AW/8TVVVUFAwB5EwD1BQAA/v/e5wH/+AB1AX\r\n" .
        "8B/wH/A/8D/wX/Bf//B/8H/wn/C/8L/w3/Df8P//8P/xH/E/8T/xX/Ff8X/xf/zxn/Gf8b/x3/Hf\r\n" .
        "wf8FBZ+SFwUFAA/yL7I/8AfwF//wJ/Jn8E/wX/Bv8q/wl/Cn//C38vfw3/Dv8P/zP/En8Tf/8Ufz\r\n" .
        "h/Fv8X/xj/PP8bfxx//x1/QX9CcyL/I/8j/yP/R3//Jf8m/yf/S/8qfyt/LH9Qf/8u/y//MP9U/z\r\n" .
        "N/NH81f1l//zf/OP85/13/PH89fz5/Yn+PQP9B/0L/I/xH/87vwATVRVVVL97/wGTQBwV9UQDya/\r\n" .
        "TgL87lXVJQgAF20KAACAWGbPTgbvlSGpAhAvgFxV9fSnjwBHAMBW9L/0z/Tf9x//9Qf1F/Un92f1\r\n" .
        "T/Vf9W/3r//1l/Wn9bf39/Xf9e/1//g/8/Yn9jf2R1GnA5WBtwHnIAIlEgcCNVVf/UgOCNdcwDHP\r\n" .
        "DdVXhBInFVVlBQIXbXocqCgAEjdSPyjvT/0ETqqqqqoSH1pYM1hYYA9wF+4NGS/wFwhNVS0CIjdg\r\n" .
        "V9VE/XBH/Q4pYk9wVbEJT24ZjxJ/lSsCIn8MWFX1v/cnAsfAXM8ALxK3AGD3R/dX92cpp1WvAQ8D\r\n" .
        "CcdCARcJCc+ACoO/Vf2s/SAlABXXVv///QBVN1WrGc8Km/8QnyAHABcBIFVV1Qv9hRAHJ1UV0B/9\r\n" .
        "ISAXcAdwP1NBA2dwkBdcViAf8JceAIBA+B/4L/g/UecAygDPA+8DNVFXATO3DYIRN00lVVf/FBdW\r\n" .
        "wgs9FBcJ1Vd/I/daIaggFBdXUIAgkdcheoALB4/9DmCR74BSD2/9TgqKqKj+Ui9SJ2APBE8CLnIv\r\n" .
        "MA9a+OI/8A/wH/B/gn/9DhViAvJ/FM+lKgoiz1QfVSUCkq8cQFUXZQcE/xGpqgAi/1WVCZvPDm4D\r\n" .
        "AQkhVzUXA0cCAMJX/af9ANTUINfVEi8AAPpV/QFk/SDV1dTUMj8rvQACR6cM314STwMGEgD/WBJX\r\n" .
        "VS0SX+AoXFUSTwAFhwn9IJQQPwBAAnchBY9g/wHd/QDVNQ0BYk8BIP0CAQEDA1AnkBAPAwMAD+/9\r\n" .
        "TsAzQGCDBwW3gIMQzzPnxIP3U+dVVoAV5+5VEFVagDP3WID9LokD16qogBYXXuKDx4gSD3qAggOv\r\n" .
        "LkAQ+PPf8cfx1/HnhDdu/U6wBp9V8j/Ef4/9Lv8f/z9/FLekj/JH8ldAZ2VVBwj0t/0uDn8EoA/6\r\n" .
        "8Ofy9/T/9P9E56USlw4M+8u9CQTXdUfNCUAJAk/H/QBUVFaEIgcAAKhXAgcBQBBAQEAR/1VVV2AO\r\n" .
        "///+sg8DAAcEjzUgCQIUl1hX1Q3/F//84AeHcCAPBEcSZ2ICBDcUn9U1BQAf/QEAYFBYVP+9BK8A\r\n" .
        "1RUl/SD84QERAQEBFNcFCQESR4AQDgH9b/vLf3oq4uAh91wiF80CTmDPZe8D92oq8/fzv/PP89//\r\n" .
        "9D/0B/QX9Cf0h/R/TX/SL//yP/SH9Of09/S/9M/1L/U/+vUH9ReSL1KvUj+FBCfWiBRv/m9AH/cg\r\n" .
        "9GghgIAiBwCAwFoWrzHpARR3EjdcVlcW1wkCCaVVFr9UVyR/ASEBAwIC/zYChyJWVyAPAACqEB8A\r\n" .
        "EpUVFQbv/rEAH4AA/ab9AFdX1xeQFJ+AgAAf6f0AFR8VFVYSxwIuci/QD6NnfgH4H1AXE4cC6PQf\r\n" .
        "A7dRP1VF9i/2P/ZP9q/2d/I///R/eP/pD/bH9tf3N/dH9w/p9x/3f8THEIW3/S4EN71BV0Aj1wP2\r\n" .
        "dv8Jz6sZzwIg/CtgXFcGX/sEiQAA6lUGBwstQAsP/y77ylX/qp8CT/tpIg9QB1AX8B/wH+AwPwBX\r\n" .
        "ED/8Kwkl1YyAP/wLeATBMj/AgIWVj4AAARBFlxD6Z/8VrwDP+D/4T/iv+L/4h/iX//j39H/4//s/\r\n" .
        "8j/5T/kX+Sf/+Yf5l/lf+W/5z/nf+af5t/36F/on+e/5//pfp6cE/F//+o/6V/pn+sf61/qf+q/7\r\n" .
        "D/37H/rn+vf2v/j/1r+PCM//HH/7R/tX+7d0H/tH81/79//8B/vP+9/8P/xP/Bf8J/yH3/yXKdcE\r\n" .
        "/o9VJ/RH/I/87//8//zH/Nf9N/1H/Q/9H/1/+H9/D8+df2APgi8VBQX3Cocfzw6fD/8ADuHwR0AX\r\n" .
        "//AfbdcQN1AHHBcMFie/GH/74B/5p7A/Dj8OZwrwX/Cf//B/+8/wf/on8J88Bw+g8L/9VHdA5/Df\r\n" .
        "+ocxFw9/qvxv72AX8B/gHwLwP/F/+wfxf9jwfyCfChCfFEdUVEDAki9R/wUFVVUAAAAAAAAAAAAA\r\n" .
        "AAAAAAAAAAAAAAAAAAA=\r\n\r\n" .
        "------=Content_" .
        $i .
        "--\r\n\r\n";

    if ($httpModSince == 0) {
        break;  // Show only one entry for first request
    }
}
echo "--" . $wc24mimebounary . "--\r\n\r\n";

// $statsd->increment(rss.feeds_processed);

?>
