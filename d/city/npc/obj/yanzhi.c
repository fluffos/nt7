inherit ITEM;
#include <ansi.h>

int do_makeup();
void remove_effect(object);

void create()
{
        set_name(HIR "胭脂" NOR, ({ "yan zhi","yanzhi"}) );
        set_weight(50);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "盒");
                set("long", "这是一盒用上好玫瑰花瓣层层叠熏细滤而成的胭脂，艳如云霞，香气袭人。这是女\n孩子化妆(makeup)的必备品。\n");
                set("value", 1);
        }
}

void init()
{
        add_action("do_makeup", "makeup");
}

int do_makeup()
{
        object me;
        object huafen, you;
        string str;
        
        me = this_player();
        if( query_temp("makeuped", me) )
        {
                write("你刚刚化过妆，不用再化了，妆化太浓效果会适得其反的。\n");
                return 0;
        }
        
        str=query("gender", me);
        if( (str != "女性") && (str != "无性"))
        {
                if(str == "男性")
                {
                        write("大男人化什么妆！\n");
                        return 0;
                }
                else
                {
                        write("你不可以化妆！\n");
                        return 0;
                }
        }

        huafen = present("huafen dai",me); 
        if(!huafen) 
        {
                write("买袋花粉吧，没有花粉耶。\n");
                return 1;
        }
        you = present("baohua you",me); 
        if(!you) 
        {
                write("买樽刨花油吧，没有刨花油耶。\n");
                return 1;
        }

        message_vision("$N用小鬃刷熬上点刨花油，理了理略显凌乱的头发。\n", me);
        message_vision("$N拔下发间银簪，小心的挑出些胭脂膏子放在手心，用右手小指沾了些点在唇上，\n更显红唇饱满娇艳欲滴。\n", me);
        if((me->query_per()>25) && (str != "无性"))
                message_vision(HIM"$N将剩下的胭脂小心地用两掌晕开，轻轻拍在双颊，揽镜自照，但见面若芙蓉目似\n秋雨，不由嫣然一笑，真个是百媚千娇。\n"NOR, me);
        else if(me->query_per()<15)
                message_vision(BLU"$N将剩下的胭脂小心地用两掌晕开，轻轻拍在双颊，揽镜自照，发现自己满脸的白\n粉嗖嗖往下掉，化完妆后的样子仍是不敢恭维。\n"NOR, me);
        else
                message_vision(HIG"$N将剩下的胭脂小心地用两掌晕开，轻轻拍在双颊，揽镜自照，似乎变漂亮了点。\n"NOR, me);

        me->start_busy(5);
        addn_temp("apply/per", 1, me);
        set_temp("makeuped", 1, me);

        destruct(huafen);
        destruct(you);
        destruct(this_object());
        return 1;
}
        
void remove_effect(object me)
{
        if( query_temp("makeuped", me) )
        {
                addn_temp("apply/per", -1, me);
                delete_temp("makeuped", me);
                tell_object(me, "忙碌了一天，你的妆全乱了，该找个地方梳洗一下了。\n");
        }
}