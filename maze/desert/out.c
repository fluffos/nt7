inherit ROOM; 

void create() 
{ 
        set("short", "大漠出口"); 
        set("long", @LONG 
一望无际的大漠，烈日、风沙、苦寒、酷热，无时不在折磨着每
一个人，在这里，如果你没有饮水，很有可能就会被晒死，沙子滚烫，
足以把脚烫烂，一到晚上，却又冰冷得透骨。

LONG
); 
                        
        set("outdoors", "desert"); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "north":__DIR__"maze/exit",
                "out": "/d/luoyang/wenmiao",
        ])); 
                        
        setup();
        // replace_program(ROOM); 
} 

/*
int valid_leave(object me, string dir)
{
        object *inv, obj;
        int ret;

        if (dir == "out")
        {
                //FUBEN_D->query_maze_mainobj(me)->refresh_maze();
                if( ret=query_temp("fuben_event", me) )
                {
                        SCHEDULE_D->delete_event(ret);
                        FUBEN_D->clear_fuben("desert",query("id", me));
                }
        }
        return 1;
}
*/
