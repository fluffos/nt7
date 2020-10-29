// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "哨卡");
        set("long", @LONG
        
你走在青石大道，来到一个哨卡，你还没有靠近，有人大喊叫你停
步，你看见士兵弓上的箭，你赶紧转身向后走。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                //"north" : __DIR__"tulu2",
                "southwest" : __DIR__"sanchalu",
        ]));
       setup();
        replace_program(ROOM);
}        
