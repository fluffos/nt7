inherit ROOM;
 
void create()
{
        set("short", "洞口");
        set("long", @LONG
这是一条后山上的一个小山洞。洞口很小，但能容一个人钻进去。里
面黑黝黝的什么也看不见。
LONG );
        set("exits", ([
                "west"   : __DIR__"road3",
                "enter"  : __DIR__"dong",
        ]));
        set("outdoors", "taohua");
 
        set("coor/x", 8990);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();
}