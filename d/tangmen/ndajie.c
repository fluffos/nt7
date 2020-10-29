// Room: /tangmen/ndajie1.c

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long",
"这就是唐家镇的南大街了，向东西两头延伸。西边就是回春堂的分店\n"
"了，平常卖一些个跌打药。唐门自己是不卖药，因为祖上传下来的。只可\n"
"自己人用。东边人去的就少一些了，大多是匆匆而来，急急忙忙而去。是\n"
"什么地方呢，自己一进去就知道了。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([ 
                "west"  : __DIR__"hcfdian",
                "north" : __DIR__"zhongxin",
                "east"  : __DIR__"tmbingqi",
        ]));

        setup();
        replace_program(ROOM);
}
