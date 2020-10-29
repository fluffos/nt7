// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "桥上");
        set("long", @LONG
小桥上，朱栏低垂，垂柳下，少女轻笑。小溪缓缓流过，几尾金
色鲤鱼越水而出。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "east" : __DIR__"gu1",
                "westdown" : __DIR__"gu3",
 
        ]));
        set("outdoors","wansong");       
        set("coor/x",110);
        set("coor/y",10);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}    
