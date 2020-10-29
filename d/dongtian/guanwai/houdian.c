// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

#define YXNUM 3500

string look_xiang(object me)
{
        object ring, ob;
        
        if (me->is_busy()) return NOR BUSY_MESSAGE NOR;
        me->start_busy(2);
                
        ring = find_object(__DIR__"ring");
        if (! ring) ring = load_object(__DIR__"ring");
        if (ring) {
                if ( objectp(ob = environment(ring)) ) {
                        return NOR + HIK "长明灯上刻着一个名字『" + HIY + query("name", ob) + NOR + HIK + "』\n" + NOR + "( 你寻思着要不要<pick>... )\n" + NOR;
                }
        }
        return NOR + HIK "长明灯上有朵美轮美奂的" + HIY + "火焰莲花" + NOR + HIK + "正跳跃燃烧着。\n" + NOR + "( 你寻思着要不要<pick>... )\n" + NOR;
}

int do_pick()
{
        object me = this_player();
        object ring, ob;
        
        if (me->is_busy()) {
                write(NOR BUSY_MESSAGE NOR);
                return 1;
        }
        me->start_busy(3 + random(2));
        
        if (query("pick_time") && query("pick_time") > time()) {
                write(NOR "长明灯上的莲花十分钟内才被人掐过。\n" NOR);
                return 1;
        }
        
    set("pick_time", time() + 600);
        ring = find_object(__DIR__"ring");
        if (! ring) ring = load_object(__DIR__"ring");
        if (ring) {
                ring->reborn();
                if ( objectp(ob = environment(ring)) && playerp(ob) ) {
                        message_vision(NOR + HIC + query("dtname", ring) + "洞天" + NOR + YEL + "传来半声清鸣，$N" + 
                                NOR + YEL + "身上的" + query("name", ring) + NOR + YEL + "滴溜溜一转，旋即化作星芒循声而去...\n" + NOR, ob);
                }
                message_vision(NOR + HIY + "火焰莲花" + NOR + CYN + "沿着$N" + NOR + CYN + "食指倏地烧上手掌，$N" + NOR + CYN + "赶忙抓住定睛一看，却是支古朴的发簪。\n" + NOR, me);
                ring->move(me);
        }
        return 1;
}

void create()
{
        set("short", __DIR__"guangchang.c"->load_name() + "后殿");
        set("long", 
"走过大殿，穿过幽静的小路，便来到后殿，与大殿的热闹比起来，这里\n"
"确实冷清之极。只见偌大的一片空地上，矗立着一座气势非凡的殿堂，四角\n"
"飞檐，琉璃瓦顶，古香古色的门牌红柱，仿佛都在这一片宁静中诉说着昔日\n"
"的历史。一阵阵青烟，从深邃而显得有些阴暗的殿内飘出，从外面看，只见\n"
"里面烛火点点，更有长明灯("CYN"deng"NOR")微微摇晃，悬挂半空。\n"
);
                //set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"dadian",
                        "north" : __DIR__"yaopu",
                ]));

        set("item_desc", ([
                "长明灯": (: look_xiang :),
                "灯": (: look_xiang :),
                "deng": (: look_xiang :),
        ]) );

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); //睡觉不雅观
        set("no_kill",1);
        //set("no_fight",1);

        set("owner_level", 2);
        set("max_carry_user" ,1);
        set("dongtianfudi", YXNUM);
        
        setup();
}

int clean_up() { return 1;}

int discmdkill() 
{ 
        tell_object(this_player(), "你不能在这里毛手毛脚。\n");  
        return -1;  
} 

void init()
{
        add_action("discmdkill", "kill"); 
        add_action("do_pick", "pick"); 
        set("max_carry_user", 1 + query("zhen_type", get_object(__DIR__"guangchang")));
        set("dongtianfudi", YXNUM + query("apply/num_yanxi", get_object(__DIR__"guangchang")));
        ::init();
}

