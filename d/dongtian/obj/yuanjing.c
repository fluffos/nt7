// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(NOR HIG "洞天元晶" NOR, ({ "dongtian yuanjing", "yuanjing"}));
        set_weight(100);
                set("value", 1000);
                set("unit", "堆");
                set("base_weight", 10);
                set("base_value", 150);
                set("base_unit", "枚");
                set("set_data", 1);  
                set("auto_load", 1);  
                set("no_steal", 1); 
                set("no_beg", 1); 
                set("no_pawn", 1); 
                set("no_sell", 1); 
                set_amount(80);
                setup();
}        

string long()
{
        return "这是一枚洞天里结出的晶石，可以使用指令(fuse xxx)熔炼成洞天令，熔炼失败照样会消失。\n  (xxx表示地域代号，目前支持emei,songshan,huangshan,huanghe,guanwai,yueyang)\n";
}

int do_open(string arg)
{
                int lh;
        object *inv;
        object ob, me = this_player();
                
                if (environment()!=me) return 0;
        if( me->is_busy() ||
                me->is_fighting()
                ) {
                write(NOR BUSY_MESSAGE NOR);
                return 1;
        }
        inv = all_inventory(me);
        if (sizeof(inv) > 200) {
                tell_object(me, NOR "你身上的物品太多了。\n" NOR);
                me->start_busy(2);
                return 1;
        }               
        if (!random(100)) me->start_busy(2);
        message_vision(NOR + CYN + "$N" + NOR + CYN + "拿出一枚晶石，用力一捏欲图熔炼它。\n" + NOR, me);
        write(NOR + "/d/dongtian/create_d.c"->convert_ling(arg, random(25), me) + NOR);
        lh = query("level", me) + 95000;
        lh = random(lh / 4) + lh * 3 / 4;
                addn("magic_points", lh, me); 
                addn("dongtian/yuanjing/num", 1, me);//log
                addn("dongtian/yuanjing/count", lh, me);
                write(NOR + HIY + "你在熔炼"+name()+NOR+HIY + "的过程中增加了" + HIW + chinese_number(lh) + HIY + "点灵慧！\n\n" + NOR);        
        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 
                        
        return 1;
}

void init()
{
        add_action("do_open","fuse"); 
}



