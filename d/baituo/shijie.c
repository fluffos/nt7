inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
你走在青石板铺成的石阶上。这里就是传说中神秘的白驼山。远
远望去，两座白沙堆积形成的山峰好像一只骆驼的脊背。一座山门立
在你的眼前。
LONG );
        set("exits", ([
                "east"      : __DIR__"caoping",
                "northup"   : __DIR__"damen",
                "southdown" : __DIR__"guangchang" ,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 19990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}