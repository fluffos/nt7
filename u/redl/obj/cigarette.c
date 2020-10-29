// cigarette.c  by Jane  4.12.1997
// redl 2013/6
#include <ansi.h> 
inherit ITEM;

int smoking(int);

void create()
{
        string *order = ({"红河", "南京", "黄鹤楼", "利群", "苏烟"});
        set_name( (order[random(5)]), ({ "cigarette" }) );
        set_weight(80);
                set("long", "一盒香烟，可以(xiyan)。\n");
                set("unit", "盒");
                set("count",12);
                set("value", 200000000);
                set("set_data", 1);  
                set("auto_load", 1); 
                set("no_sell", "多好的烟啊，卖掉多可惜，赶紧抽掉吧..."); 
}

void init()
{
        add_action("do_smoke", "xiyan");
}

void call_pond(object me)
{
        call_other("/u/redl/obj/cigarette_c", "chk_pond", me );
        destruct(this_object());
}

int do_smoke()
{
                int stp, lh = 4 + random(3);
        object me = this_player();
        object obj = this_object();

        if( query("no_smoke", environment(me)) && (wiz_level(me) < wiz_level("(wizard)")) )
                return notify_fail("这里不准抽烟！\n");

        if( me->is_busy() ) {
                        me->command("cough");
                return 1;
        }
                
        if(query("count") == 12) 
                message_vision("$N抽出一支$n，点着了火，美滋滋地吸了起来。\n", me, this_object());
        else if (query("count") <= 1 ) {
                message_vision(YEL "$N把剩下的烟蒂摁熄在掌心里，真是内力深厚呀。\n" NOR, me, obj);
                            set("no_give", "烟蒂粘在你的手掌上了...");
                        set("no_store", "烟蒂粘在你的手掌上了...");
                        set("no_drop", "烟蒂粘在你的手掌上了...");
                        set("no_sell", "烟蒂粘在你的手掌上了...");
                        set("no_steal", "烟蒂粘在你的手掌上了...");
                        set("no_beg", "烟蒂粘在你的手掌上了...");
                call_out("call_pond", 1, me);
                me->start_busy(3);
                return 1;
        } else 
        switch(random(12)) {
                case 0: 
                case 1: 
                                message_vision(HIK "$N食指轻轻敲动$n，烟灰积落烟缸里，犹如一堆灰色的雪。\n" NOR, me, obj );
                                addn("magic_points", lh, me); 
                                write(NOR + "恭喜你吸烟有成，增加了" + chinese_number(lh) + "点灵慧！\n" + NOR);
                        break;
                case 2: 
                                if (time()-query("last_time") < 1+random(2)) {
                                        message_vision(YEL "$N狠狠的吸了一口$n，大概是吸得太快了，一张脸涨的通红。\n" NOR, me, obj);
                                        me->start_busy(25 + random(6));
                                } else {
                                        message_vision(HIK "$N轻轻一叹，手里的烟头上火星忽明忽暗，心思也晦涩难辩。\n" NOR, me );
                                        addn("magic_points", lh*3, me); 
                                        write(NOR + "恭喜你吸烟悟道，增加了" + chinese_number(lh*5) + "点灵慧！\n" + NOR);
                                }
                        break;
                default:
                                addn("stp", 1);
                                stp = query("stp");
                                switch(stp) {
                                        case 1: 
                                                message_vision(NOR "$N吐出一串烟圈，看着它们往天上一个接一个地飘散开. \n" NOR, me);
                                        break;
                                        case 2: 
                                                message_vision(NOR "$N吐出一串烟圈，看着它们往天上一个接一个地飘散开. 。\n" NOR, me);
                                        break;
                                        case 3: 
                                                message_vision(NOR "$N吐出一串烟圈，看着它们往天上一个接一个地飘散开. 。o\n" NOR, me);
                                        break;
                                        case 4: 
                                                message_vision(NOR "$N吐出一串烟圈，看着它们往天上一个接一个地飘散开. 。o O\n" NOR, me);
                                        break;
                                        default:
                                                message_vision(NOR "$N轻轻呼出一股青烟，在氤氲中静默着，好像一只呆鸟。\n" NOR, me);
                                                if (random(3)) set("stp", 0);
                                        break;
                                }
                        break;
        }
        addn("count",-1);
        set("last_time", time());
        return 1;
}



