#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_attack(string arg);

void create()
{
        set("short", "城墙上");
        set("long", @LONG
这里就是「大宋」军营前城墙。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "down" :   __DIR__"syuanmen1",
        ]));

        create_door("down", "铁门", "up", DOOR_CLOSED);
        setup();
}

void init()
{
        if (interactive(this_player()))
        add_action("do_attack", ({ "throw", "touzhi", "luoshi" }));
}
 
int do_attack(string arg)
{
        object me, ob, room, env;
        string dir, who;
        string zhen, craft;
        mapping exits;

        me = this_player();
        env = environment(me);

        if (! arg) return notify_fail("你要指挥部队朝谁发起进攻？\n");

        /*
        if( query("env/auto_war", me) )
                return notify_fail("你已经设置为由系统自动指挥作战！如想自己操作，请修改设置。\n");
*/
        
        if( query_temp("warquest/attack", me) )
                return notify_fail("你的队伍正在列阵进攻，不要乱发号令了！\n");

        if( !query("craft/siegecity/luoshi", me) )
                return notify_fail("你目前还没有通晓「守城系兵法」中「落石」这种兵法！\n");
                
        if( !query_temp("warquest/train", me) )
                return notify_fail("你未带一兵一卒，指挥个什么呀？\n");

        if( query_temp("warquest/train", me) != "infantry" )
                return notify_fail("你又不是率领步兵，如何实施落石？\n");
        
        if( query_temp("warquest/group", me)<1 )
                return notify_fail("你的队伍已经损失殆尽，无法列阵冲锋了！\n");

        if (WAR_D->query_stones(me) < 1)
                return notify_fail("你的军营里已经没有任何檑木滚石，无法实施落石了！\n");
                                
        if (sscanf(arg, "%s on %s", who, dir) != 2)
                return notify_fail("指令格式错误，请用 luoshi <军队> on <方向> 指挥你的队伍！\n");

        if( !mapp(exits=query("exits", env)) || undefinedp(exits[dir]) )
                return notify_fail("无法找到目标，请用 luoshi <军队> on <方向> 指挥你的队伍！\n");

        room = get_object(exits[dir]);
        if (! room) return notify_fail("无法找到目标，请用 luoshi <军队> on <方向> 指挥你的队伍！\n");

        if( query("no_fight", room) )
                return notify_fail("那里不允许撕杀！！\n");

        if (! objectp(ob = present(who, room)))
                    return notify_fail("无法找到目标，请用 luoshi <军队> on <方向> 指挥你的队伍！\n");

        if( !query_temp("warquest", ob) || query_temp("warquest/party", ob) != "meng" )
                    return notify_fail("你军务在身，还是不要轻易招惹是非的好！\n");

        message_vision(HIY "$N将手中宝剑一挥，大喝道：步兵营准备向敌军落石！！\n" NOR, me, ob);
        
        zhen = "普通阵";
        craft = "落石";
         set_temp("warquest/attack", 1, me);
        me->start_call_out((: call_other, WAR_D, "attack_over", me :), 10);
        WAR_D->do_attack(me, ob, zhen, craft, env, dir, room);
        return 1;
}