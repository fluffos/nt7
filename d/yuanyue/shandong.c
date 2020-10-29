inherit ROOM;
#include <ansi.h>; 
void create()
{
        set("short", "洞道"); 
        set("long", @LONG
山洞极窄，须膝行而爬，若一不小心，就不免被洞中的石壁撞的
头破血流，洞中潮湿阴暗，腥臭难闻，一阵阵的恶臭扑面而来，你不
禁头晕目眩，难受异常。
LONG );
        set("indoors", "wansong");
        set("type","mountain");
        set("exits",([
                "out":__DIR__"dongkou",
                "north":__DIR__"shandong1",
        ]) ); 
        set("coor/x",-610);
        set("coor/y",290);
        set("coor/z",80);
        setup();
        
} 
int valid_leave(object me, string dir)
{
        
        if( userp(me) && !query_temp("fugui_liquan", me) && dir == "north" )
        {
        message_vision( HIC "一阵阵的恶臭扑面而来，$N不禁头晕目眩,难受异常。\n\n"NOR,me);
                // me->unconcious();
                return 0;
        } else
        {
                return 1;
        }
}  
