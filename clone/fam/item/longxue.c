#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "龙血" NOR, ({ "dragon blood", "dragon", "blood" }) );
        set_weight(30);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一瓶龙之血液，可以用来修复镶嵌物(指令 rehab)。\n "
                            HIY "下线丢失    ：   否\n"NOR);
                set("value", 2000000);
                set("unit", "瓶");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_rehab", "rehab");
        }
}

int do_rehab(string arg)
{
        object me;
        object ob;
        string enid, obid;

        me = this_player();

        if (! arg)return notify_fail("指令格式：rehab <镶嵌物品ID> in <道具ID>\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if (sscanf(arg, "%s in %s", enid, obid) != 2)
                return notify_fail("指令格式：rehab <镶嵌物品ID> in <道具ID>\n");

        if (! objectp(ob = present(obid, me)))
                return notify_fail("你身上没有这样道具。\n");         
        
        if (! ob->query("enchase"))
                return notify_fail(ob->name() + "好象没有镶嵌什么吧！\n" NOR);

        if (! ob->query("enchase/" + enid))
                return notify_fail(ob->name() + "上没有这个镶嵌物品。\n" NOR);

        if (ob->query("enchase/" + enid + "/cur_firm") >= 99)
                return notify_fail(ob->query("enchase/" + enid + "/name") + "目前并不需要增加坚固。\n");

        // 开始为镶嵌物品增加坚固
        ob->set("enchase/" + enid + "/cur_firm", 99);
        ob->save();

        tell_object(me, HIG + ob->query("enchase/" + enid + "/name") + "的坚固增加了！\n" NOR);

        destruct(this_object());

        return 1;
}

int query_autoload()
{
         return 1;
}