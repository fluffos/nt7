// muding.c 木鼎

#include <ansi.h>

inherit ITEM;

int do_clear(string arg);
int do_light(string arg);
int do_make(string arg);
int do_liandu(string arg);
void back_owner(object me);

mapping insects = ([
        "zhizhu"        : 100000,
        "chanchu"       : 100000,
        "xiezi"         : 100000,
        "wugong"        : 100000,
        "duzhu"         : 20000,
        "huoxie"        : 20000,
        "jinwugong"     : 20000,
        "heiguafu"      : 5000,
]);

void create()
{
        set_name("木鼎", ({ "mu ding", "muding", "ding" }) );
        set_weight(1000);
        set("long", @LONG
一只木制的鼎，里面散发出香料的气味，但是细细感觉下却有一股腥味。
LONG );
        set("unit", "只");
        set("value", 2500);
        set_max_encumbrance(600);
        setup();
}

int is_container() { return 1; }

void init()
{
        add_action("do_clear", "clear");
        add_action("do_light", "light");
        add_action("do_liandu", "liandu");
        add_action("do_make", "make");
}

int do_clear(string arg)
{
        object me;
        object *ob;
        int i;
        int k;

        if (! id(arg))
                return notify_fail("你要清空什么？\n");

        me = this_player();
        ob = all_inventory(this_object());
        if (! ob)
                return notify_fail("现在" + name() + "里面没有任何东西。\n");

        if( query_temp("id") != query("id", me) && 
            query_temp("id") && environment() != me)
                return notify_fail("人家正用的" + name() + "，你瞎搞什么？\n");

        if (query_temp("lighting"))
        {
                delete_temp("lighting");
                delete_temp("id");
                remove_call_out("catch_insect");
                message_vision("$N把" + name() + "中的火息掉了。\n", me);
        }

        k = 0;
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_insect())
                        continue;

                message_vision("$N把" + name() + "里面的$n倒了出来，扔掉了。\n",
                               me, ob[i]);
                k++;
                destruct(ob[i]);
        }

        if (! k)
                message_vision("$N晃了晃" + name() + "，没啥毒虫。\n", me);

        back_owner(me);
        return 1;
}

int do_light(string arg)
{
        object ob;
        object me;

        me = this_player();
        if( query_temp("id") != query("id", me) && 
            query_temp("id") && environment() != me)
                return notify_fail("人家正用的" + name() + "，你瞎搞什么？\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("这里你也想练毒，不太好吧。\n");

        if (query_temp("lighting"))
                return notify_fail("现在" + name() + "中正在燃烧香料。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢，等一会儿吧。\n");

        if (me->is_fighting())
                return notify_fail("打架的时候你还有心思弄这个？\n");

        if (! objectp(ob = present("xiang liao", me)) ||
            ! ob->query_amount())
                return notify_fail("现在你身上没有香料，无法使用" + name() + "。\n");

        ob->add_amount(-1);
        message_vision(HIM "\n$N" HIM "把" + name() + HIM "摆在地上，放入"
                       "香料，点燃后发出缕缕香气。\n\n" NOR, me);
        set_temp("lighting", 1);
        set_temp("id",query("id", me));

        if (environment() == me)
        {
                this_object()->move(environment(me));
                set("no_get", name() + "里面正烧着香料呢，别乱动！\n");
        }

        remove_call_out("catch_insect");
        call_out("catch_insect", random(2) + 1, me);

        return 1;
}

void back_owner(object me)
{
        if (environment() != me)
        {
                this_object()->move(me);
                if (! me->is_busy())
                        me->start_busy(random(1));
        }
}

void catch_insect(object me)
{
        object env;
        object insect;
        mapping rs;
        string *st;
        int i;
        int sum;

        delete_temp("lighting");
        delete_temp("id");
        delete("no_get");

        env = environment(this_object());
        if (! objectp(me) || environment(me) != env || ! living(me))
        {
                message_vision("香气渐渐的散去了。\n", this_object());
                return;
        }

        if( !query("outdoors", env) || query("no_insect", env) )
        {
                message_vision("香气渐渐散去了，啥也没抓到，看来$N是白忙活了。\n"
                               "$N叹口气，收回了" + name() + "。\n",
                               me);
                back_owner(me);
                return;
        }

        rs = insects;
        if( mapp(query("insects", env)) )
                rs+=query("insects", env);

        st = keys(rs);
        sum = 0;
        for (i = 0; i < sizeof(st); i++)
        {
                if (! intp(rs[st[i]]))
                        rs[st[i]] = 0;
                sum += rs[st[i]];
        }

        if (! sum) return;
        sum = random(sum);
        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < rs[st[i]])
                {
                        catch(insect = new("/clone/insect/" + st[i]));
                        if (! objectp(insect)) break;

                        message_vision(HIG "香气越来越稀薄，突然一" +
                                       query("unit", insect)+insect->name()+
                                       HIG "爬进了" + name() + HIG "。\n" NOR, me);
                        if (! insect->move(this_object()))
                        {
                                message_vision("可惜" + name() + "剩下的空间太小了，" + insect->name() +
                                               "没能钻进去，走掉了。\n", me);
                                destruct(insect);
                                message_vision("$N叹口气，收回了" + name() + "。\n", me);
                                back_owner(me);
                                return;
                        } else
                        if (me->is_fighting() || me->is_busy())
                        {
                                message_vision("可是$N正忙着，只好眼睁睁的看着" +
                                               insect->name() + "又走掉了。\n", me);
                                destruct(insect);
                                return;
                        }
                        insect->unconcious();
                        back_owner(me);
                        message_vision("$N大喜，连忙收起" + name() + "。\n", me);
                        me->start_busy(random(1));
                        return;
                }
                sum -= rs[st[i]];
        }

        message_vision("香气渐渐散去了，啥也没抓到，看来是白忙活了。\n"
                       "$N叹口气，收回了" + name() + "。\n",
                       me);
        back_owner(me);
}

int do_liandu(string arg)
{
        object me;
        object *ob;
        int i;
        int amount;
        int add;

        me = this_player();

        if (me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技火候不够，不能练毒。\n");

        if (me->query_skill("huagong-dafa", 1) < 80)
                return notify_fail("你的化功大法火候不够，不能练毒。\n");

        ob = all_inventory(this_object());
        if (! ob)
                return notify_fail("现在" + name() + "里面没有任何东西。\n");

        if( query_temp("id") != query("id", me) && 
            query_temp("id") && environment() != me)
                return notify_fail("人家正用的" + name() + "，你瞎搞什么？\n");

        if (query_temp("lighting"))
                return notify_fail("现在" + name() + "里面正燃着香料呢。\n");

        for (amount = 0, i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_insect()) continue;
                amount++;
        }

        if (! amount) return notify_fail(name() + "又没啥毒虫，你练什么毒？\n");

        message_vision(HIG "$N" HIG "盘腿坐下，将手伸入" + name() +
                       HIG "，冥神练功。\n\n" NOR, me);

        amount = 0;
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_insect()) continue;
                message_vision(HIM "$n" HIM "慢慢化作桨水，渗入到$N" HIM "手心。\n" NOR,
                               me, ob[i]);
                amount+=query("insect_poison/level", ob[i])*
                          query("insect_poison/maximum", ob[i]);
                destruct(ob[i]);
        }

        me->start_busy(random(1));
        message_vision("\n$N练功完毕，睁开眼睛，站了起来。\n", me);
        amount /= 4;
        if (amount < 5)
        {
                tell_object(me, "你觉得没有任何效果。\n");
                return 1;
        }
 
        if( query("id", this_object()) == "shenmuwang ding" )
                add =1 + random(amount / 2);

        else add = 0;

        if (me->can_improve_skill("poison"))
                me->improve_skill("poison", 1 + random(amount / 2) + add);

        if (me->can_improve_skill("huagong-dafa"))
                me->improve_skill("huagong-dafa", 1 + random(amount / 2) + add);

        tell_object(me, HIG "你觉得你的「化功大法」和「基本毒技」又有了新的进步。\n" NOR);

        return 1;
}

int do_make(string arg)
{
        object me;
        object *ob;
        object du;
        int flvl;
        int plvl;
        int i;
        int amount;

        if (! arg)
                return notify_fail("你想利用" + name() + "制作什么？\n");

        if (arg != "poison" && arg != "du")
                return notify_fail("使用" + name() + "无法制作这种东西。\n");

        me = this_player();

        if (me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技火候不够，不能制毒。\n");

        if (me->query_skill("huagong-dafa", 1) < 80)
                return notify_fail("你的化功大法火候不够，不能制毒。\n");

        ob = all_inventory(this_object());
        if (! ob)
                return notify_fail("现在" + name() + "里面没有任何东西。\n");

        if( query_temp("id") != query("id", me) && 
            query_temp("id") && environment() != me)
                return notify_fail("人家正用的" + name() + "，你瞎搞什么？\n");

        if (query_temp("lighting"))
                return notify_fail("现在" + name() + "里面正燃着香料呢。\n");

        for (amount = 0, i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_insect()) continue;
                amount++;
        }

        if (! amount) return notify_fail(name() + "又没啥毒虫，你怎么制毒？\n");

        message_vision(HIG "$N" HIG "双手围住" + name() +
                       HIG "，运起内功开始制毒。\n\n" NOR, me);

        amount = 0;
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_insect()) continue;
                message_vision(HIM "$n" HIM "慢慢化作桨水...\n" NOR,
                               me, ob[i]);
                amount+=query("insect_poison/level", ob[i])*
                          query("insect_poison/maximum", ob[i]);
                destruct(ob[i]);
        }

        me->start_busy(random(3));
        message_vision("\n$N运功完毕，松开了手\n", me);

        // calculate poison level & duratiin

        flvl = me->query_skill("force");
        plvl = me->query_skill("poison", 1);
        amount += plvl * 3;
        amount += flvl * 3;
        plvl = flvl * 2 / 3 + random((flvl * 2 / 3 + plvl * 2) / 3);
        amount = (amount + plvl / 2) / plvl;
        if (amount < 5)
        {
                tell_object(me, "你发现什么都没有弄出来，看来这次是失败了。\n");
                return 1;
        }

        if (plvl > flvl * 13 / 10)
                plvl = flvl * 13 / 10;

        du = new("/clone/misc/duwan");
        set("poison/name", "剧毒", du);
        set("poison/level", plvl, du);
        set("poison/id",query("id",  me), du);
        set("poison/duration", amount, du);

        du->move(this_object());

        tell_object(me, "你揭开" + name() + "，一粒暗红色的毒丸赫然其中，你赶忙将其取出。\n");

        return 1;
}
