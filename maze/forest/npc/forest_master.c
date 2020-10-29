inherit NPC;
#include <ansi.h>

void give_reward_forest(object ob, int ref_exp);

mapping itemlist = ([      
        "/maze/forest/npc/obj/bear_dan":1,
        "/maze/forest/npc/obj/bear_hand":5,
        "/maze/forest/npc/obj/bear_skin":10,
        "/maze/forest/npc/obj/snake_egg":1,
        "/maze/forest/npc/obj/snake_dan":5,
        "/maze/forest/npc/obj/snake_skin":10,
        "/maze/forest/npc/obj/tiger_xxx":1,
        "/maze/forest/npc/obj/tiger_bone":5,
        "/maze/forest/npc/obj/tiger_skin":10,
        "/maze/forest/npc/obj/wolf_eye":1,
        "/maze/forest/npc/obj/wolf_meat":5,
        "/maze/forest/npc/obj/wolf_skin":10,
        "/maze/forest/npc/obj/dragon_skin":3,
        "/maze/forest/npc/rabbit":1,
        "/maze/forest/npc/toad":1,
]);

void create()
{
        set_name(HIG "丛林狩猎者" NOR, ({ "forest hunter","hunter" }) );

        set("gender", "男性");
        set("age", 30);
        set("long",
                GRN"\n    这是一个猎物收购者，给他一定数量的猎物，获取你的奖励！
                \n      十张狼皮  五块狼肉  一对狼眼
                \n      十张熊皮  五只熊掌  一只熊胆    
                \n      十张虎皮  五具虎骨  一根虎鞭
                \n      十张蛇皮  五个蛇胆  一个蛇蛋
                \n      三块龙鳞  一个龙蛋
                \n      一只流氓兔
                \n"NOR);
        set("attitude", "peaceful");
        set("str", 26000);
        set("com", 30);
        set("int", 24);
        set("dex", 30);
        set("per", 50);



        set("chat_chance", 10);
        set("chat_msg", ({
                BLU"丛林狩猎者说道：收购各种猎物。\n"NOR ,
                YEL"丛林狩猎者说道：唉，我那走丢了的孩子啊......\n"NOR ,

        }) );

        set("combat_exp", 11000000);
        set("attitude", "peaceful");

        set_skill("unarmed", 300);
        set_skill("dodge", 300);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);

        setup();

}

int accept_object(object me, object obj)
{
        string filename;
        int need_amount,amount,exp;
        filename = base_name(obj);
        
        if (undefinedp(itemlist[filename]))
        {
                command("shake");
                command("say 这是什么东西，我不需要！");
                return 0;
        }
        
        need_amount = itemlist[filename];
        if (need_amount<=0 )
                return 0;
        if (function_exists("query_amount",obj) && obj->query_amount()<need_amount )
                return 0;

        exp = 200;

        if (function_exists("query_amount",obj))
                amount = obj->query_amount();
        else 
                amount = 1;

        exp = exp/need_amount*amount;

        command("pat "+query("id", me));
        give_reward_forest(me,exp);
        destruct(obj);
        return 1;
}

void give_reward_forest(object ob, int ref_exp) 
{
        //ref_exp是参考经验，exp不影响gold，高级玩家可以到forest挣钱
        int user_exp;
        int exp,pot,mar,score,gold;
        string reward_msg;
        int gold_times;
        gold = ref_exp/100;
        user_exp=query("combat_exp", ob);
        if( user_exp < 50000000 )
                exp = ref_exp*5/4;
        else if( user_exp < 100000000 )
                exp = ref_exp;
        else if( user_exp < 200000000 )
                exp = ref_exp/2;
        else
                exp = ref_exp/20;;

        pot = exp/2;
        score = exp/500;
        mar = exp/800;
        gold_times = "/adm/daemons/actiond"->query_action("forest_reward"); 
        if( gold_times )
                gold *= gold_times;
        if (gold < 1) gold = 1;
        /*
        reward_msg =GRN"你得到了报酬：\n\t\t" +
        chinese_number(exp) + "点实战经验\n\t\t"+
        chinese_number(pot) + "点潜能\n\t\t" +
        chinese_number(mar) + "点体会\n\t\t" +
        chinese_number(score) + "点评价\n\t\t" + 
        chinese_number(gold) + "两黄金\n"NOR;
        tell_object(ob,reward_msg);

        addn("combat_exp", exp, ob);
        addn("potential", pot, ob);
        addn("experience", mar, ob);
        addn("score", score, ob);
        addn("balance", gold*10000, ob);
        */
        
        GIFT_D->fuben_bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "score" : score, "gold" : gold ]));
}
