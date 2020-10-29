// woshi.c 盘龙居卧室

#include <room.h>
#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "卧室");
        set("long", @LONG
这是主人的卧室，收拾得井井有条。南窗下是一张大床，床边有一个
柜子。推开窗户可以看到下面的花园，还可嗅到阵阵花香，非常惬意。远
处是一大片竹林。
LONG );

        set("default_long", "这是主人的卧室，收拾得井井有条。南窗下是" /* EXAMPLE */
                            "一张大床，床边有一个柜子。推开窗户可以看" /* EXAMPLE */
                            "到下面的花园，还可嗅到阵阵花香，非常惬意" /* EXAMPLE */
                            "。远处是一大片竹林。");                   /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "down" : __DIR__"jusuo",
        ]));

//**    set("objects", ([
//**            "/adm/npc/obj/xiang" : 1,
//**    ]));

//**    set("sleep_room", 1);
//**    set("loving_room", 1);
        set("no_fight", 1);
        setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    add_action("do_findbaby", "xunzhao");
}

int do_findbaby(string arg)
{
        object me = this_player(), baby;
        string file;

//**    if (! arg || (arg != "baby" && arg != "child") ||
//**        ! is_room_owner(me)) 
                return 0;

        if( !query("couple/child_id", me) )
                return notify_fail("你又还没有孩子，来这里凑什么热闹啊？\n");

        if( objectp(baby=find_living(query("couple/child_id", me)) )
        &&  environment(baby) && baby->is_baby())
                return notify_fail("你们的孩子已经跑出去玩了，好好四处找找吧！\n");

        if( query("gender", me) == "女性" )
                file=read_file("/data/baby/"+query("id", me)+".o");
        else file=read_file("/data/baby/"+query("couple/couple_id", me)+".o");

        if (stringp(file))
        {
                baby = new("/clone/user/baby");

                baby->load_baby(me);
                baby->move(environment(me));
                message_vision("你忽然看到床底下" +
                        ({"探出一颗小脑瓜", "伸出一双小脚丫", "伸出一支小手"})
                        [random(3)] + "．．．\n", me);

        } else
        {
                tell_object(me, MAG "你们的孩子不幸夭折了，请节哀吧。\n" NOR);
                delete("couple/child_id", me);
                delete("couple/child_name", me);
        }
        return 1;
}      
