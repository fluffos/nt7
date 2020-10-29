#include <ansi.h>
#include <room.h>

inherit PRIVATE_ROOM;

void create()
{
              set("short", "化乐天石阶"); 
              set ("long", 
          "这是一条通往神秘的化乐天大殿的石阶，往上望去石阶两边的披甲\n"
      "傀儡散发着威武肃杀之气。阶上有个将军手执一个银铃("CYN"summon"NOR")端正在\n" 
      "那里站着。\n"
        ); 

        setup();

        set("exits", ([
                "north"  : __DIR__"dadian",
                "down"  : "/d/city/kedian4",
        ]));

                set("no_steal", 1); 
                set("no_beg", 1); 
                set("no_get", 1); 
                set("no_kill", 1); 
                set("no_fight", 1); 
                set("no_magic", 1); 
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_sleep_room", 1);

/*
        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("room_owner", "红莲老祖");
        set("room_name", "莲池");
        set("room_id", "redl");
        set("room_owner_id", "redl");
        set("room_position", "溪岸小路");
*/
}

void init()
{
        add_action("do_here", "summon");
        if (userp(this_player())) this_player()->command("maphere");
}

int do_here(string arg)
{
        object me = this_player(), ob;
        
                if ( query("id", me) != "redl" && query("couple/couple_id", me) != "redl" ) {
                         tell_object(me, "你没权利在这里召唤。\n");       
                         return 1;
                }
        if (!arg || arg=="") {
                tell_object(me, "你想要召唤谁?\n");
                return 1;
        }
        ob = find_player(arg);
        if (!objectp(ob) || !playerp(ob)) {
                tell_object(me, "你没有发现有这玩家。\n");
                return 1;
        }
//         if (environment(ob)==this_object()) {
//              tell_object(me, "这个玩家正站在你面前呢。\n");
//              return 1;
//         }
                ob->move(this_object());
                set_temp("can_enterredlroom", 1, ob);
                message_vision(YEL "傀儡将军摇晃银铃，一股神念传进$n脑海里：请到化乐天大殿喝茶。\n"
                                                   "  大片紫青色烟雾聚拢弥散过后，$n迷迷糊糊地出现在$N脚下的台阶面前。\n" NOR, me, ob);
        return 1;       
}

int is_myobj(object me)
{
        if (!sscanf(base_name(me), "/u/redl/%*s") &&
                !sscanf(base_name(me), "/u/gigi/%*s") &&
                !sscanf(base_name(me), "/data/room/redl/%*s") &&
                !sscanf(base_name(me), "/data/room/gigi/%*s")) return 0;
        return 1;
}

int valid_leave(object me, string dir)
{
                object *inv;
        
        if (dir == "north" && !query_temp("can_enterredlroom", me) && query("id", me) != "redl" && query("couple/couple_id", me) != "redl" && !is_myobj(me))
                return notify_fail("傀儡将军瞪了你一眼道：未经召唤不能上去。\n");//有钥匙也没用
                
        if (dir == "north" && !is_myobj(me)) {        
                        inv = deep_inventory(me);
                        if( sizeof(inv) > 0 ) {
                foreach( object ob2 in inv ) {
                        if( interactive(ob2) || userp(ob2) ) {
                                tell_object(me, NOR"傀儡将军瞪了你一眼道：你背上背的是什么？\n"NOR);
                                return -1;
                        }
                }
                }
        }
        
        if (dir!="north" && !playerp(me)) {
                return notify_fail("傀儡将军瞪了你一眼道：非玩家不得乱走。\n");//保护特殊NPC不得下凡捣乱
        }

        return ::valid_leave(me, dir);
}

