// This program is a part of NITAN MudLIB 
// redl 2013/5
// 非战时用品，不用冷却

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"芳"HIY"华"HIW"木" NOR, ({"mu"}));
                set("nj", 30);//60 nt，2nt解毒full一次
                set("longx",  
HIK 
"(                          芳华兽的传说\n"
"    芳华兽皆为雄兽，性安，独居，身形与凡人无异，尤善植奇花异草珍药，\n"
"濯然而名，花同华，故名芳华兽。\n"
"    芳华兽，少言，神色多寂寥。肤白如凝脂，终年异香，眉眼下有朱砂痣。\n"
"泪痣颜色愈浅愈年少，直至殷红、暗红、墨黑，芳华兽亡之。\n"
"    兽亡后自浴火海，化为一截枯木，曰芳华木。此木乃芳华兽之精魄，可解\n"
"万世之毒。如将木埋入土中，将药草、花瓣碾碎加之晨曦露滴哺之，一月后枯\n"
"木红而似火，质地如玉；再二月，颜色褪淡，木上长出四肢；再三月，木出五\n"
"官，似成年人，既而木质变柔，白而无瑕；又四月，木根断，芳华兽出世。若\n"
"兽成形之十月期，以挚爱之血为引每日濯之，乃续魂，幼兽尚能保留前世记忆。\n"
"出世后的幼兽不通人语，食花蜜、花瓣及少量药草为食，但成长极其快，不出\n"
"半岁身形便与人类小孩无异，此时便言语流畅，极其聪慧，此后十天便如人类\n"
"小孩一年，直至成年。\n"
"    芳华兽乃至情之物，若成年兽不堕红尘，心如明镜，可长命乃至修仙，动\n"
"情者便如荒草，岁岁枯荣，浴入火海，反复轮回。若被情伤，十日将如凡人一\n"
"年，直至堕入轮回化为枯木，情伤愈重，木质色泽愈黑，化毒药性愈强。\n"
"    芳华绝色，世间难寻，此兽乃至情至性之物，终其一生为情所困，终逃不\n"
"脱情殇之劫，成正果者少之又少。)\n"
NOR);
                //set("base_unit", "根");
                //set("base_value", 150000000);
                //set("base_weight", 800);
                set("value", 1);
                set("weight", 800000);
                set("unit", "根");
                //set("no_store", 1); 
                set("no_steal", 1); 
                set("no_beg", 1); 
                set("set_data", 1);  
                set("auto_load", 1);  
        setup();
}

string long()
{
        return HIG "这是一根芳华兽的遗骨所化的神木 - 耐久度："+ HIC + query("nj") + HIG + 
                        "\n闻之(smell mu)  可解万毒除虚弱医目盲原地复活，\n食之(eat mu)    可以直接到最美好的十八岁年龄(必须完整耐久度)。\n" NOR + query("longx");
}

void init()
{
        add_action("do_smell", "smell");
        add_action("do_eat", "eat");
}

int do_smell(string arg)
{
    mapping my;
        object me = this_player();
        
        if (! arg || arg != "mu") {
                tell_object(me, "你要闻什么东西？\n");
                return 1;
        }
        if (me->is_busy()) {
                tell_object(me, "你先忙完手里的事再说吧！\n");
                return 1;
        }
     if (query_temp("durg_time/mu", me) > time()) {
         tell_object(me, "你这么频繁地闻以为是吸毒啊？\n"); 
         return 1;
     }

/*
        if (me->is_fighting()) {
                tell_object(me, "你正在打架没空去闻木头！\n");
                return 1;
        }
*/
        
        me->start_busy(1);
        delete_temp("block_msg/all", me);
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
        my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
        my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
        my["neili"]  = my["max_neili"];
        me->clear_condition();
        me->clear_weak();
              if( query_temp("block_msg/all", me) ) { 
                              tell_object(me, HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR); 
                              delete_temp("block_msg/all", me); 
              } 
        //me->full_self();
     set_temp("durg_time/mu", time() + 60, me);

        message_vision(YEL + "$N取出一截"+ query("name") + YEL +"放在鼻端嗅了嗅，旋即精神大振。\n" + NOR, me); 
        addn("nj", -1);
        if (query("nj") < 1) {
                message_vision(NOR + "$N手里的"+ query("name") + NOR +"微颤，化作恢恢消散了。\n" + NOR, me); 
                destruct(this_object());
        }
        return 1;
}


int do_eat(string arg)
{
        object me = this_player();
        
        if (! arg || arg != "mu") {
                //tell_object(me, "你要吃什么东西？\n");
                return 0;
        }
        if (me->is_busy()) {
                tell_object(me, "你先忙完手里的事再说吧！\n");
                return 1;
        }
        if (me->is_fighting()) {
                tell_object(me, "你正在打架没空去吃木头！\n");
                return 1;
        }
        if (query("nj") != 30) {
                tell_object(me, "你手里这根木头不完整了！\n");
                return 1;
        }
        
        me->start_busy(1);
        set("age", 18, me);
        set("mud_age", (18 - 11) * 518400, me);
        message_vision(YEL + "$N拿出一截"+ query("name") + YEL +"捏碎成黑粉，仰头吞了下去。\n" + NOR +
                                                 "$N的全身骨骼咔咔作响，皮肤也不断扭曲，片刻之后身形一顿定了下来，显得好年轻啊~~~\n" + NOR, me); 
        message_vision(NOR + "$N手里的"+ query("name") + NOR +"微颤，化作恢恢消散了。\n" + NOR, me); 
        destruct(this_object());
        return 1;
}


