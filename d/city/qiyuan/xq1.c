//象棋室
// redl 2013/2

#include <ansi.h>
inherit  ROOM;

string look_string();

void  create  ()
{
    set  ("short",  "象棋室");
        set("long", @LONG
这里是下中国象棋的静室，墙上贴着“观棋不语真君子，输钱不痛大丈夫”。
在房间中央的柱子上还贴着一张下棋指南(help 或者 ?)，观棋(look ccb)。
LONG );

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         


    set("exits",  ([
//    "east"  :  __DIR__"qiyuan2",
//    "south"  :  __DIR__"qiyuan3",
    "north"  :  __DIR__"xxzl1",
//    "west" : "/d/city/kedian4",
    ]));

     set("objects",  ([
    __DIR__"cch2"  :  1,
    ]));
   setup();
}



