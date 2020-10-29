#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "干将圣符" NOR, ({ "ganjiang charm", "charm" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIM "干将圣符可以将普通道具升级为可SUMMON道具，以后可以随时\n"
                            "召唤(SUMMON)升级后的道具。\n"
                            "指令格式： upd <欲升级道具ID> to <SUMMON的代号> \n" NOR);
                        
                set("unit", "块");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_integrate", "upd");
}

int do_integrate(string arg)
{
        object me;
        object ob;
        string filename, content;
        string item, str;
        mapping data;

        if (! arg)
                return notify_fail("你要往什么道具上使用该圣符？\n");
        
        if (sscanf(arg, "%s to %s", item, str) != 2)
                return notify_fail("指令格式： upd <欲升级道具ID> to <SUMMON的ID> \n");
                
        me = this_player();
        if (! objectp(ob = present(item, me)) /*&&
            ! objectp(ob = present(item, environment(me)))*/)
                return notify_fail("你身上没有这样道具啊。\n");

        if (member_array(F_EQUIP, deep_inherit_list(ob)) == -1 &&
            !query("can_summon", ob) )
                return notify_fail("这类物品无法升级。\n");        
        
        if( query("unique", ob) || ob->is_item_make() || 
            ob->is_character() || ! clonep(ob) || ob->is_no_clone() ||
            query("task_ob", ob) || query("no_store", ob) || 
            query("maze_item", ob) )
                return notify_fail("这个物品无法升级。\n");
        
        if( query("money_id", ob) )
                return notify_fail("你没用过钱啊？\n"); 
                
        if( query("only_do_effect", ob) || 
            query("food_supply", ob) )
                return notify_fail("这个物品无法升级。\n");
                
        if( sscanf(base_name(ob), "/data/%*s") || query("item_owner", ob) )      
                return notify_fail("这类物品无法再升级。\n");

        if( query("equipped", ob) )
                return notify_fail("你先卸除他先。\n");

        if( mapp(query("can_summon", me)) && sizeof(query("can_summon", me)) )
        {
                if( member_array(str,keys(query("can_summon", me))) != -1 )
                        return notify_fail("你已经有同样的SUMMON ID了,请重新换个!\n");
                        
                if( member_array(base_name(ob),values(query("can_summon", me))) != -1 )
                        return notify_fail("这个物品已经升级过了。\n");
        }
                
        message_sort(HIR "\n$N" HIR "用利刃将双手手心划破，双掌贴在" + ob->name() + HIR "上，"
                     "渐渐地，" + ob->name() + HIR "将$N" HIR "的鲜血吸收……\n\n" NOR, me);

        tell_object(me, "你把" + name() + "盖在" + ob->name() + "上，然后口中念念有词，\n"
                        "只见圣符化作一道红光飞入" + ob->name() + "体内！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"发生了不可言喻的变化。\n" NOR);
        
        data = copy(ob->query_entire_dbase());
        data["item_owner"] = query("id", me);
        data["no_sell"] = 1;
        data["no_store"] = 1;
        
        if( filename=TEMPLATE_D->create_file(base_name(ob),query("id", ob),data) )
        {       
                content = @TEXT

int is_no_clone() { return 1; }

TEXT;
                write_file(filename, content);
                
                destruct(ob);    
                catch(call_other(filename, "???"));
                ob = find_object(filename);      
                if (! ob)
                {
                        write("文件出错，请与巫师联系！\n");
                        log_file("static/template", sprintf("%s %s creating  %s(%s) had errors.\n",
                                 log_time(),log_id(me),filter_color(ob->name(1)),query("id", ob)));
                        return 1;
                } else
                {
                        ob->move(me, 1);
                        //str = replace_string(str, " ", "-");
                        tell_object(me, HIG "开光成功！以后请用 summon " + 
                                    str + " 来召唤该物品。\n" NOR);
                        log_file("static/template", sprintf("%s %s created  %s(%s)\n",
                                 log_time(), log_id(me),
                                 filter_color(ob->name(1)),query("id", ob)));
                }
                set("can_summon/"+str, base_name(ob), me);
                me->save();
        }                                     

        destruct(this_object());
        return 1;
}
