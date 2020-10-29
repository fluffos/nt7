// Room: /d/playertown/xuemeiting.c 雪梅亭
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short", "雪梅亭");
        set("long",
"这是一个非常别致的小亭子，暗红色的亭柱被几条汉白玉长凳相连，\n"
"畔在碧绿的湖水边，亭子的周围种着几棵梅树，当这里下雪的时候，红梅\n"
"正是绽放时，配上这顶红亭，格外秀气，所以这里时常有恋人再次相会，\n"
"被当地的百姓戏称为“鸳鸯亭”。\n"
);
        set("outdoors", "playertown");
        set("exits", ([
                "west"  : __DIR__"road5",
        ]));
        setup();
}
