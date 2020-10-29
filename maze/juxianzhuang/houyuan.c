// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "游府后院");
        set("long",  @LONG
这里是游府的后院，几个仆役穿梭奔走，为这次的英雄宴而忙碌着。
后院一角聚坐着一帮乞丐，低声商谈着什么，旁边的江湖人士似乎对
他们颇为不屑，甚少有人上前攀谈。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"neitang",
                "west"  :  __DIR__"chaifang",
                "south" :  __DIR__"xiangfang3",
                "north" :  __DIR__"xiangfang2",
        ]));
        /*
        set("objects",([
                __DIR__"npc/gangbang" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"

int valid_leave(object me, string dir)
{
        object room, ob;

        if( dir == "west" )
        {
                if( me->query_temp("juxianzhuang_step") == 6
                ||  me->query_temp("juxianzhuang_step") == 10 )
                {
                        room = get_object(__DIR__"chaifang");
                        if( !present("xiao feng", room) )
                        {
                                ob = new(__DIR__"npc/xiaofeng");
                                ob->move(room);
                        }
                        return 1;
                }
        }

        return ::valid_leave(me, dir);
}