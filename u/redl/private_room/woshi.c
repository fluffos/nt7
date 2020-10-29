#include <ansi.h>
#include <room.h>

inherit PRIVATE_ROOM;

void create()
{
        set("short", "卧室");
        set ("long", 
    "这里是男女主人吃小龙虾聊人生理想的地方。\n"
"    此时芝芝正坐几前，为两人斟上一杯后道：“女儿悲，进的外人\n"
"是乌龟。女儿愁，这里撺来大马猴。”说完后有意无意地往你瞥了一\n"
"眼。红莲老祖按箸，举杯一饮而尽后接道：“女儿喜，洞房花烛朝慵\n"
"起。女儿乐，一根叽吧往里戳。”接着和芝芝相视一笑，挥出一掌隔\n"
"空扇灭了烛火。\n"
"    房间的光线顿时黯淡下来，只听得一阵狂笑和娇呼声传来。\n"
BLU "    但你什么也没有看见...\n" NOR
);

        set("objects", ([
                "/adm/npc/obj/xiang" : 1,
/*
                "/clone/wizard/dan" : 2,
                "/u/redl/obj/fanghuamu" : 2,
*/
        ]));
        setup();

        set("exits", ([
                "west" : __DIR__"houyuan",
        ]));

        
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "红莲老祖");
        set("room_name", "莲池");
        set("room_id", "redl");
        set("room_owner_id", "redl");
        set("room_position", "溪岸小路");
}

void init()
{
        object me = this_player();
        if ( query("id", me) != "redl" && query("couple/couple_id", me) != "redl" )
        {
                        message_vision(YEL "一股微风吹过，把$N吹到了室外。\n" NOR, me);
                        me->move(__DIR__"houyuan");
                        return;
        }

        add_action("do_findbaby", "xunzhao");
        //add_action("do_action", "");
}

/*
int do_action(string arg)
{
        string action;
        object me;
        me = this_player();
        if (query("id", me) == "redl" || query("couple/couple_id", me) == "redl") return 0;
        action = query_verb();
        tell_room(find_object(__DIR__"woshi"), YEL + "id:<" + query("id",me) + "> action:<" + action + ">" + ((arg != "") ? " "+arg : "") + "\n" + NOR);
        tell_object(me, YEL + "id:<" + query("id",me) + "> action:<" + action + ">" + ((arg != "") ? " "+arg : "") + "\n" + NOR); 
        return 0;
}*/

int do_findbaby(string arg)
{
        object me = this_player(), baby;
        string file;

        if (! arg || (arg != "baby" && arg != "child") ||
            ! is_room_owner(me)) 
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

