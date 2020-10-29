inherit ROOM;

#include <ansi.h>

int TEST_FLAG = 1;

public void set_test_flag(int n){TEST_FLAG = n;}

void create()
{
        set("short", HIR "祭坛" NOR);
        set("long",
"这里是冰火岛的中心，也是一处祭坛，这个祭坛没有名字，但\n"
"从其建造的复杂度和气势来讲，并不输于嵩山的封禅台。祭坛四周\n"
"角落燃着蓝色的火焰，正中摆放着一个巨大的香炉和祭台(jitai)。\n"
);

        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_magic", 1);
        set("binghuo", 1);           // 表示在冰火岛

        set("no_clean_up", 1);
        
        set("outdoors", "battle4");
       
        set("league_flag", "ALL_LEAGUE"); // 默认所有帮派都可以提前进入密道
        set("exits", ([ 
                "north"   : __DIR__"xuanwutai",
                "south"   : __DIR__"shenghuotai",
        ]));
        
        set("item_desc", ([ 
                "jitai"   :  HIC "祭台旁竟隐藏着一个奇怪的拉环，转动(turn)拉环（lahuan）可能会开启什么机关。\n" NOR,
                "lahuan"  :  HIM "一个半圆形的拉环，古铜色，似乎连接着什么机关。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_turn", "turn");
}

int do_turn(string arg)
{
        object me = this_player();
        object ob;
        
        if (! arg || arg != "lahuan")
                return notify_fail("你要转动什么东西！\n");
                
        if( query("exits/enter") )
                return notify_fail("密道入口已经开着了，你没事吧？。。。\n");

        // 读取帮战控制文件，判断是否密道开启了，否则不能拉动拉环
        if( !BUNCH_D->is_battle_start() && !TEST_FLAG )
                return notify_fail("你使劲转动拉环，似乎没有什么作用。\n");
                
        // 金毛狮王存在则不能开启
        if (objectp(ob = present("jinmao shiwang", this_object())))
        {
                message_vision(HIM "一阵光芒闪过，" + ob->name() + HIM "拦在$N" HIM "面前，喝道：”哼，先过了我这关再说！“\n" NOR, me);
                return 1;
        }

        write("你使劲转动拉环，只听一声闷响，祭坛微微颤动，祭坛后竟露出一条通道(enter)。\n" NOR);
        tell_room(this_object(), HIC + me->name() + HIC "使劲转动拉环，只听一声闷响，祭坛微微颤动，祭坛后竟露出一条通道(enter)。\n" NOR, ({me}));

        set("exits/enter", __DIR__"st0");
        
        remove_call_out("close_out");   
        call_out("close_out", 300);
        
        me->start_busy(2);
        
        return 1;
}

void close_out()
{
        delete("exits/enter");  
        tell_room(this_object(), HIC "一声闷响，祭坛微微颤动，似乎是密道关闭了。\n" NOR, ({}));
}


// 呼叫来自 金毛狮王死亡后 ,league代表帮派名，如果为"ALL_LEAGUE"表示任何帮派都可以进入
public set_flag(string league)
{
        set("league_flag", league);
        remove_call_out("clear_league_flag");
        call_out("clear_league_flag", 60, league);
        
        if (league != "ALL_LEAGUE")
                tell_room(this_object(), HIM "现在只有【" + league + HIM "】可以提前一分钟进入密道！\n" NOR, ({}));
}
void clear_league_flag(string league)
{
        set("league_flag", "ALL_LEAGUE");
        
        if (league != "ALL_LEAGUE")     
                tell_room(this_object(), HIG "其他帮派可以进入密道了！\n" NOR, ({}));
}

int valid_leave(object me, string dir)
{
        
        if (dir == "enter")
        {
                // 非帮战不能进入
                if( !BUNCH_D->is_battle_start() && !TEST_FLAG )
                        return notify_fail("现在不是帮战期间，不能进入密道！\n");
                
                // 金毛狮王未死亡的标志不能进入
                if (present("xie xun", this_object()))
                        return notify_fail("金毛狮王守护着祭坛密道，不能进入！\n" NOR);
                
                // 如有帮派优先标志，标志不是ALL_LEAGUE，我不是标志指示帮派，则标志存在时不能进入
                if( query("league_flag") != "ALL_LEAGUE" && query("bunch/bunch_name", me) != query("league_flag") && !TEST_FLAG )
                        return notify_fail("你现在暂时不能进入，还是稍微等等吧！\n");
        }
        
        return ::valid_leave(me, dir);
}
