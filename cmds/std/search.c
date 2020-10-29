// search.c

// 在一个ROOM中寻找物品
// 由于SCORE的不同，寻找的对象和几率也不同。
// ROOM可以设置环境变量：search_objects，这样可以指定在在这
// 个房间中的某些物品的搜索几率。也可以设置no_search 指明如
// 果江湖阅历小于某一个值就不能找到（如果该值为零，那么将不
// 查阅该人的江湖阅历，这个物品将绝对不可能找到）。这两个变
// 量可以是设置房屋的正式变量也可以是临时变量，正是变量表示
// 房屋的环境，临时变量表示是房屋临时的搜寻信息。

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;

        seteuid(getuid());

        env = environment(me);

        if (me->is_busy())
                return notify_fail("等你忙完了手头的事情再找吧！\n");

        if (me->is_fighting())
                return notify_fail("一边打架一边找东西？只有你才想得出来！\n");

        if( query("no_search", env) == "all" )
                return notify_fail("这地方看来找不出什么东西...\n");

        set_temp("pending/searching", 1, me);
        me->set_short_desc("正在东张西望。");
        message("vision", me->name() + "东瞅瞅、西望望，干什么呢？\n",
                environment(me), ({ me }));
        tell_object(me, "你开始在这里摸索，看有没有什么值钱的东西。\n");
        me->start_busy(bind((:call_other, __FILE__, "searching" :), me),
                       bind((:call_other, __FILE__, "halt_searching" :), me));
        return 1;
}

mapping query_default_objects(object me)
{
        int score=query("score", me);

        if( !query("outdoors", environment(me)) )
                return ([ ]);

        if (score < 100)
                return ([
                  "/clone/money/coin"       : 100000,
                  "/clone/money/silver"     : 20000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 20000,
                  "/d/city/npc/obj/jiudai"  : 10000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 400)
                return ([
                  "/clone/money/coin"       : 10000,
                  "/clone/money/silver"     : 15000,
                  "/clone/misc/jinchuang"   : 15000,
                  "/clone/weapon/dagger"    : 8000,
                  "/d/city/npc/obj/jiudai"  : 8000,
                  "/clone/weapon/duanjian"  : 3000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 2000)
                return ([
                  "/clone/money/coin"       : 5000,
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 25000,
                  "/clone/weapon/dagger"    : 20000,
                  "/d/city/npc/obj/jiudai"  : 10000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 10000)
                return ([
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 10000,
                  "/d/city/npc/obj/jiudai"  : 5000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
                return ([
                  "/clone/weapon/changjian" : 8000,
                  "/clone/weapon/blade"     : 8000,
                  "/clone/weapon/gangzhang" : 8000,
                  "/clone/cloth/tiejia"     : 2500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
}

//object found(object me, object env)
mixed found(object me, object env)
{
        mixed  *st;
        mapping cs, ns;
        mapping os;
        object  ob, task_ob;
        mixed   sob;
        int sum;
        int i;

        os = query_default_objects(me);
        if( mapp(cs=query_temp("search_objects", env)) )
                os += cs;

        if( mapp(cs=query("search_objects", env)) )
                os += cs;

        sum=query("score", me)>>7;
        if( mapp(ns=query_temp("no_search", env)) )
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if( mapp(ns=query("no_search", env)) )
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if (sum > 30) sum = 30;
        if( query_temp("been/searched", env)>0 )
                sum-=query_temp("been/searched", env);
        if (random(sum + 100) < 93)
                return 0;

        st = keys(os);
        sum = 0;
        for (i = 0; i < sizeof(st); i++)
        {
                if (! intp(os[st[i]]))
                        os[st[i]] = 0;
                sum += os[st[i]];
        }

        if (! sum) return 0;
        sum = random(sum);
        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < os[st[i]])
                {
                        if (stringp(st[i]))
                        {
                                if (objectp(task_ob = get_object(st[i])) &&
                                    sscanf(st[i], "/task/obj/%*s"))
                                {
                                        object boss;

                                        if( !random(5) )
                                                ob = task_ob;
                                        else {
                                                FUBEN_D->enter_fuben(me, "ultra");
                                                boss = new("/maze/ultra/npc/yaowang");
                                                boss->move(get_object("/f/ultra/"+query("id", me)+"/maze/exit"));
                                                task_ob->move(boss);
                                                get_object("/f/ultra/"+query("id", me)+"/maze")->set_display_map(1);
                                                get_object("/f/ultra/"+query("id", me)+"/maze")->set_maze_boss(boss);
                                                tell_object(me, "咦，这里好象有个隐蔽的迷宫，你撕下封条进入迷宫大门。\n");
                                                delete_temp("search_objects", env); 
                                                return 1;
                                        }
                                        delete_temp("search_objects", env);
                                }
                                else
                                        ob = new(st[i]);
                        }
                        else
                        if (objectp(st[i]))
                                ob = st[i];
                        else
                        if (functionp(st[i]))
                                ob = evaluate(st[i], me, env);

                        if (! objectp(ob))
                                return 0;

                        addn_temp("been/searched", 15, env);
                        return ob;
                }
                sum -= os[st[i]];
        }

        return 0;
}

int searching(object me)
{
        object env;
        mixed ob;

        env = environment(me);
        if( me->add_temp("pending/searching",1)>6 )
        {
                tell_object(me, "找了半天，你还是一无所获，只好先放弃了。\n");
                message("vision", me->name() + "叹了口气，发了发呆。\n", env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        if( query("qi", me)<30 || 
            query("jing", me)<30 )
        {
                tell_object(me, "你实在太疲倦了，只好放弃了寻找。\n");
                message("vision", me->name() + "叹了口气，一脸倦容。\n",
                        env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        me->receive_damage("qi", 30);
        me->receive_damage("jing", 30);

        ob = found(me, env);
        if (intp(ob) && ob > 0)
        {
                me->set_short_desc(0);
                return 0;
        }
        if (objectp(ob))
        {
                if( query("base_unit", ob) )
                        ob->set_amount(random(5) + 1);
                tell_object(me,HIC"你突然发现了一"+query("unit", ob)+
                                ob->name() + HIC "！\n");
                message("visoin", me->name() + "突然弯下腰，不知道从地"
                        "上捡起了什么东西，眉开眼笑的。\n", env, ({ me }));
                if (! ob->move(me, 1))
                {
                        tell_object(me, "可惜" + ob->name() + "对你来"
                                    "说太重了，你只好先放在地上。\n");
                }
                delete_temp("pending/searching", me);
                addn("score", 1, me);
                me->set_short_desc(0);
                return 0;
        } else
        {
                message_vision(random(2) ? "$N继续东张西望的到处瞅。\n"
                                         : "$N时而弯下腰在地上拨拉什么东西。\n",
                               me);
                return 1;
        }
}

int halt_searching(object me)
{
        object env;

        env = environment(me);
        delete_temp("pending/searching", me);
        tell_object(me, "你放弃了寻找。\n");
        message("vision", me->name() + "舒展了一下腰，叹了口气。\n", env, ({ me }));
        me->set_short_desc(0);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: search

在地上寻找东西。能找到什么呢？只有天才知道，某些地方能够找到
好东西。不过大部分地方只能找到一些普通的东西。如果你找到了东
西，你的江湖阅历将会因此而增长一点。

HELP );
        return 1;
}
