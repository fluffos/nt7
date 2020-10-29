// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h> 
inherit __DIR__"normal.c"; 

void create()
{
        //甲(jiǎ)、乙(yǐ)、丙(bǐng)、丁(dīng)、戊(wù)、己(jǐ)、庚(gēng)、辛(xīn)、壬(rén)、癸(guǐ)。
        set("short", "壬字舱");
        set("long", @LONG
这是广成金船上庞大的船舱群，其中一处隐秘的船舱里，(out)能逃脱这里。
LONG );
        set("objects", ([ 
                "/clone/medicine/yuqingwan" : random(8)+23,
                        __DIR__"npc/liu" : (!random(90) ? 1 : 0),
        ])); 
        set("stop_run", 1);
                set("no_protect", 1);
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_fly", 1);
                set("no_sleep_room", 1); 
                set("yuan_ci_num", 15);
                
        setup();
}

int user_cant_unconcious(object me)
{
        if (!playerp(me)) {
                return 0;
        }
        me->die();
    return 1;
}

int escboat(object me)
{
        string msg;
        object usr, *usrs;
        
        if (!me || !objectp(me)) return 1;
        if (!environment(me) || environment(me)!=this_object()) return 1;
        
        tell_room(this_object(), NOR BLINK HIR "\n船底的漩涡之力吸住了这里，轰隆一声船舱爆裂...\n\n" NOR);
        usrs = filter_array(all_inventory(this_object()), (: playerp($1) :));
        
        for( int i = 0; i<sizeof(usrs); i++) {
                if (!msg) msg = NOR + HIC + query("name", usrs[i]) + NOR;
                else msg += HIG "、" + NOR + HIC + query("name", usrs[i]) + NOR;
        }
        msg = sort_msg( HIG "听说" + msg + HIG "从" HIY "广成金船" HIG "的" + query("short", this_object()) + HIG + "逃出生天。" + NOR );
        CHANNEL_D->channel_broadcast("chat", msg);
        destruct(this_object());
        return 1;
}

int do_esc()
{
        if (this_player()->is_fighting())
             {
                tell_object(this_player(), "你在战斗里没法从船舱逃脱！\n"); 
                return -1;
        }
    if (query("blv",get_object("/u/redl/teleport/ailao"))) {
                tell_object(this_player(), "金船覆没前你没法从船舱逃脱！\n"); //避免玩家排队利用dest here刷宝
                return -1;
    }    
    escboat(this_player());
    return 1;
}

void init()
{
        object npc;
        int maxc = random(5)+6;
        
        if (!playerp(this_player())) return;
        add_action("do_esc", "out"); 
        
                for(int i = 0; i < maxc; i++ ) {
                        npc = new(__DIR__"npc/ghost");
                        set("guarder_level", random(50) + 300, npc);
                        npc->do_copyskill();
                        npc->move(this_object());
                }
                
        call_out("escboat", 300, this_player());
        ::init();
}




