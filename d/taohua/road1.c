inherit ROOM;
 
void create()
{
        set("short", "小路");
        set("long", @LONG
这是一条小径，弯弯曲曲向远方延伸。小径两边种植了一些桃花树。
你只一瞥就发现：这些桃花全是白色的。
LONG );
        set("exits", ([
                "east"  : __DIR__"road2",
                "south" : __DIR__"mudi",
        ]));
        
        set("outdoors", "taohua");
 
        set("coor/x", 8970);
        set("coor/y", -2940);
        set("coor/z", 0);
        setup();
}