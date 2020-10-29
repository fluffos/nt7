// This program is a part of NT MudLIB
// enchant
// Written by Lonely@nitan.org

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        string what, tessera;
        object item, obj;
        object scroll;
        int flag = 0;

        if( !arg || sscanf(arg,"%s from %s", tessera, what) != 2 )
                return notify_fail("指令格式：enchant <物品> from <装备>\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if( me->is_fighting() )
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if( !objectp(obj = present(tessera, me)) )
                return notify_fail("你身上没有 " + tessera + " 这种物品啊。\n");

        if( !objectp(item = present(what, me)) )
                return notify_fail("你身上没有" + what + "这样装备啊。\n");

        if( me->query_skill("enchanting", 1) < 200 )
                return notify_fail("你觉得你的附魔技艺还不够娴熟，不敢贸然动手。\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("你现在的精力修为有限，无法附魔物品。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你现在精力不济，无法附魔物品。\n");

        if( query("equipped", item) )
                return notify_fail("你先卸除他先。\n");

        if( query("no_identify", item) )
                return notify_fail("此物品还没有签定。\n");

        if( !query("enchase", item) || !query("enchase/apply_prop", item) )
                return notify_fail("这个物品上面没有可用作附魔的属性。\n");

        if( item->is_item_make() || !query("insert", item) )
                return notify_fail("这个物品无法用来附魔的属性。\n");

        if( query("maze_item", item) )
                return notify_fail("这个物品来历不明，不可以用作附魔属性。\n");

        if( query("enchase/increase", item) )
                return notify_fail("改造过的装备不可以用作附魔属性。\n");

        if( !query("can_enchant", obj) )
                return notify_fail("只有日魂和月魄才可以用来附魔装备属性。\n");

        if( query("enchase", obj) )
                return notify_fail(obj->name()+"上已经附魔过属性了。\n");

        if( query("skill_type", item )
         || (query("armor_type", item) == "hands"
         || query("armor_type", item) == "finger") )
        {
                if( query("can_enchant", obj) != "weapon" )
                        return notify_fail("只有日魂才可以用来附魔此装备属性。\n");
        }
        else
        {
                if( query("can_enchant", obj) != "armor" )
                        return notify_fail("只有月魄才可以用来附魔此装备属性。\n");
        }

        scroll = present("enchant scroll", me);

        if( objectp(scroll) )
                tell_object(me, HIW "\n你双目微闭，将"+item->name()+HIW"和"+obj->name()+HIW"置于附魔卷轴上凝于身前，运转内劲迫"
                        "使它们空中旋转交融。\n" NOR);
        else
                tell_object(me, HIW "\n你双目微闭，将"+item->name()+HIW"和"+obj->name()+HIW"凝于身前，运转内劲迫"
                        "使它们空中旋转交融。\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);

        flag = obj->do_extract(me, item);

        if( flag ) {
                message("vision", HIW "\n霎时间只见" + me->name() + HIW "身前一道"
                        "光华闪过，但转瞬即逝，似乎发生了什么不同寻常的"
                        "事情。\n\n" NOR, environment(me), ({me}));

                tell_object(me, HIW "霎时间只见万道光华疾闪而过，你急忙伸出双手将"+obj->name()+HIW"接住，"
                        "发现掌心"+obj->name()+HIW"蕴漾着七色霞光。\n\n" NOR);

                if( objectp(scroll) )
                {
                        tell_object(me, HIW"只见"+scroll->name()+HIW"在内力注入下已化为灰烬。\n"NOR);
                        destruct(scroll);
                }
                
                addn("max_jingli", -1, me);

                return 1;
        }
        if( objectp(scroll) )
        {
                tell_object(me, HIW"但见"+scroll->name()+HIW"在内力注入下已化为灰烬。\n"NOR);
                destruct(scroll);
        }
        else
        {
                tell_object(me, HIW"但见"+item->name()+HIW"瞬间破裂，变成片片碎片洒落一地。\n");
                destruct(item);
        }

        tell_object(me, HIR "你不禁一声长叹。\n" NOR);

        return 1;
}
