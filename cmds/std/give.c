// give.c
#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int do_give(object me, object obj, object who, int info);
int accept_object(object me, object who, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string target, item;
        object obj, who, *inv, obj2;
        string no_accept;
        mixed info;
        int i, amount;

        if (! arg) return notify_fail("你要给谁什么东西？\n");

        if (sscanf(arg, "%s to %s", item, target) == 2 ||
            sscanf(arg, "%s %s", target, item) == 2 );
        else return notify_fail("你要给谁什么东西？\n");

        if (! objectp(who = present(target, environment(me))))
        {
                string ext;

                if (sscanf(arg, "%s %s %s", ext, target, item) != 3 ||
                    ! objectp(who = present(ext + " " + target, environment(me))))
                        return notify_fail("这里没有这个人。\n");
        }


        if (me == who) return notify_fail("毛病！你自己给自己东西干吗？\n");
        if (in_input(who))
                return notify_fail("你还是得等人家忙完了再说吧。\n");
        if (! living(who))
                return notify_fail("你还是得等人家醒了再说吧。\n");

        if( playerp(me) && !wizardp(me) && stringp(no_accept=query("env/no_accept", who)) )
        {
                if ((no_accept == "all" || no_accept == "ALL" ||
                     is_sub(query("id", me),no_accept)) && 
                    !is_sub(query("id", me),query("env/can_accept", who)) )
                {
                        // user refuse to accept
                        return notify_fail("人家现在不想要什么东西。\n");
                }
        }

        if (sscanf(item, "%d %s", amount, item) == 2)
        {
                if (! objectp(obj = present(item, me)) && item[0] > 160)
                {
                        inv = all_inventory(me);
                        for (i = 0; i < sizeof(inv); i++)
                        if (filter_color(inv[i]->name(1)) == item)
                        {
                                obj = inv[i];
                                break;
                        }
                }

                if (!obj)
                        return notify_fail("你身上没有这样东西。\n");

                if( query_temp("is_riding", me) == obj )
                        return notify_fail("你正骑着它呢。\n");

                if (! obj->query_amount())
                        return notify_fail( obj->name() + "不能被分开给人。\n");

                if (amount < 1)
                        return notify_fail("东西的数量至少是一个。\n");

                if (amount > obj->query_amount() )
                        return notify_fail("你没有那么多的" + obj->name() + "。\n");

                else if (amount == (int)obj->query_amount())
                {
                        do_give(me,obj,who,1);
                        return 1;
                } else
                {
                        obj->set_amount((int)obj->query_amount() - amount);
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        if (do_give(me, obj2, who,1))
                        {
                                if( obj2 && !environment(obj2) ) destruct(obj2);
                                return 1;
                        }
                        else
                        if (obj2)
                        {
                                obj->set_amount((int)obj->query_amount() + amount);
                                destruct(obj2);
                                return 1;
                        }
                }
        }

        if (item == "all")
        {
                inv = all_inventory(me);
                for (amount = 0, i = 0; i < sizeof(inv); i++)
                {
                        if (! living(me)) break;
                        if (environment(me) != environment(who)) break;
                        if (objectp(inv[i]) &&
                            query_temp("is_riding", me) != inv[i] )
                                amount += do_give(me, inv[i], who, 0);
                }
                if (! amount)
                {
                        write("你什么都没有给出去。\n");
                        return 1;
                }
                message_vision("$N将一堆东西递给$n。\n",me,who);

                write("给完了。\n");
                return 1;
        }

        if (! objectp(obj = present(item, me)) && item[0] > 160)
        {
                inv = all_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                if (filter_color(inv[i]->name(1)) == item)
                {
                        obj = inv[i];
                        break;
                }
        }
        if (!obj)
                return notify_fail("你身上没有这样东西。\n");

        if( query_temp("is_riding", me) == obj )
                return notify_fail("你正骑着它呢。\n");

        do_give(me, obj, who, 1);
        return 1;
}

int do_give(object me, object obj, object who,int info)
{
        if( query("no_drop", obj) && !who->is_ultra() )
        {
                tell_object(me, "这样东西不能随便给人。\n");
                return 0;
        }

        if (living(obj))
        {
                tell_object(me, "天哪！你怎么连活人生意也做？\n");
                return 0;
        }

        if( query("dynamic_quest", obj) && playerp(who) )
        {
                tell_object(me, "这种物件岂可随意给人！\n");
                return 0;
        }

        if( playerp(who) && query("maze_item", obj) )
        {
                tell_object(me, "副本物品不能送给别人。\n");
                return 0;
        }

        if (playerp(who) &&
            sizeof(filter_array(all_inventory(who),(:!query("equipped", $1):))) >= MAX_ITEM_CARRIED && 
            ! obj->can_combine_to(who))
        {
                tell_object(me, "人家身上的东西实在是太多了，没法再拿东西了。\n");
                return 0;
        }

        switch(query("equipped", obj) )
        {
        case "worn":
                tell_object(me, obj->name() + "必须脱下来才能给别人。\n");
                return 0;

        case "wielded":
                tell_object(me, obj->name() + "必须解除装备才能给别人。\n");
                return 0;
        }

        if (info)
        if( query("id", who) != "you xun" )
        message_vision("$N拿出" + obj->short() + "给$n。\n", me, who);

        /*
        if( query("dynamic_quest", obj) )
        {
                if (TASK_D->quest_reward(me, who, obj))
                return 1;
        }
        */

        if( obj->is_task() /*&& !query("reborn/times", me)*/ )
        {
                if (TASK_D->task_reward(me, who, obj))
                return 1;
        }

        if (! playerp(who))
        {
                function f;
                int r;

                r = 0;

                // 接受物品的时候先判断是否为NPC帮派任务
                if( query("bunch_quest", me) && query("bunch_quest/type", me) == "寻找物品" )
                        r = accept_object(me, who, obj);

                if (! r)
                {
                        // 接受物品的时候先判断是否有重载的接收函数
                        f=query_temp("override/accept_object", who);
                        if (functionp(f))
                                r = (*f)(who, me, obj);
                        else
                                r = 0;
                }

                if (! r)
                        // 重载的函数不接受，也不处理(返回-1)
                        // 那么就调用accept_object进行处理
                        r = who->accept_object(me, obj);

                if (! objectp(who)) return 0;
                switch (r)
                {
                case 0:
                        if (info)
                        message_vision("$n不肯要$N的" + obj->name() + "。\n", me, who);
                        return r;
                case -1:
                        // The receiver will handle all the things
                        if (! obj || environment(obj) == who)
                                return 1;
                        return 0;
                default:
                        break;
                }
                if (! objectp(obj))
                        // The receive has destructted the object
                        return 1;
        }

        if (! playerp(who) && obj->value())
        {
                message_vision("$n接过了$N的" + obj->short() + "。\n", me, who);
                destruct(obj);
                return 1;
        }

        if (! obj->move(who))
        {
                message_vision("然而$n没能拿住$N的" + obj->name() + "。\n", me, who);
                return 0;
        }

        return 1;
}

int accept_object(object me, object who, object ob)
{
        mapping bunch_quest,b;
        object reward;

        int exp;
        int pot;
        int score;
        int weiwang;

        if (ob->is_character() || ob->is_item_make())
                // 不接受人物和自造的兵器
                return 0;

        bunch_quest=query("bunch_quest", me);

        //给错人了
        if (bunch_quest["target"] != base_name(who))
                return 0;

        //给错东西了
        if (ob->name() != bunch_quest["obj_name"])
                return 0;

        message_sort("$N接过" + ob->name() + "，翻来覆去看了看，喜不"
                     "自胜，一时间是激动万分。半晌才对$n道：“这位" +
                     RANK_D->query_respect(me) +
                     "，实在是感激不尽，这点小意思，务必笑纳！”\n", who, me);

        message_vision("$N交给$n一些白银作为报酬。\n", who, me);

        reward = new("/clone/money/silver");
        reward->set_amount(20);
        reward->move(me, 1);

        // 奖励
        addn("pk_score", -2, me);
        if (query("pk_score", me) < 0) set("pk_score", 0, me);

        exp = bunch_quest["bonus"];
        exp += random(exp);
        pot = exp/(2 + random(2));
        score = 5 + random(10);
        weiwang = 5 + random(10);

        b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在帮助" + who->name() + "寻找" + bunch_quest["obj_name"] +
                         HIG "的过程中，经过锻炼" ]);

        GIFT_D->delay_bonus(me, b);

        delete("bunch_quest", me);
        addn_temp("finish_bunch_times", 1, me);

        destruct(ob);
        return -1;
}

int help(object me)
{
        write(@HELP
指令格式 : give <物品名称> | all to <某人>
      或 : give <某人> <物品名称> | all

这个指令可以让你将某样物品给别人，当然，首先你要拥有这样物品。

HELP );
        return 1;
}
