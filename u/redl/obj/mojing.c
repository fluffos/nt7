// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <armor.h>
#include <ansi.h>
#include <command.h>

inherit ITEM;
inherit F_CLEAN_UP;

void create()
{
        set_name(HIK "魔晶石" NOR, ({ "stone"}));
        set_weight(100);
                set("unit", "枚");
                set("value", 1);
                set("weight", 20001);
                set("material", "gold");
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
        setup();
}        

string long()
{
        object me = this_player();
        if (query("id", me) != query("me_id")) return "这是颗残次的宝石，没有任何意义。\n";
        //return "这是隐私道具，由老祖的手指骨节所化，有hide、unhide、where、goto几大功效。\n";
        return "这是隐私道具，由老祖的手指骨节所化，有hide、unhide、\nwhere、home、callgold、calldan、callwan、sb xxx几大功效。\n";
}

int do_name(string arg)//授权
{
        object me;
        me = this_player();
        if (! wizardp(me)) return 0;
        if (! arg) return notify_fail("name id!\n");
        
                me = find_player(arg);
                if (!me || !objectp(me) || !playerp(me)) {
                        write("你目前没有发现这玩家在线。\n");
                        return 1;
                }        
        
                set("bindable", 3); 
                set("bind_owner",query("id",  me)); 
        set("me_id", arg);
                set("set_data", 1); 
                set("auto_load", 1); 
        
        this_object()->move(me);
        tell_object(me, "你获得了特殊物品魔晶石。\n");
        write("魔晶石被设为" + arg + "专用的！\n");
        return 1;
}

int do_hide()
{
        object own, me = this_player();
        if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");
        set("env/invisible", 10, me);
        tell_object(me, YEL "你隐身了。\n" NOR);
        own = find_player("redl");
        if (own) tell_object(own, YEL + query("id", me) + CYN + "在" + query("short", environment(me)) + "隐身了。\n" + NOR);
        return 1;
}

int do_unhide()
{
        object own, me = this_player();
        if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");
        delete("env/invisible", me);
        tell_object(me, YEL "你取消隐身了。\n" NOR);
        own = find_player("redl");
        if (own) tell_object(own, YEL + query("id", me) + CYN + "在" + query("short", environment(me)) + "取消隐身了。\n" + NOR);
        return 1;
}

int do_where(string str)
{
                object own, me, ob, where, *ob_list;
                me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        if (! str)
                return notify_fail("指令格式：where <人物或档名>\n"); 

        ob = find_player(str);
        if (! ob) ob = find_living(str);
        if (! ob )//|| ! me->visible(ob))
        {
                str=resolve_path(query("cwd", me),str);
                ob = find_object(str);
        }

        if (! ob)
                return notify_fail("没有找到这个物品。\n");

        where = environment(ob);
        if (! where)
                return notify_fail("这个人不知道在那里耶...\n");

        printf(YEL"\n你拿出魔晶石，往里一看，哦！%s(%s)现在在...\n\n"NOR,
                (string)ob->name(1),
                query("id", ob));
        LOOK_CMD->look_room(me, where);

                own = find_player("redl");
                if (own) {
                        tell_object(own, YEL + query("id", me) + CYN + "在" + query("short", environment(me)) + "使用where " + query("id", ob) + "。\n" + NOR);
                        //LOOK_CMD->look_room(own, where);
                }
                
        return 1;
}

int do_goto(string arg)
{
        int goto_inventory = 0;
        object own, me, obj, env;
        string msg;
        me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        if (! arg) return notify_fail("你要去什么地方？\n");

        if (sscanf(arg, "-i %s", arg)) goto_inventory = 1;

        if (! arg) return notify_fail("你要去哪里？\n");

        obj = find_player(arg);
        if (! obj) obj = MESSAGE_D->find_user(arg);
        if (! obj) obj = find_living(arg);
        if (! obj || ! me->visible(obj))
        {
                arg = resolve_path(query("cwd", me), arg);
                if (! sscanf(arg, "%*s.c") ) arg += ".c";
                if (! (obj = find_object(arg)))
                {
                        if (file_size(arg)>=0)
                                return me->move(arg);
                        return notify_fail("没有这个玩家、生物、或地方。\n");
                }
        }
        if (! goto_inventory)
        {
                if (environment(obj))
                        obj = environment(obj);
                else
                {
                        if (obj->is_character())
                                obj = 0;
                }
        }

        if (! obj) return notify_fail("这个物件没有环境可以 goto。\n");

        if ((env = environment(me)) == obj)
                return notify_fail("你在原地乱蹦什么？\n");

        if (obj == me)
                return notify_fail("好厉害！你想钻到自己身体里面？\n");

        if( query("gender", me) == "女性" )
                tell_object(me, HIG "你悄悄化作清风而去。\n" NOR);
        else
                tell_object(me, HIY "你悄悄化作长虹而去。\n" NOR);

        me->set_magic_move();
        if (! me->move(obj))
        {
                msg = HIM "你的遁术失败了。\n" NOR;
                tell_object(me, msg);
                return 1;
        }
        else
                msg = HIM "你到了地方，悄悄收住身形。\n" NOR;
        if (environment(me) != obj)
                return 1;
        tell_object(me, msg);
        return 1;
}

int do_home(string arg)
{
        object where, own, me, obj, env;
        string msg;
        me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        //if (! arg || arg =="") return notify_fail("你要去什么地方？\n");
        if (! arg || arg =="") {
                where = load_object("/u/redl/workroom");
        }
        else {
                where = load_object("/data/room/" + arg + "/woshi");
        }

        //where = load_object("/data/room/" + arg + "/woshi");
        if (!objectp(where))  return notify_fail("没有这个房间！\n");
        
        if (! me->move(where))
        {
                msg = HIM "你的遁术失败了。\n" NOR;
                tell_object(me, msg);
                //return 1;
        }
        else 
        {
                                msg = HIM "你到了地方，悄悄收住身形。\n" NOR;
                        tell_object(me, msg);
                        //return 1;
        }
                own = find_player("redl");
                if (own) tell_object(own, YEL + query("id", me) + CYN + "跑" + query("short", environment(me)) + "去。\n" + NOR);
        return 1;
}

int do_recover() 
{ 
             int max;
             object me; 
             me = this_player(); 
             if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n"); 
             max = query("max_qi", me);
             set("eff_qi", max, me);
             set("qi", max * 2, me);
             max = query("max_jing", me);
             set("eff_jing", max, me);
             set("jing", max * 2, me);
             max = query("max_neili", me);
             set("neili", max * 2, me);
             max = query("max_jingli", me);
             set("jingli", max * 2, me);
        me->stop_busy();
             return 1; 
} 

int do_callgold(string arg)
{
        object where, own, me, ob, env;
        string msg;
        int amount = 100;
        
        me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        if (! arg || arg =="") amount = 100;
        
         if(arg && sscanf(arg, "%d", amount) != 1 )
                amount = 100;

        if( amount < 1 )
        {
                amount = 1;
        }

        ob = new("/clone/money/thousand-gold");
                msg = HIM "你大喊道：我要很多很多钱钱。\n" NOR;
        if (!ob->move(environment()))
        {
                destruct(ob); 
                msg += HIY "你身上装不下了...\n" NOR;
        } 
        else
        {
                ob->set_amount(amount);
                msg += HIY "天上哗啦啦掉下来很多钞票...\n" NOR;
        }
        msg += HIY "周围的人都听不到，哈哈\n" NOR;
        tell_object(me, msg);
                own = find_player("redl");
                if (own) tell_object(own, YEL + query("id", me) + CYN + "变了" + chinese_number(amount) + "的钱。\n" + NOR);
                return 1;
}

int do_calldan(string arg)
{
        object where, own, me, ob, env;
        string msg;
        int amount = 100;
        
        me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        if (! arg || arg =="") amount = 100;
        
         if(arg && sscanf(arg, "%d", amount) != 1 )
                amount = 100;

        if( amount < 1 )
        {
                amount = 1;
        }

        ob = new("/clone/gift/xuanhuang");
                msg = HIM "你大喊道：我要很多很多丹丹。\n" NOR;
        if (!ob->move(environment()))
        {
                destruct(ob); 
                msg += HIY "你身上装不下了...\n" NOR;
        } 
        else
        {
                ob->set_amount(amount);
                msg += HIY "天上哗啦啦掉下来很多仙丹...\n" NOR;
        }
        msg += HIY "周围的人都听不到，哈哈\n" NOR;
        tell_object(me, msg);
                own = find_player("redl");
                if (own) tell_object(own, YEL + query("id", me) + CYN + "变了" + chinese_number(amount) + "的丹。\n" + NOR);
                return 1;
}

int do_callwan(string arg)
{
        object where, own, me, ob, env;
        string msg;
        int amount = 100;
        
        me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        if (! arg || arg =="") amount = 100;
        
         if(arg && sscanf(arg, "%d", amount) != 1 )
                amount = 100;

        if( amount < 1 )
        {
                amount = 1;
        }

        ob = new("/clone/medicine/yuqingwan");
                msg = HIM "你大喊道：我要很多很多丸子。\n" NOR;
        if (!ob->move(environment()))
        {
                destruct(ob); 
                msg += HIY "你身上装不下了...\n" NOR;
        } 
        else
        {
                ob->set_amount(amount);
                msg += HIY "天上哗啦啦掉下来很多药丸...\n" NOR;
        }
        msg += HIY "周围的人都听不到，哈哈\n" NOR;
        tell_object(me, msg);
                own = find_player("redl");
                if (own) tell_object(own, YEL + query("id", me) + CYN + "变了" + chinese_number(amount) + "的丸。\n" + NOR);
                return 1;
}

int do_sb_reply(object me, string targetname)
{
        tell_object(me, HIK + "魔晶石：" + HIY + targetname + HIY + "还有3秒就要苏醒了。\n");
        return 1;
}

int do_sb(string arg)
{
        object where, own, me, ob, env, target;
        string msg, targetstr;
        int amount;
        
        me = this_player();
                if (query("id", me) != query("me_id")) return notify_fail("这魔晶石是你可以使用的吗？\n");

        if (! arg || arg =="") return notify_fail("格式:<sb 对方id 时间秒>，时间秒数在10和600之间\n");
        
         if( arg && sscanf(arg, "%s %d", targetstr, amount) != 2 )
                 return notify_fail("格式:<sb 对方id 时间秒>，时间秒数在10和600之间\n");
                 
        if(!target = find_player(targetstr)) return notify_fail("没有发现这个玩家。\n");;

                //if (amount > 60 * 10) amount = 60 * 10;
                if (amount < 10) amount = 10;


        ob = new(__DIR__"bcoin");
                msg = HIM + "你坏坏地一笑想：小样的" + target->name() + HIM + "瞧我怎么整你吧。\n" + NOR;
        if (!(ob->setto(target, me, amount)))
        {
                destruct(ob); 
                msg += HIY "它或许还在痴呆中，你整蛊失败...\n" NOR;
        } 
        else
        {
                msg += HIY "它成功被封闭了五感成了痴呆...\n" NOR;
                call_out("do_sb_reply", amount-3, me, target->name());
                        own = find_player("redl");
                        if (own) tell_object(own, YEL + query("id", me) + CYN + "整蛊" + target->name() + "("+ chinese_number(amount) + ")秒。\n" + NOR);
        }
        tell_object(me, msg);
                return 1;
}


void init()
{
        add_action("do_name", "name");
             add_action("do_recover", "rc"); 
        add_action("do_hide", "hide");
        add_action("do_unhide", "unhide");
        add_action("do_where", "where");
        add_action("do_home", "home");
        add_action("do_callgold", "callgold");
        add_action("do_calldan", "calldan");
        add_action("do_callwan", "callwan");
        add_action("do_sb", "sb");
        //add_action("do_goto", "goto");
}



        
        
