// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// resolve

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        object item, ob;
        object scroll;
        mapping *ins;
        int    i, j;
        string *ks;
        string my_id, my_name;
        mapping apply;
        mapping data;

        if( !arg )
                return notify_fail("指令格式：resolve <动态装备>\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if( me->is_fighting() )
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if( !objectp(item = present(arg, me)) )
                return notify_fail("你身上没有" + arg + "这样装备啊。\n");

        if( !objectp(scroll = present("resolve scroll", me)) )
                return notify_fail("你身上没有分解卷轴。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你现在的内力修为有限，无法分解物品。\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("你现在的精力修为有限，无法分解物品。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你现在精力不济，无法分解物品。\n");

        if( query("equipped", item) )
                return notify_fail("你先卸除他先。\n");

        if( query("no_identify", item) )
                return notify_fail("此物品还没有签定。\n");

        if( sscanf(base_name(item), "/data/%*s") || query("item_owner", item) )
                return notify_fail("你先解除该物品的被绑定状态。\n");

        if( query("quality_level", item) < 3 && (!query("enchase", item) || !query("enchase/apply_prop", item)) )
                return notify_fail("这个物品上面没有可用来分解的属性元素。\n");

        if( item->is_item_make() || (query("quality_level", item) < 3 && !sizeof(ins=query("insert", item))) )
                return notify_fail("这个物品无法用来分解属性元素。\n");

        if( query("maze_item", item) )
                return notify_fail("这个物品来历不明，不可以用来分解。\n");

              if( query("unique", item) ) //redl 2014
                      return notify_fail("这个物品来历不明，不可以用来分解。\n"); 

        if( !query("weapon_prop", item) && !query("armor_prop", item) )
                return notify_fail("这个物品不是完整的装备，不可以用来分解。\n");

        if( query("enchase/increase", item) )
                return notify_fail("改造过的装备不可以用来分解属性元素。\n");

        tell_object(me, HIM "\n你双目微闭，将分解卷轴与"+item->name()+HIM"凝于身前，运转内劲迫"
                        "使它们空中旋转交融。\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);
        
        for( i=0; i<sizeof(ins); i++ ) {
                apply = copy(ins[i]["apply_prop"]);
                ks = keys(apply);
                for( j=0; j<sizeof(ks); j++ ) {
                        my_id = ks[j];
                        my_name = EQUIPMENT_D->chinese(my_id)+"元素";
                        data = ([]);
                        data["element"] = my_id;
                        data["name"] = my_name;
                        ob = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data);
                        ob->set_name(my_name, ({my_id, "element"}));
                        ob->move(me, 1);
                }
        }
        
        if( query("quality_level", item) > 2 )
        {
                ob = new("/clone/tessera/jhunshi");
                if( query("skill_type", item) )
                {
                        apply = copy(query("weapon_prop", item));
                        map_delete(apply, "damage");
                        
                        set("enchase/apply_prop", apply, ob);
                        set("enchase/type", query("skill_type", item), ob);
                }
                else
                {
                        apply = query("armor_prop", item);
                        map_delete(apply, "armor");
                        if( query("armor_type", item) == "hands" ||
                            query("armor_type", item) == "finger" )
                                map_delete(apply, "unarmed_damage");
                                
                        set("enchase/apply_prop", apply, ob);
                        set("enchase/type", query("armor_type", item), ob);
                }
                
                set("quality_level", query("quality_level", item), ob);
                set("set_data", 1, ob);
                ob->move(me, 1);
        }
        
        
        
        map_delete(apply, "damage");
        
        message("vision", HIW "\n霎时间只见" + me->name() + HIW "身前一道道"
                "光华闪过，但转瞬即逝，似乎发生了什么不同寻常的"
                "事情。\n\n" NOR, environment(me), ({me}));

        tell_object(me, HIW "霎时间只见万道光华疾闪而过，你急忙伸出双手，发现掌心蕴漾着七色霞光。\n\n" NOR);

        addn("max_jingli", -1, me);
        destruct(scroll);
        destruct(item);

        return 1;
}

