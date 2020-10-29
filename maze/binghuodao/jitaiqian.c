inherit ROOM;

#include <ansi.h>

int TEST_FLAG = 0;

public void set_test_flag(int n){TEST_FLAG = n;}

void create()
{
        set("short", HIY "祭台前" NOR);
        set("long",@LONG
这是一处宽阔的洞穴，明亮开朗。洞穴四周插满了各种旗
帜，石壁上也挂有各种祭祀的牲口，但早已化为白骨。洞穴正
中摆放着一个玉石做成的祭台（jitai）， 上面插着一面鲜红
的旗帜。
LONG);

        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_magic", 1);
        set("binghuo", 1);           // 表示在冰火岛


        set("no_clean_up", 1);
        
        set("exits", ([ 
                "out"     : __DIR__"jitan",
        ]));
        
        set("item_desc", ([ 
                "jitai"   :  HIC "这是一个废弃的祭台，似乎进行过大型祭祀，似乎可以跳上(jump jitai)祭台。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();
        
        if (! arg || arg != "jitai")
                return notify_fail("你要往哪里跳。\n");
                
        // 有隐身符或保护的不增加帮派时间
        if( query_temp("apply/shade_vision", me) )
        {
                tell_object(me, HIG "你处于隐身状态，不能上祭台！\n" NOR);
                return 1;
        }
/*
        if (me->query_condition("die_guard"))
        {
                tell_object(me, HIG "你处于被保护状态，不能上祭台！\n" NOR);
                return 1;
        }
        
        if( query("age", me) < 5 && query("reborn/times", me) )
        {
                tell_object(me, HIG "你处于被保护状态，不能上祭台！\n" NOR);
                return 1;
        }
*/

        if( !query_temp("in_pkd", me) )
        {
                tell_object(me, HIG "你没有正式报名参加帮派争夺战，不能上祭台！\n" NOR);
                return 1;
        }

        message_vision(HIC "$N纵身一跃，跳上祭台！\n" NOR, me);

        me->move(__DIR__"jitai");
        
        return 1;
}
