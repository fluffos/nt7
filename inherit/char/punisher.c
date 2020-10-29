// punisher.c

#include <ansi.h>

inherit NPC;
int is_punisher() { return 1; }

void setup()
{
        addn_temp("apply/attack", 300);
        addn_temp("apply/defense", 300);
        addn_temp("apply/damage", 500);
        addn_temp("apply/unarmed_damage", 500);
        addn_temp("apply/armor", 2000);
        ::setup();
        set_heart_beat(1);
}

void init()
{
        add_action("do_halt", "halt");
}

int do_halt()
{
        object me;

        if (this_player() == query_temp("punish_ob"))
        {
                write(name() + "喝道：“逆徒！休走！”\n");
                return 1;
        }

        return 0;
}

void receive_damage(string type, int amount, object who)
{
        ::receive_damage(type, 1 + amount / 100, who);
}

void receive_wound(string type, int amount, object who)
{
        ::receive_wound(type, 1 + amount / 100, who);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 200000000000000 + random(200000000000000), me);
        set("neili", query("max_neili",me), me);
        return HIR "$N" HIR "一招突出，竟然是$n"
               HIR "闻所未闻，见所未见的招式，一惊之下，已然受创！\n" NOR;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        if (ob != query_temp("punish_ob") &&
            ! is_fighting(ob))
        {
                message_vision("$N对$n冷笑道：“我在这里清理门户，你插手做甚？”\n",
                               this_object(), ob);
                if (! ob->is_busy())
                        ob->start_busy(2);
        }

        ::fight_ob(ob);
        if (! is_killing(query("id", ob)))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N不理$n。\n", this_object(), ob);
        return 0;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        command("say 嘿！且慢！");
        return 1;
}

void start_punish(object ob, string fam)
{
        set_temp("punish_ob", ob);
        set_temp("punishing_fam", fam);
        move(environment(ob));
        message_vision("$N走了过来，看到$n，冷笑一声。\n", this_object(), ob);
        if (! this_object()->chat_punish())
        {
                // no chat for punish, use default
                command("chat " + ob->name(1) + "你背叛师门，今天我就替" + fam +
                        "清理你这个门户败类，留下武功，走你的路！");
        }
        command("follow " + query("id", ob));

        if (query("no_fight", environment(ob)))
        {
                tell_object(ob, "你看到" + name() + "，不由大吃一惊，慌忙转身逃走。\n");
                message("vision", ob->name() + "看到" + name() +
                        "，脸色大变，慌里慌张的转身逃走。\n" +
                        name() + "冷笑一声，喝道：“那里走？”，紧随其后追了上去。\n",
                        environment(ob), ({ ob }));
                ob->move("/d/city/guangchang");
                move("/d/city/guangchang");
                tell_object(ob, HIR "...这...这是哪里？好熟悉啊？"
                            "你心底一横，转过身来，喝道：“不是鱼"
                            "死，就是网破，来吧！”。\n" NOR);
                message("vision", ob->name() + "慌慌张张的跑了过来，只见有一人"
                        "紧随其后而来。\n", environment(ob), ({ ob }));
        }

        command("yun powerup");
        kill_ob(ob);
        ob->unconcious(this_object()); 
}

void punish_ob(object ob)
{
        string fam;

        remove_enemy(ob);
        if (living(ob))
                ob->unconcious();

        message_vision("$N伸手粘在$n的后背，脸上煞气一抹而过，喃喃"
                       "自语道：“你走吧！武功留下了！”\n",
                       this_object(), ob);

        fam = query_temp("punishing_fam");
        addn("detach/times", 1, ob);
        addn("detach/"+fam, 1, ob);
        if (addn("betrayer/times", -(int)query("betrayer/" + fam, ob), ob) < 1)
                delete("betrayer", ob);
        else
                delete("betrayer/"+fam, ob);

        ob->skill_expell_penalty();

        if (is_fighting())
        {
                // Am I in fighting now ?
                message_vision("$N冷冷道：“今天我走了，你们"
                               "几个我改日再收拾！”\n",
                               this_object());
        }
        message_vision("$N撇下$n，扬长而去。\n", this_object(), ob);

        CHANNEL_D->do_channel(this_object(), "rumor", "听说" +
                            ob->name(1) + HIM "因为背叛师门，被" +
                            name() + HIM "废去一身武功。");
        destruct(this_object());
        return;
}

int attack()
{
        object ob;

        if (objectp(ob = query_temp("punish_ob")) &&
            ! living(ob) &&
            environment(ob) == environment())
        {
                punish_ob(ob);
                return 1;
        } else
                return ::attack();
}

void unconcious()
{
        die();
}

void die()
{
        command("chat 天哪！我" + name() + "难道...难道是不中用了？");
        ::die();
}

void scan()
{
        object ob;

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        if (! objectp(ob = query_temp("punish_ob")) ||
            environment(ob) != environment() ||
            query("no_fight", environment(ob)))
        {
                message_vision("$N收住招式，悻悻道：“哼”，随即转身离去。\n",
                               this_object());
                destruct(this_object());
                return;
        }

        if (! living(ob))
        {
                punish_ob(ob);
                return;
        }

        if (! is_fighting(ob))
                fight_ob(ob);

        ::scan();
}

