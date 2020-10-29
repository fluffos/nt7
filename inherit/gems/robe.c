#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_GEMS;

void init_sockets(object me)
{
        set("max_sockets", 3);
        if (me->query("combat_exp") > 10000000)
                add("max_sockets", 1);
        if ((int)query("sockets/max")>5)
        set("sockets/max",5);

        if (me->query("diablo/" + TYPE_CLOTH + "/id") != query("id")) return;

        set("sockets", me->query("diablo/" + TYPE_CLOTH + "/sockets"));
        set_armor_desc();
}

void setup()
{
        init_sockets(this_player());
        ::setup();
}

void spec_prop(object me, string socket, int socket_level, int mode)
{
        if (!valid_gem(socket, socket_level)) return;
        if (me->query("diablo/" + TYPE_CLOTH + "/id") != query("id")) return;
        switch (socket) {
        case "ruby":
                break;
        case "topaz":
                break;
        case "sapphire":
                break;
        case "emerald":
                break;
        case "amethyst":
                if (mode == 1)
                        message_vision(MAG + query("name") + MAG"散出一片紫色云光环绕着$N，渐渐$P的身形显得越来越朦胧！\n"NOR, me);
                else
                        message_vision(MAG"紫色越来越淡，$N的身形又显露了出来。\n"NOR, me);
                me->add_temp("apply/defense", 50 * socket_level * mode);
                break;
        case "diamond":
                if (mode == 1)
                        message_vision(HIW"只见$N身上的" + query("name") + HIW"表面晶彩流动，毫光四射！\n"NOR, me);
                else
                        message_vision(HIW"渐渐的，" + query("name") + HIW"似乎又恢复了寻常。\n"NOR, me);
                me->add_temp("apply/armor", query("armor_prop/armor") * socket_level * mode / 10);
                break;
        case "skull":
                break;
        }
        return;
}

int wear()
{
        int i, sockets, ret;
        object me = environment();

        if (!(ret = ::wear())) return 0;
        sockets = query("sockets/max");
        for (i = 1; i <= sockets; i++)
                spec_prop(me, query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)), 1);

        remove_call_out("check_fight");
        call_out("check_fight", 1, me);

        return ret;
}

int unequip()
{
        int i, sockets, ret;
        object me = environment();

        if (!(ret = ::unequip())) return 0;
        sockets = query("sockets/max");
        for (i = 1; i <= sockets; i++)
                spec_prop(me, query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)), -1);

        remove_call_out("check_fight");

        return ret;
}

int spec_effect(object ob, object me, int damage, string socket, int socket_level)
{
        int i, def = 0;

        if (!valid_gem(socket, socket_level)) return def;
        if (me->query("diablo/" + TYPE_CLOTH + "/id") != query("id")) return 0;
        if (random(100) + me->query_temp("apply/magic") < 70) return def;

        switch (socket) {
        case "ruby":
                break;
        case "topaz":
                break;
        case "sapphire":
                break;
        case "emerald":
                if (!ob->query_condition("emerald_poison")) {
                        message_vision(HIG"$n大叫：不好！只见一道绿气迅速延伸到$p的手臂！\n"NOR, me, ob);
                        ob->apply_condition("emerald_poison", ob->query_condition("emerald_poison") + random(5) + 1);
                        ob->set("emerald_poison", socket_level);
                        if (!ob->is_killing(me->query("id")) && (ob->query("host_id") != me->query("id")))
                                ob->kill_ob(me);
                }
                break;
        case "amethyst":
                break;
        case "diamond":
                message_vision(HIW"$n只觉$N身上似乎有一股柔力将$p的劲力化去不少！\n"NOR, me, ob);
                def = -damage * socket_level / 10;
                break;
        case "skull":
                if (objectp(ob->query_temp("weapon")))
                        i = damage * socket_level / 20;
                else
                        i = damage * socket_level / 10;
                if (i > 0) {
                        message_vision(WHT"忽然$N周围阴气大盛，$n只感到气血汹涌，无法自控！\n"NOR, me, ob);
                        ob->receive_damage("qi", i);
                        ob->receive_wound("qi", random(i));
                        if (wizardp(me))
                                tell_object(me, sprintf("反震伤害力： %d\n", i));
                }
                break;
        }
        return def;
}

int ob_hit(object ob, object me, int damage)
{
        int i, sockets, ret = 0;

        sockets = query("sockets/max");
        for (i = 1; i <= sockets; i++)
                ret += spec_effect(ob, me, damage,
query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)));
        return ret;
}

void spec_recover(object me, string socket, int socket_level)
{
        int i;

        if (!valid_gem(socket, socket_level)) return;
        if (me->query("diablo/" + TYPE_CLOTH + "/id") != query("id")) return;
        if (random(100) + me->query_temp("apply/magic") < 70) return;

        switch (socket) {
        case "ruby":
                if (me->query("max_qi") > me->query("eff_qi") || me->query("eff_qi") > me->query("qi")) {
                        message_vision(HIR"只见$N的伤口红光流动，血流顿时止住了，连伤口似乎也开始渐渐愈合！\n"NOR, me);
                        me->add("eff_qi", 50 * socket_level);
                        if (me->query("eff_qi") > me->query("max_qi"))
                                me->set("eff_qi", me->query("max_qi"));
                        me->add("qi", 100 * socket_level);
                        if (me->query("qi") > me->query("eff_qi"))
                                me->set("qi", me->query("eff_qi"));
                }
                break;
        case "topaz":
                if (me->query("max_jing") > me->query("eff_jing") || me->query("eff_jing") > me->query("jing")) {
                        message_vision(HIY"只见$N的双眼开合之间金光闪现，精神顿时大振！\n"NOR, me);
                        me->add("eff_jing", 20 * socket_level);
                        if (me->query("eff_jing") > me->query("max_jing"))
                                me->set("eff_jing", me->query("max_jing"));
                        me->add("jing", 40 * socket_level);
                        if (me->query("jing") > me->query("eff_jing"))
                                me->set("jing", me->query("eff_jing"));
                }
                break;
        case "sapphire":
                if (me->is_busy() && (me->query_busy() <= socket_level + 1 )) {
                        message_vision(HIB"$N只觉一股劲力引导着内气游走全身，被阻塞的穴道在它的冲击下已一贯而通！\n"NOR, me);
                        me->start_busy(0);
                }
                break;
        case "emerald":
                break;
        case "amethyst":
                break;
        case "diamond":
                break;
        case "skull":
                break;
        }
        return;
}

void check_fight(object me)
{
        int i, sockets;

        if (!me || !query("equipped")) return;
        if (me->query("diablo/" + TYPE_CLOTH + "/id") != query("id")) return;
        if (living(me) && me->is_fighting()) {
                sockets = query("sockets/max");
                for (i = 1; i <= sockets; i++)
                        spec_recover(me, query(sprintf("sockets/socket%d", i)),
query(sprintf("sockets/socket%d_level", i)));
        }

        call_out("check_fight", 1, me);
}
void dest() { destruct(this_object()); }
void owner_is_killed() { call_out("dest",1); }