// suanming.c
#include <ansi.h>
inherit NPC;
string ask_where();
string ask_chance();

void create()
{
        set_name("李半仙", ({ "li banxian", "li", "banxian", "xiansheng" }) );
        set("nickname", "算命先生" );
        set("gender", "男性" );
        set("age", 92);
        set("long", "这位算命先生坐在那里，一副神秘莫测的样子。\n");
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("no_get", 1);
        set("inquiry", ([
                "name" : "在下姓李，因为算命算得准，所以大家都尊称我为李半仙。",
                "rumors" : "要想知道你今生的祸福荣辱，那就问我来算命吧。",
                "行踪": (: ask_where :),
                "where": (: ask_where :),
                "机会" : (: ask_chance :),
                "算命" : "我的价钱最公道，不多不少，只要一两黄金。"
        ]) );
        set("chat_chance", 10);
        set("chat_msg", ({
                "李半仙吆喝道：铁嘴神算，价钱公道，相资一两黄金。\n",
                "李半仙吆喝道：命运机缘，欲知详情，相资十两黄金。\n",
                (: random_move :),
                "李半仙对你说道：客倌请留步，卜个吉凶如何？\n",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

string ask_chance()
{
    object me = this_player();
    me->set_temp("ask_chance",1);
    return "机会是吧？待老夫掐指算来......恩，如此这般，看来此事颇为不易啊！"NOR;
}

string ask_where()
{
    object me;
    string name;
    mapping quest;
    me=this_player();

    if ( !mapp(quest = me->query_temp("quest")))
        return "你这人真是的，没事问别人的行踪干嘛？";

    if (!me->query_temp("suanming_paid"))
        return "什么？你说什么？我听不见呢。\n";

    if (!stringp(name = me->query_temp("quest/name")))
        return "这，你要问谁啊？\n";

    if (!stringp(name = me->query_temp("quest/place")))
        return "唉哟，这人可不知道在哪呢。\n";

    me->delete_temp("suanming_paid");
    return me->query_temp("quest/name")+CYN"是吧？听说有人看见他曾经出现在"+name+CYN"一带。"NOR;
}


int accept_object(object who, object ob)
{
        int kar, per, max_age;
        int tc , temp;

        if (!who->query_temp("ask_chance") && ob->query("money_id") && ob->value() >= 5000)
        {
                message_vision("算命先生对着$N端详了一阵。\n", who);
                who->set_temp("suanming_paid", 1);
                per = who->query("per");
                if (random(2)) per += random(10);
                  else per -= random(7);
                kar = who->query("kar");
                if (random(2)) kar += random(10);
                  else kar -= random(7);
                max_age = 67 + random(7) + who->query("con") - who->query("kar") - who->query("per")
                             + who->query("pur") + who->query("shen")/1000000;

                if (per > 25) {
                        write("算命先生景仰地说：“看" + RANK_D->query_respect(who) + "相貌堂堂，天庭饱满，地廓方圆，");
                        if (random (kar) > 25) write("真乃富贵之象也！”\n");
                        else if (random (kar) >= 20) write("一生运势平平，也算过得去了。”\n");
                        else if (random (kar) >= 15) write("可惜冲撞了小人。”\n");
                        else write("不过你霉运当头，行事可要小心了！”\n");
                }
                else if (per >= 20) {
                        write("算命先生清了清嗓子，说：“看" + RANK_D->query_respect(who) + "相貌属中上之资，");
                        if (random (kar) > 25) write("一生大富大贵，子孙多多。”\n");
                        else if (random (kar) >= 20) write("一生运势平平，也算过得去了。”\n");
                        else if (random (kar) >= 15) write("就可惜冲撞了小人。”\n");
                        else write("不过你霉运当头，行事可要小心了！”\n");
                }
                else if (per >= 15) {
                        write("算命先生有点勉强地说：“看" + RANK_D->query_respect(who) + "相貌平平，倒也还能算是中人之资，");
                        if (random (kar) > 25) write("前生一定行了善事，一生大富大贵，子孙多多。”\n");
                        else if (random (kar) >= 20) write("一生也就运势平平，只能算过得去。”\n");
                        else if (random (kar) >= 15) write("就可惜冲撞了小人。”\n");
                        else write("你最近霉运当头，行事可要小心了！”\n");
                }
                else {
                        write("算命先生很厌恶地说：“看" + RANK_D->query_respect(who) + "五官挪位，印堂发暗，");
                        if (random (kar) > 25) write("不过你前生一定行了善事，一生大富大贵，子孙多多。”\n");
                        else if (random (kar) >= 20) write("倒还有些运气，也算过得去了。”\n");
                        else if (random (kar) >= 15) write("所以你就一生坎坷，多遇小人。”\n");
                        else write("活该倒霉，当有血光之灾！”\n");
                }
                write("算命先生掐指一算，道：“" + RANK_D->query_respect(who) + "今生估计寿至" + chinese_number(max_age) + "岁。”\n");
                return 1;
        } else {
                if (who->query_temp("ask_chance") && ob->query("money_id") && ob->value() >= 100000) {
                        write("算命先生当即说道：“好说，好说，一切都好说。”\n");

                        tc = who->query("combat_exp")/1000000;
                        write("算命先生说道：“看" + RANK_D->query_respect(who) + "的命相，当前每个谜题总共可有" + chinese_number(tc) + "次机会。”\n");

                        if (!who->query("quest/jiuyin1/pass")) {
                                temp = tc - who->query("quest/jiuyin1/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，解开九阴真经上册。”\n");
                        }

                        if (!who->query("quest/jiuyin2/pass")) {
                              	tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("quest/jiuyin2/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，解开九阴真经下卷。”\n");
                        }

                        if (!who->query("jiuyin/emeipass") && (who->query("family/family_name") == "峨嵋派")) {
                                temp = tc - who->query("jiuyin/emeifail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，解开峨嵋九阴真经。”\n");
                        }
                        if (!who->query("quest/qianzhu/pass") && (who->query("gender") == "女性" )) {
                        	      tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("quest/qianzhu/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，解开千蛛万毒手。”\n");
                        }
                        
                        if (!who->query("quest/jiuyingm/pass") && (who->query("family/family_name") == "古墓派")) {
                                tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("jiuyin/jiuyingm/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，解开古墓九阴真经。”\n");
                        }

                        if (!who->query("quest/jiebai/pass")
                            && who->query("class") !="bonze"
                            && who->query("class") != "huanxi"
                            && (who->query("gender") == "男性" || who->query("gender") == "女性")
                            && (int)who->query("shen") >= 0
                            && (int)who->query("combat_exp") >= 1000000) {
                                temp = tc - who->query("quest/jiebai/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，和老顽童结拜。”\n");

                                temp = tc - who->query("quest/hubo/fail");
                                tc = who->query("combat_exp")/500000;
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，学会双手左右互搏。”\n");
                        }

                        if (who->query("quest/jiebai/pass") && !who->query("double_attack")) {
                                tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("quest/hubo/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，学会双手左右互搏。”\n");
                        }

/*                       if (!who->query("lbwb/lbwb1pass") && !who->query("lbwb/lbwb2pass")) {
                                temp = tc - who->query("lbwb/lbwb1fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，在无量玉洞学到凌波微步。”\n");

                                temp = tc - who->query("lbwb/lbwb2fail");
                                if (temp < 0) temp = 0;
                                write("算命先生说道：“" + RANK_D->query_respect(who) + "还有" + chinese_number(temp) + "次机会，从段誉处学到凌波微步。”\n");
                        }
*/
                        if (who->query("combat_exp")<1000000) {
                                tc=0;
                        }
                        else
                        {
                                tc = who->query("combat_exp")/1000000;
                        }
                        temp = who->query("user_weapon_imbued");
                        write("算命先生说道：“" + RANK_D->query_respect(who) + "有" + chinese_number(tc) + "次打造机会，已经用了" + chinese_number(temp) +"次了。”\n");

                        who->delete_temp("ask_chance");
                        return 1;
                }
        }
        return 0;
}

