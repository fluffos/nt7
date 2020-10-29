inherit DEMONROOM;

#include <ansi.h>

void setup()
{

        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("binghuo", 1);           // 表示在冰火岛
        set("no_die", 1);
        set("outdoors", "battle4");

        ::setup();
}

void init ()
{
        if (! userp(this_player()))return;
        
        if (! wizardp(this_player()))
        {
                this_player()->start_busy(1+ random(2));
                tell_object(this_player(), NOR + WHT "你来到这里，突然间迷失了方向。\n" NOR);
        }
        
        // 非帮战期间，清理所有非天下第一帮的成员
        if( !BUNCH_D->is_battle_start() && !BUNCH_D->is_top_bunch(this_player()) )
        {
                this_player()->move(__DIR__"haitan");
        }
        // 帮战期间，上届天下第一帮成员不能进入
        if( (BUNCH_D->is_battle_start() || BUNCH_D->is_battle_open()) && BUNCH_D->query_bunch_topten(1) == query("bunch/bunch_name", this_player()) )
        {
                this_player()->move(__DIR__"haitan");
        }
        if( (BUNCH_D->is_battle_start() || BUNCH_D->is_battle_open()) && !query_temp("in_pkd", this_player()) ) 

        {
                this_player()->move(__DIR__"haitan");
        }
}
