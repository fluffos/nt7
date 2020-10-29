//破立丹
//snowlf  by 2001.10.10



#include <ansi.h>

inherit ITEM;
inherit F_SAVE;
inherit F_CLEAN_UP;

int cure_ob(string);
int do_esf(string argg);
int do_egg(string argg);
int do_ewx(string argg);
int do_ebl(string argg);


int intgg;
int intsf;
int intbl;
int intnl;
int intwx;

void init();

void create()
{
        set_name(HIB "破立丹" NOR, ({"poli dan", "puoli", "dan"}));
        set("long", HIW"     一颗淡蓝色的小药丸，闪烁着晶莹的光泽，这就是传说中能够让
人脱胎换骨，洗心革面，重新做人的破立丹了。如想了解更多关于破
立丹的祥情，请看帮助(help help_pldan)"NOR"\n\n");
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "枚");
                set("value", 50000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
//    object me;
//   me = this_player();
    
    if( query("fupldan", me) == "yes" )
    {
                    write(HIR "破立丹每人最多只能服用一次，你以前服用过，不可以再次服用了！\n");
                    return 1;
    }
    else
    {  
                    write(HIW "\n\n\n\n\n\n破立丹 V 2.0A\n
                    ------------------------------------\n
                   1. 某一项先天天赋增加两点。\n
                    2. 重新分配所有的先天天赋，但是总值减少二。\n
                    3. 增加四十级的基本内功。\n
                    4. 还俗。（限非全真派的道士，非少林派的和尚，非雪山派的喇嘛）\n
                    5. 重新制定自己的神。\n
                    6. 破立丹每人最多只能服用一次，服用过则永远不可以再次服用，
                       如果你想等以后再服，请选6 \n
                    ------------------------------------\n\n
                    你想要发生哪种效果呢？（请输入对应的数字代码）\n
                    " NOR);

                    add_action("do_one", "1");
                    add_action("do_two", "2");
                    add_action("do_three", "3");
                    add_action("do_four", "4");
                    add_action("do_five", "5");
                    add_action("do_six", "6");

                 return 1;
    }
}



int do_one()
{
    object me;
    me = this_player();


    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");

    write(HIW "\n\n\n\n\n破立丹\n
    1. 膂力，增加两点先天膂力。\n
    2. 根骨，增加两点先天根骨。\n
    3. 身法，增加两点先天身法。\n
    4. 悟性，增加两点先天悟性。\n\n
    请选择\n
    " NOR);

    add_action("do_bl", "1");
    add_action("do_gg", "2");
    add_action("do_sf", "3");
    add_action("do_wx", "4");

    return 1;

}


           int do_bl()
           {
               int cbl;
               int fbl;

               object me;
               me = this_player();

               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");


               cbl=query("str", me);
               fbl = cbl + 2;

               set("str", fbl, me);
               set("jingli",query("max_jingli",  me), me);
               set("fupldan", "yes", me);
               message_vision(HIY "先天盈弱的$N服下破立丹，只觉得浑身是劲，顿时显得强壮了许多！\n" NOR, me);
        
//             me->unconcious();
               destruct(this_object());
               return 1;
           }





           int do_gg()
           {
               int cgg;
               int fgg;
               object me;
               me = this_player();


               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");

               cgg=query("con", me);
               fgg = cgg + 2;

               set("con", fgg, me);
               set("fupldan", "yes", me);
               message_vision(HIY "$N服下了一枚破立丹，身体似乎悄悄的发生了些变化。\n $N只感觉浑身胫脉之处如虫蚁咬嚼般难受，惭惭浑身疼痛，意识模糊....\n" NOR, me);
               me->unconcious();
               destruct(this_object());
               return 1;
           }



           int do_sf()
           {
               int csf;
               int fsf;

               object me;
               me = this_player();

               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");


               csf=query("dex", me);
               fsf = csf + 2;

               set("dex", fsf, me);
               set("fupldan", "yes", me);
               message_vision(HIY "$N服下了一枚破立丹，骨节啪啪作响，顿觉身轻如燕，\n$N有一很想飞起来的感觉！\n" NOR, me);
//             me->unconcious();
               destruct(this_object());
               return 1;
           }



           int do_wx()
           {
               int cwx;
               int fwx;

               object me;
               me = this_player();

               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");


               cwx=query("int", me);
               fwx = cwx + 2;

               set("int", fwx, me);
               set("fupldan", "yes", me);
               message_vision(HIY "$N服下了一枚破立丹，有点意识恍惚.... \n$N猛的打了一下激凌，脑中突然一片空明，人看上去显得灵慧了许多。\n" NOR, me);
//             me->unconcious();
               destruct(this_object());

               return 1;
           }






int do_two()
{
int cwx;
int cgg;
int cbl;
int cst;


int arg;
object me;
me = this_player();

    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");

        cwx=query("int", me);
        cgg=query("con", me);
        cbl=query("str", me);
        cst=query("dex", me);


    printf(BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(me), me->short(1));

    write("你的原来的先天天赋为："HIW" 膂力：" + cbl+" 悟性："+ cwx+" 根骨："+ cgg+" 身法："+ cst+"\n\n");
    write(HIW "\n请输入天赋 (格式： enter <臂力> <悟性> <根骨> <身法>\n");
    write(HIW "(注意：每项天赋数限在15至30之间，且四项天赋的总和应比你原来四项天赋之和少2.\n");
    write(HIW " 例子：enter 20 20 20 20\n");
    add_action("do_ebl", "enter");
    return 1;
}



               int do_ebl(string argg)
               {  
                int cwx;
                int cgg;
                int cbl;
                int cst;
                                             
                int arg;
                int cinttotal;
                int inttotal;
                object me;
                me = this_player();
                       
                cwx=query("int", me);
                cgg=query("con", me);
                cbl=query("str", me);
                cst=query("dex", me);
     
                                
                               sscanf(argg,"%d %d %d %d", intbl,intwx,intgg,intsf);
                               cinttotal = cwx + cgg + cbl + cst - 2;
                               inttotal = intbl + intgg + intwx + intsf;
                          
                        if (intbl < 15 ||intbl > 30 || intgg < 15 || intgg > 30 || intwx < 15 || intwx > 30 || intsf < 15 || intsf > 30 || inttotal > cinttotal ||inttotal < cinttotal)
                        {
                                       write(HIW "\n你输入的资料有误, 请再输入一次\n");
                                       write(HIW "注意：每项天赋数限在15至30之间，且四项天赋的总和应为 "+ cinttotal+"(即比你原来四项天赋之和少2)\n");
                                       add_action("do_ebl", "enter");
                                       return 1;

                        }

                               else
                        {

                                      set("int", intwx, me);
                                set("con", intgg, me);
                                set("str", intbl, me);
                                set("dex", intsf, me);
                                set("fupldan", "yes", me);
                                message_vision(HIY "$N服下破立仙丹，身体发生了翻天覆地的变化，\n整个人脱胎换骨，好象变成了另外一个人。\n" NOR, me);
                                me->unconcious();
                                destruct(this_object());
                                return 1;
                         }
                }



int do_three()
{
    int ccforce;
    int fforce;
    object me;
    me = this_player();


    ccforce = me->query_skill("force",1);
    fforce = ccforce + 40;

    me->set_skill("force", fforce);
    set("fupldan", "yes", me);
    message_vision(HIY "$N服下破立仙丹，打通了常人须数十年修为方能打通的{任],{督]二脉。功力大进！\n$N的基本内功徒然增进了40级！\n" NOR, me);
    me->unconcious();
    destruct(this_object());
    return 1;
}



int do_four()
{
    object me;
    me = this_player();

    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");
    
    
    
    if( query("class", me) == "taoist" || query("class", me) == "bonze" || query("class", me) == "lama" )
    {
   
                    if( query("family/family_name", me) == "全真教" )
                    {
                    
                        write(HIW "你是全真教的道士，不能使用破立还俗，还是去找掌教真人吧！\n");
                        return 1;
                    }
                    
                    else if( query("family/family_name", me) == "少林派" )
                    {
                    
                        write(HIW "阿弥陀佛！你是少林派的和尚，不能使用破立还俗！\n");
                        return 1;
                    }
                    
                    else if( query("family/family_name", me) == "雪山派" )
                     {
                            write(HIW "阿弥陀佛！你是雪山派的喇嘛，不能使用破立还俗！\n");
                        return 1;
                   }  
                    
                    else 
                    {
                        delete("class", me);
                        set("fupldan", "yes", me);
                        message_vision(HIY "$N改换装束，重新成为了凡间俗人中的一员，不用再受清规戒律的约束。\n" NOR, me);
                        me->unconcious();
                        destruct(this_object());
                        return 1;
                    }   
    }
    else
    {
                 write(HIW "这位"+RANK_D->query_respect(me)+" 未曾出家，还什么俗啊？\n 开玩笑可以，别浪费了这么珍贵的东西！\n");
                 return 1;
    }
    

}



int do_five()
{
    int cshen;
    int fshen;
    object me;
    me = this_player();

    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");

    cshen=query("shen", me);
    fshen = cshen * -1;

    set("shen", fshen, me);
    if(fshen < 0)
    {
    
                    message_vision(HIY "原本一向善良淳厚，古道热肠，侠骨铮铮的$N ，自服了破\n立丹之后，恍若恶魔附身般，变成了一个无恶不作，让人只想敬而远之的大魔头。\n" NOR, me);
    }
    else
    {
                message_vision(HIY "$N服下一枚破立仙丹，恍若受了神明点一般，大彻大悟，\n从此洗心革面，重新做人了，善哉善哉！\n" NOR, me);
  
    }
    set("fupldan", "yes", me);
    me->unconcious();
    destruct(this_object());

    return 1;
}


int do_six()
{
    object me;
    me = this_player();
    message_vision(HIY "因为考虑到破立丹每人只能服用一次，$N最终取消了现在服用破立丹的念头，打算留到最关键的时候再服。\n" NOR, me);
    return 1;
}