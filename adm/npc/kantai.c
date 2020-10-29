#include <ansi.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create() {
        set("short", "比武看台");
        set("long", @LONG
这里是比武场的看台。现在已经是人声鼎沸，群雄议论纷纷，都在猜
测谁能折桂。四周有些桌子。
LONG
    );
        set("exits", ([
                "down"  : "/d/huashan/houzhiwangyu",
        ]));
        
        set("no_fight", 1);
        set("outdoors", "huashan" ); 

        setup();
}

int valid_leave(object me, string dir) 
{
        delete_temp("flag_hslj", me);
        return ::valid_leave(me, dir);
}
