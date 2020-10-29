// This program is a part of NITAN MudLIB 
// redl 2013/4/1 
#include <ansi.h>

inherit ITEM;

int halt_diging(object me)
{
        message_vision(YEL + "$N放下"+query("name")+ NOR + YEL + "擦了擦汗。\n" + NOR,  me);
        delete_temp("toucai", me);
        me->set_short_desc(0);
        me->stop_busy();
        me->start_busy(2);
        return 1;
}

int diging(object me)
{
        int stage, rnd, exp, i;
        object tool = query_temp("toucai_tool", me);

        if (!objectp(tool) || environment(tool) != me)
        {
                        tell_object(me, "咦...你的锄头呢？\n");
                delete_temp("toucai", me);
                me->set_short_desc(0);
            me->stop_busy();
            me->start_busy(6);
                return 1;
        }        

        if (query("nj", tool) < 1 ){
                        message_vision(NOR + "$N手里的"+query("name")+ NOR + "咔嚓一声散架了。\n" + NOR,  me);
                me->set_short_desc(0);
            me->stop_busy();
                me->start_busy(2);
                        destruct(this_object());
                return 1;
        }
        
        switch(stage=query_temp("toucai", me) )
        {
        case 1:
        case 2:
        case 3:
        case 4:
                if (random(10))//因为是挖宝石来地不能太快，减慢速度！
                {
                        tell_object(me, "你轻轻地刨翻着菜地。\n");
                        break;
                }

                tell_object(me, "你挖掘动作逐渐放慢了..\n");
                stage++;
                break;
        case 5:
                        tell_object(me, "你提锄头时似乎有些吃力...\n");
                stage++;
                break;
        case 6:
                        rnd = random(1000);
                        exp = 280 + random(100);
                if (rnd<6){//鲁智深出现
                        tell_object(me, CYN + "你面前突然出现一个胖大和尚暴喝道：哪里来的泼皮，敢来洒家地里偷菜！\n" + 
                                                                  "说完一个醋钵大小的拳头扑面飞至，你慌忙地举起小锄头一搁架，“咔嚓”一声\n" +
                                                                  "你的锄头快断了，鼻子也被打破了...\n" + NOR);
                        addn("nj", -100, tool);
                                        set_temp("block_msg/all",1 ,me);
                        message_vision(YEL + "一个黑影暴雷似的一声大喝，$N还没来得及反应，脸上就重重挨了一拳。\n" + NOR, me);
                        delete_temp("block_msg/all", me);
                        //me->unconcious();//给被偷抢的机会

                                delete_temp("toucai", me);
                                me->set_short_desc(0);
                                me->stop_busy();
                                me->start_busy(2);
                                return 1;
                }
                else if (rnd<33){//金元宝=百两黄金
                        for(i = random(3) + 2; i > 0; i--) {
                                message_vision(YEL + "$N一锄头下去“咔嗒”一声，似乎挖到了什么，\n$N狂喜之下刨出一块金闪闪的硬物揣到怀里。\n" + NOR, me);
                                new("/clone/money/yuanbao")->move(me);
                        }
                                if (query("combat_exp", me)>1000000) GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : exp / 4 ]));
                }
                else if (rnd<334){
                                        for(i = random(3) + 2; i > 0; i--) {
                                message_vision(YEL + "$N一锄头下去“咔嗒”一声，似乎挖到了什么，\n$N惊喜之下刨出一块不知名的宝石揣到怀里。\n" + NOR, me);
                                rnd = random(5);
                                switch(rnd)
                                {
                                        case 0:
                                                new("/clone/tessera/cdiamond")->move(me);
                                                break;
                                        case 1:
                                                new("/clone/tessera/cemerald")->move(me);
                                                break;
                                        case 2:
                                                new("/clone/tessera/csapphire")->move(me);
                                                break;
                                        case 3:
                                                new("/clone/tessera/cruby")->move(me);
                                                break;
                                        default:
                                                new("/clone/tessera/ctopaz")->move(me);
                                                break;
                                }
                        }
                        exp /= 3;
                        if (query("combat_exp", me)>1000000) GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : exp / 4 ]));
                }
                else {
                        message_vision(YEL + "$N一锄头下去“噗哧”一声，挖到一颗粘粪的烂白菜，\n$N悻悻地把烂白菜扔到一边，念叨：“锄禾日当午，偷情真幸苦”。\n" + NOR, me);
                        exp /= 6;
                        if (query("combat_exp", me)>1000000) GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : exp / 4 ]));
                }

                //stage = 1;
                //me->set_short_desc(0);
                //break;
                
                                halt_diging(me);
                                return 1;
                default:
                    me->set_short_desc(0);
                    me->stop_busy();
                        me->start_busy(2);
                                return 1;
        }
        
        set_temp("toucai", stage, me);
        return 1;
}

int move(mixed dest, int raw)
{
        object me;

        if (me = query_temp("owner"))
                me->interrupt_me();

        return ::move(dest, raw);
}


int do_dig()//string arg)
{
        object *obs;
        object where;
        object me = this_player();
        
//              if (! arg || arg != "cai"){
//                      tell_object(me, "你要挖什么？\n");
//                      return 1;
//              }
               
        if (me->is_busy() || me->is_fighting()){
                        tell_object(me, "你还是忙完手头上的事情再说吧。\n");
                        return 1;
                }
  if ( !interactive(this_player()) ) return 1;
                
//         if (query("combat_exp", me)>5000000){
//              tell_object(me, "你实战经验大于五百万了，别再做这种丢脸的事了。\n");
//                      return 1;
//              }
// 
//         if (query("combat_exp", me)<1000000){
//              tell_object(me, "你实战经验还不足一百万，放弃这想法吧。\n");
//                      return 1;
//              }

                where = environment(me);
/*
                if (!sscanf(base_name(where), "/d/kaifeng/caidi%*s")){
                        tell_object(me, "这里不是开封大相国寺的菜地吧？\n");
                        return 1;
                }
*/
                if (strsrch(query("short", where), "菜地") == -1) {
                        tell_object(me, "这里不是菜地吧？\n");
                        return 1;
                }

        obs = filter_array(all_inventory(where),
                           (: interactive($1) &&
                             $1 != $(me) &&
                             query_temp("toucai", $1) :));

        if (sizeof(obs) > 10)
        {
                 tell_object(me, "这里已经有" + sizeof(obs) + "个人在偷菜了，你等等吧。\n");
                 return 1;
        }

                
                if (query("nj") < 1) {
                        message_vision(NOR + "$N手里的"+query("name")+ NOR + "咔嚓一声散架了。\n" + NOR,  me);
                        destruct(this_object());
                        return 1;
                } else addn("nj", -1);

        message_vision(YEL + "$N鬼鬼祟祟地摸出一把小锄看了看周围，飞速地蹲下来挖挖挖..\n" + NOR, me);
        set_temp("toucai", 1, me);
        set_temp("toucai_tool", this_object(), me);
        me->start_busy((: call_other, __FILE__, "diging" :),
                       (: call_other, __FILE__, "halt_diging" :));
                me->set_short_desc("正在偷菜。");
        return 1;
}



void init()
{
        if (interactive(this_player()) &&
            environment() == this_player())
        {
                add_action("do_dig", "toucai");
                add_action("do_dig", "wacai");
        }
}

void create()
{
        set_name(HIY "金刚" BLINK HIR "琉" HIC "璃" NOR HIW "锄" NOR, ({ "jingang chu", "chu tou", "chu" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else
        {*/
                set("unit", "把");
                set("long", "这是一把能在菜地里使用的小锄头，\n上面写着“开封大相国寺.制”，指令(toucai)或者(wacai)。\n");//不和emote wa重复cmd dig重复
                set("value", 1);
                set("weight", 50000000);
                set("nj", 3000);
                set("no_store", "这样东西不能放在那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                                set("set_data", 1); 
                                set("auto_load", 1); 
        //}

        setup();
}

