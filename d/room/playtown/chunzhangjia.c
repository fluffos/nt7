// Room: /d/playtown/chunzhangjia.c 村长家
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "村长家");
        set("long",
"你走进来便觉得这里与其他村里人的居所有所不同，明显在门面上气\n"
"派了许多，两张暗红色的桐木长椅将一张茶几夹在中间，上面挂着一副大\n"
"大的财神画像，一副对联(duilian)由于时间悠久，早已看不太清晰，但\n"
"那横幅仍然十分显眼，赫然写道“财源滚滚”。\n"
);

//      set("no_clean_up", 0);
        set("item_desc",([
                "duilian"        :        "上面已经看不太清楚了，只模模糊糊地认得清几个字。\n",
        ]));
        
        set("exits", ([
                "east"  : __DIR__"road1",
                "west"  : "/d/room/xiaoyuan",
        ]));
        setup();
        replace_program(ROOM);
}