// gems - by xbd

#include <ansi.h>

inherit ITEM;
inherit F_GEMS;

void create()
{
        int lev, i;
        string gem, s;
        object me = this_player();

        i = random(17);
        if (i < 3) gem = "ruby";
        else if (i < 6) gem = "topaz";
        else if (i < 9) gem = "sapphire";
        else if (i < 12) gem = "emerald";
        else if (i < 15) gem = "amethyst";
        else if (i < 16) gem = "diamond";
        else gem = "skull";

        i = random(100);
        if (i < 50) lev = 1;
        else if (i < 75) lev = 2;
        else if (i < 90) lev = 3;
        else if (i < 95) lev = 4;
        else if (i < 96) lev = 5;
        else if (i < 97) lev = 6;
        else if (i < 98) lev = 7;
        else lev = 8;

        set_name(query_gem_name(gem, lev), ({query_gem_id(gem, lev)}));
        set_weight(100);
        set("long", query_all_effect(gem));
        set("unit", "颗");
        set("no_put",1);
//        set("no_get",1);
set("no_sell",1);        
//        set("no_drop",1);
        set("no_beg",1);
        set("no_steal",1);
        set("no_clone",1);
        set("no_pawn",1);
        set("value", 100000 * lev * lev * lev);
        set("material", gem);
        set("level", lev);
        setup();
}

void init()
{
        add_action("do_insert", "insert");
        add_action("do_combine", "combine");
}

int do_insert(string arg)
{
        int index;
        string gem, item_name;
        object ob, me = this_player();

        if (!arg || arg == "")
                return notify_fail("指令格式：insert 宝石 into 物品 at socket 编号\n");
        if (sscanf(arg, "%s into %s at socket %d", gem, item_name, index) != 3)
                return notify_fail("指令格式：insert 宝石 into 物品 at socket 编号\n");
        if (gem != query("id")) return 0;
        if (!objectp(ob = present(item_name, me)))
                return notify_fail("你想把它镶嵌在什么东西上？\n");
        if (index > ob->query("sockets/max"))
                return notify_fail(ob->name() + "上好象并没有这个接孔呀！\n");
        if (ob->query("equipped"))
                return notify_fail(ob->name() + "正装备着呢！\n");
        if (me->query("max_neili") < 1000 || me->query("neili") < 1500)
                return notify_fail("以你现在的内力修为，还无法运功镶嵌宝石！\n");

        message_vision(HIG"$N暗运内力，一使劲把" + name() + HIG"镶入了" + ob->name() + HIG"中，
刹那间，只觉" + ob->name() + HIG"上泛出一道奇异的光芒，似乎有一股神奇的力量附在其中！\n", me);
        me->add("max_neili", -100);
        me->add("neili", -1000);
        me->start_busy(2);
        ob->set(sprintf("sockets/socket%d", index), query("material"));
        ob->set(sprintf("sockets/socket%d_level", index), query("level"));

        seteuid(ROOT_UID);
        reload_object(ob);
        seteuid(getuid());
        destruct(this_object());

        return 1;
}

int do_combine(string arg)
{
        int i;
        object *inv, gem, me = this_player();

        if (!arg || arg == "")
                return notify_fail("你想合并什么宝石？\n");
        if (arg != query("id")) return 0;
        if (query("level") == 8)
                return notify_fail("这个宝石已经是最高等级了！\n");
        if (me->query("max_neili") < 500 || me->query("neili") < 800)
                return notify_fail("以你现在的内力修为，还无法运功合并宝石！\n");

        inv = all_inventory(me);
        for(i = 0; i < sizeof(inv); i++)
                if (inv[i] != this_object() && inv[i]->query("id") == query("id")) {
                        if (!objectp(gem))
                                gem = inv[i];
                        else {
                                message_vision(HIG"$N暗运内力劲透宝石，但见" + name() + HIG"表面异彩流动，
渐渐的$N收回了内力，只觉" + name() + HIG"似乎变得更加完美了！\n", me);
                                me->add("max_neili", -10);
                                me->add("neili", -500);
                                me->start_busy(1);
                                new_gem(query("material"), query("level") + 1)->move(me);
                                destruct(gem);
                                destruct(inv[i]);
                                destruct(this_object());
                                return 1;
                        }
                }
        return notify_fail("你必须有三块同样的宝石才能进行合并！\n");
}
