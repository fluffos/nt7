inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "海滩");
        set("long",
"这里是冰火岛西岸海滩，海浪拍打着海边巨石。周围是一望无\n"
"际的大海，东边传来阵阵巨大的声响，地动山摇一般，似乎岛上的\n"
"火山在不断地喷发，释放出巨大的能量。\n"
);
        set("exits", ([ 
                "east"    : __DIR__"shadi",
        ]));
        
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("binghuo", 1);           // 表示在冰火岛    
        set("outdoors", "battle4");
        
        set("objects", ([
                __DIR__"npc/shouwei" : 1,
                __DIR__"npc/xiexiao-ci" : 1,
        ]));
        
        set("no_fight", 1);
        
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder, horse, person;
        object *inv;
        int i;

        if (dir == "east")
        {
                // 非天下第一帮，且不在帮战期间不得进入冰火岛
                if( !BUNCH_D->is_battle_start() && !BUNCH_D->is_top_bunch(me) )
                {
                        if (! objectp(guarder = present("binghuo shouhushen", this_object())))
                        {
                                message_vision(HIM "一阵光芒闪过，冰火守护神的幻想竟出现在$N" HIM "眼前，令$N无法前进。\n" NOR, me);
                                return 0;
                        }
                        else
                        {
                                message_vision(HIM "$N" HIM "一把将$n" HIM "拦住，道：“目前冰火岛只允许天下第一帮玩家进入！\n" NOR, guarder, me);
                                return 0;
                        }
                }
                
                if( (BUNCH_D->is_battle_start() || BUNCH_D->is_battle_open()) && !query_temp("in_pkd", me) ) 
                {
                        if (! objectp(guarder = present("binghuo shouhushen", this_object())))
                        {
                                message_vision(HIM "一阵光芒闪过，冰火守护神的幻想竟出现在$N" HIM "眼前，令$N无法前进。\n" NOR, me);
                                return 0;
                        }
                        else
                        {
                                message_vision(HIM "$N" HIM "一把将$n" HIM "拦住，道：“目前冰火岛只允许报名帮战的玩家进入！\n" NOR, guarder, me);
                                return 0;
                        }
                }

                // 帮战期间，上届天下第一帮成员不能进入
                if( (BUNCH_D->is_battle_start() || BUNCH_D->is_battle_open()) && BUNCH_D->query_bunch_topten(1) == query("bunch/bunch_name", me) )
                {
                        if (! objectp(guarder = present("binghuo shouhushen", this_object())))
                        {
                                message_vision(HIM "一阵光芒闪过，冰火守护神的幻想竟出现在$N" HIM "眼前，令$N无法前进。\n" NOR, me);
                                return 0;
                        }
                        else
                        {
                                message_vision(HIM "$N" HIM "一把将$n" HIM "拦住，道：“目前冰火岛不允许上届天下第一帮进入！\n" NOR, guarder, me);
                                return 0;
                        }
                } 
                
                // 所有骑马的人必须下马
                if( objectp(horse=query_temp("is_riding", me)) )
                {
                        if( objectp(person=query_temp("is_rided_follow", horse)) )
                                delete_temp("is_riding_follow", person);
        
                        delete_temp("is_rided_follow", horse);
                        delete_temp("is_rided_by", horse);
                        delete_temp("is_riding_follow", me);
                        delete_temp("is_riding", me);
        
                        message_vision(HIR "\n$N的" + horse->name() + HIR " 似乎受到了惊吓，前蹄一扬，所有人"
                                       "被迫跳下马。\n\n" NOR, me);
        
                        return 1;
                }

                // 把背起的用户放下来
                inv = deep_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                {
                        if (! playerp(inv[i])) continue;
        
                        // 被人背起的用户
                        inv[i]->move(__FILE__);
                }                       
        }

        return ::valid_leave(me, dir);
}
