//qianyuan.c

#include <room.h>;
inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "唐门前院");
        set("long",
"来了前院，一股花香扑鼻而来，你不由的深深的吸了一口气，好香啊\n"
"！四周都是一些花，有知名的，有不认识的，但有一朵花是最突出的，你\n"
"不禁想上去摘下来。旁边有一个小木牌(sign)。\n"
);
        set("exits", ([
                "out"   : __DIR__"tmdamen",
                "north" : __DIR__"shuige1",
        ]));
        set("item_desc", ([
                "sign" : (HIG"路边的野花不要采，家里花儿也不要摘\n"NOR),
        ]));        
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_zhai","zhai");
}

int do_zhai(string arg)
{
        object me;
      
        me = this_player();
      
        tell_object(me,HIR"你死了！\n"NOR);    
      
        return 1;
}      