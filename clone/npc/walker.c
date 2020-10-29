 // walker.c
 // Updated By Plzw for walker quest 2004-08-17


#include <ansi.h>

//#define ONEDAY (86400 / 365)
#define ONEDAY 480


inherit NPC;

int is_walker() { return 1; }
int do_walk();
int ask_quest();

void create()
{
        set_name("拾荒者", ({ "walker" }));
        set("gender", "男性");
        set("age", 53 + random(20));
        set("long", @LONG
这是一个拾荒者，看上去老实巴交的。不过听
说他和官府有交情，最好别去招惹。
LONG);
        set("attitude", "heroism");
        set("str", 35);
        set("int", 15);
        set("con", 19);
        set("dex", 17);
        
        set_skill("gleaning", 2500);

        set("chat_chance", 30);
        set("chat_msg", ({
                (: do_walk :),
        }));

        set("inquiry", ([
                "拾荒" : (: ask_quest :),
                "help" : (: ask_quest :),
        ]));
        setup();
        if (clonep()) keep_heart_beat();

        set("check_time", time());
        carry_object("/clone/cloth/cloth")->wear();
}

int do_walk()
{
        string start_room;
        object room;
        object ob;
        mapping obmap;
        int n;

        if (! environment())
                return 0;

        if (time() - query("check_time") > 900)
        {
                if (! stringp(start_room = query("startroom")) ||
                    ! objectp(room = find_object(start_room)) ||
                    !mapp(obmap=query_temp("objects", room)) || 
                    member_array(this_object(), values(obmap)) == -1)
                {
                        message_vision(CYN "$N" CYN "叹了叹气，走了。\n"
                                       NOR, this_object());
                        destruct(this_object());
                        return 0;
                }

                set("check_time", time());
        }

        n = 0;
        foreach (ob in all_inventory(environment()))
        {
                if (ob->is_character() ||
                    ob->is_head() ||
                    query("no_get", ob) )
                        continue;
                destruct(ob);
                n++;
        }

        if (n == 1)
                message_vision(HIC "$N" HIC "一弯腰，从地上捡起一样"
                               "东西。\n" NOR, this_object());
        else
        if (n > 1)
                message_vision(HIC "$N" HIC "弯腰在地上摸摸索索找了"
                               "半天，捡起一堆东西。\n" NOR,
                               this_object());
                        
        random_move();
        return 1;
}

void unconcious()
{
        die();
}

int ask_quest()
{
        int t, count;
        object ob = this_player();
        // 阅历不够不能领取任务
        if( query("score", ob)<2000 )
        {
                command("say 你这点阅历，恐怕地图都还没有跑熟吧，别在这里给我添乱了！\n");
                return 1;
        }
        // 拾荒技能不够不能领取任务
        if (ob->query_skill("gleaning", 1) < 30)
        {
                command("say 你估计连什么是垃圾都不知道，还是和我学学再说吧！\n");
                return 1;
        }
        // 不能连续领任务
        if( query("walker_quest/finish_time", ob) )
        {
                if( time()-query("walker_quest/finsh_time", ob)<ONEDAY )
                {
                        command("say 你帮我也要注意身体，还是休息休息，改天再做吧！\n");
                        return 1;
                }
            }
        // 已经领过任务尚未完成
        if( query("walker_quest/count", ob) )
        {
                command("say 你不是答应我帮我拾荒了吗？还站在这里罗嗦什么？\n");
                return 1;
        }
        // 领取任务
        t = time();
        set("walker_quest/time", t, ob);
        // 任务个数
        count = random(9) + 1;
        set("walker_quest/count", count, ob);
        if (count > 5)
                t += 3 * ONEDAY;
        else
                t += 2 * ONEDAY;
        set("walker_quest/limit", t, ob);

        message("vision", WHT + name() + WHT "小声的对" + ob->name() +
                          WHT "吩咐着什么，" + ob->name() +
                          WHT "一边听，一边不住的点头。\n" NOR,
                          environment(ob), ({ ob }));
        message("vision", WHT + name() + WHT "在你耳边悄声说道：你就去帮我"
                                          NOR + HIY + CHINESE_D->chinese_number(count) + NOR + WHT
                                          "件垃圾来吧！\n你务必要在" NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT
                          "之前完成！\n" NOR, ob);
        ob->start_busy(1);
        return 1;
}

int accept_object(object who, object ob)
{
        int count, intime, amount, pot, score, weiwang, exp;
        object gold, silver;
        // 没有领过任务
        if( !query("walker_quest/count", who) )
        {
                command("say 你给我这个东西干吗？\n");
                return -1;
        }
        // 非任务物品
        if( !query("walker_item", ob) )
        {
                command("say 这些东西别人还有用，你怎么就给拣来了？\n");
                return -1;
        }
        count=query("walker_quest/count", who);
        set("walker_quest/count", count-1, who);
        if( query("walker_quest/limit", who)>time() )
                intime = 1;
        else
                intime = 0;
        if (intime)
                command("say 恩，做得不错，这是给你的奖励。\n");
        else
                command("say 恩，虽然晚了点，但也还不错，这是给你的奖励。\n");
        amount = random(2) + 1;
        exp = random(30) + 10;
        pot = exp / 3;
        score = random(5) + 2;
        weiwang = random(2) + 1;
        if (intime)
        {
                // 1/4的几率获得额外的奖励
                if (random(4)==0)
                        amount++;
                gold = new("/clone/money/gold");
                gold->set_amount(amount);
                gold->move(this_object());
                command("give gold to "+query("id", who));
                // 如果及时完成的话，得到的奖励加倍
                pot *= 2;
                score *= 2;
                exp *= 2;
        }
        else
        {        
                amount = amount * 50;
                silver = new("/clone/money/silver");
                silver->set_amount(amount);
                silver->move(this_object());
        }
                
                // 如果拾荒技能超过60级则奖励加倍
                if (who->query_skill("gleaning", 1) >= 60)
                {
                        pot *= 1.5;
                        score *= 2.5;
                        exp *= 2;
                }
        GIFT_D->work_bonus(who, ([ "exp" : exp, "pot" : pot, "score" : score ]));
        addn("weiwang", -weiwang, who);
        if( query("weiwang", who)<0 )
                set("weiwang", 0, who);
        // 全部完成
        if( query("walker_quest/count", who) == 0 )
        {
            set("walker_quest/finish_time", time(), who);
            command("say 好了，你也累了，去休息休息吧！\n");
        }
        else
                       message("vision", WHT + name() + WHT "在你耳边悄声说道：你还需要帮我拣"
                                          NOR+HIY+CHINESE_D->chinese_number(query("walker_quest/count", who))+NOR+WHT
                                          "件垃圾。\n" NOR, who);
        destruct(ob);
        return 1;
}

int recognize_apprentice(object me, string skill)
{

        if (skill != "gleaning")
        {
                command("say 我除了拾荒在行，其他可什么都不会啊。\n");
                return -1;
        }

        return 1;
}
