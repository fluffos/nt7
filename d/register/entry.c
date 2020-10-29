// regiser: entry.c
// by Doing

#include <ansi.h>
#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_choose(string arg);
int do_washto(string arg);
int do_born(string arg);

mapping born = ([
        "关外人氏" : "/d/guanwai/kedian",
        "燕赵人氏" : "/d/beijing/kedian",
        "齐鲁人氏" : "/d/taishan/kedian",
        "秦晋人氏" : "/d/changan/kezhan",
        "蒙古人氏" : 0,
        "中原人氏" : "/d/nanyang/kedian1",
        "西域人氏" : "/d/xingxiu/kezhan",
        "荆州人氏" : "/d/jingzhou/kedian",
        "扬州人氏" : "/d/city/kedian",
        "苏州人氏" : "/d/suzhou/kedian",
        "杭州人氏" : "/d/hangzhou/kedian",
        "福建人氏" : "/d/fuzhou/rongcheng",
        "巴蜀人氏" : "/d/chengdu/kedian",
        "云南人氏" : "/d/dali/kedian",
        "黔中人氏" : 0,
        "两广人氏" : "/d/foshan/beidimiao",
        "欧阳世家" : ([ "born"      : "西域人氏",
                        "surname"   : "欧阳",
                        "startroom" : "/d/baituo/dating",
                     ]),
        "关外胡家" : ([ "born"      : "关外人氏",
                        "surname"   : "胡",
                        "startroom" : "/d/guanwai/xiaowu",
                     ]),
        "段氏皇族" : ([ "born"      : "大理人氏",
                        "surname"   : "段",
                        "startroom" : "/d/dali/wangfugate",
                     ]),
        "慕容世家" : ([ "born"      : "江南人氏",
                        "surname"   : "慕容",
                        "startroom" : "/d/yanziwu/cuixia",
                     ]),
        "唐门世家" : ([ "born"      : "巴蜀人氏",
                        "surname"   : "唐",
                        "startroom" : "/d/tangmen/kedian",
                     ]),
]);

void create()
{
        int i, k;
        string desc;
        string *position;

        set("short", HIR "生命之谷" NOR);
        set("long",
"混沌初分盘古开天地，迷雾、微风，天地初开，四周混沌，雾茫\n"
"茫一片，这里就是子天丑地人寅出的生命之谷。\n"
"　　谷中有一个石头砌成的池子，其中水清澈却不见底，不知道它究\n"
"竟有多深，池子正上方悬挂着太极两仪四象，不知有何奥妙？！\n"
);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/pangu" : 1,
        ]));

        // set("no_say", "盘古正在闭目沉思，你哪里敢乱说话？\n");

/*
        set("item_desc", ([
                "paizi" : "投胎乃人生大事，切记不可草率！选好方向，就输入born <地名>。\n"
        ]));

        desc = query("item_desc/paizi");
        position = keys(born);

        for (i = 0, k = 1; i < sizeof(position); i++)
        {
                if (! stringp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIW "%s" NOR "\n", k++, position[i]);
        }

        for (i = 0; i < sizeof(position); i++)
        {
                if (! mapp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIC "%s" NOR "\n", k++, position[i]);
        }
        set("item_desc/paizi", desc);
*/

        setup();
}

void init()
{
        add_action("do_choose", "choose");
        add_action("do_washto", "washto");
        add_action("do_born", "born");
}

int do_choose(string arg)
{
        object me;
        int n;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        
        if (! arg || arg == "")
                n = 1;
        else
                sscanf(arg, "%d", n);

        if (n < 1 || n > 4)
        {
                write("您只能选择(choose)系统所提供的这四种角色性格：\n"
                    HIC "1" NOR ".光明磊落  "
                    HIC "2" NOR ".狡黠多变  "
                    HIC "3" NOR ".心狠手辣  "
                    HIC "4" NOR ".阴险奸诈 ("
                    HIC "choose 1" NOR "-" HIC "4" NOR ")\n");
                return 1;
        }

        switch(n)
        {
        case 1:
                set("character", "光明磊落", me);
                break;
        case 2:
                set("character", "狡黠多变", me);
                break;
        case 3:
                set("character", "心狠手辣", me);
                break;
        case 4:
                set("character", "阴险奸诈", me);
                break;
        }
        
        write(HIC"你选择了"NOR+HIM+query("character", me)+NOR+HIC"的性格，接下来你可以洗(washto)天赋了。\n"NOR,me);
        write(HIY "新手导师：戚长发有洗天赋丹出售(一两黄金)，可以重新设定天赋，所以你不用在这里纠结而浪费时间。\n" NOR); 
        write("指令格式：washto <膂力> <悟性> <根骨> <身法>\n例    如：washto 20 20 20 20\n"); 
        return 1;
}
        
int do_wash(string arg)
{
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query("character", me) )
        {
                write(HIC "你还是先确定(choose)好你的角色性格再选天赋吧。\n" NOR, me);
                return 1;
        }
                
        write(HIC "你跳入生命池，顿时被一股激流卷了进去。\n" NOR, me);

        tmpstr = tmpint = tmpcon = tmpdex = 13;

        switch(query("type", me) )
        {
        case "猛士型":
                tmpstr = 20;
                break;

        case "智慧型":
                tmpint = 20;
                break;

        case "耐力型":
                tmpcon = 20;
                break;

        case "敏捷型":
                tmpdex = 20;
                break;

        default:
                break;
        }

        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: if (tmpstr < 30) tmpstr++; else i--; break;
                case 1: if (tmpint < 30) tmpint++; else i--; break;
                case 2: if (tmpcon < 30) tmpcon++; else i--; break;
                case 3: if (tmpdex < 30) tmpdex++; else i--; break;
                }
        }

        my = me->query_entire_dbase();

        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);

        write(HIC "“啪”的一声，你被湿漉漉的抛了出来。\n" NOR, me);
        write(sprintf(HIY "\n你这次获得的四项先天天赋分别是：\n"
                          "膂力：【 " HIG "%d" HIY " 】 "
                          "悟性：【 " HIG "%d" HIY " 】 "
                          "根骨：【 " HIG "%d" HIY " 】 "
                          "身法：【 " HIG "%d" HIY " 】\n"
                          "如果你满意，就去投胎(born)吧！\n\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        set_temp("washed", 1, me);

        return 1;
}

int do_washto(string arg) 
{ 
        int tmpstr, tmpint, tmpcon, tmpdex, dower; 
        object me; 
        mapping my; 
  
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query("character", me) )
        {
                write(HIC "你还是先确定(choose)好你的角色性格再选天赋吧。\n" NOR, me);
                return 1;
        }
        
        if (! arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) != 4)
                return notify_fail("指令格式：washto <膂力> <悟性> <根骨> <身法>\n" +
                                   "例    如：washto 20 20 20 20\n"); 
  
        if (tmpstr > 30 || tmpstr < 13) 
                return notify_fail("你所选择的膂力数值要求必须在13和30之间。\n"); 
        
        if (tmpint > 30 || tmpint < 13) 
                return notify_fail("你所选择的悟性数值要求必须在13和30之间。\n"); 
                
        if (tmpcon > 30 || tmpcon < 13) 
                return notify_fail("你所选择的根骨数值要求必须在13和30之间。\n"); 
                
        if (tmpdex > 30 || tmpdex < 13) 
                return notify_fail("你所选择的身法数值要求必须在13和30之间。\n"); 

        if (tmpstr + tmpint + tmpcon + tmpdex > 80) 
                return notify_fail("你所选择的天赋数值总和不能大于80。\n"); 
        
        dower = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
      
        write(HIC "你跳入忘忧池，顿时被一股激流卷了进去。\n" NOR, me); 
        my = me->query_entire_dbase(); 
  
        my["str"] = tmpstr; 
        my["int"] = tmpint; 
        my["con"] = tmpcon; 
        my["dex"] = tmpdex; 
        my["kar"] = 28 + random(3); 
        my["per"] = 28 + random(3); 
        if (dower > 0)
                my["dow"] = dower;
          
/*
        write(HIC "只听“啪”的一声，你被湿漉漉的抛了出来。\n" NOR, me); 
        write(sprintf(HIY "\n你这次获得的四项先天天赋分别是：\n" 
                    "膂力：【 " HIG "%d" HIY " 】 " 
                    "悟性：【 " HIG "%d" HIY " 】 " 
                    "根骨：【 " HIG "%d" HIY " 】 " 
                    "身法：【 " HIG "%d" HIY " 】\n" 
                    "天赋总和为【 " HIR "%d" HIY " 】，如果你满意，就去投胎(born)吧！方法如" HIR "<born 扬州人氏>\n\n" NOR,
                     tmpstr, tmpint, tmpcon, tmpdex, 80 - dower)); 
*/
        set_temp("washed", 1, me);
  

        set("startroom", "/d/newbie/shijiezhishu", me);
        set("born", "古村", me);
        set("born_family", "没有", me);
        // 选择特殊技能
        UPDATE_D->born_player(me);

        me->move("/d/newbie/shijiezhishu");
        set("mud_age", 0, me);
        set("age", 11, me);
        me->save();
        message_vision("$N揉揉眼睛，迷惘的望着这个陌生的世界。\n", me);
        tell_object(me, HIY "新手导师：查看本人所在地的地图指令map，查看所有地图指令为map map\n" NOR);
        return 1; 
}

int do_born(string arg)
{
        object me;
        object obj;
        object item;
        mixed dest;
        string new_name;
        string msg;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query("character", me) )
                return notify_fail("你先选择(choose)好角色性格，你再投胎也不迟啊！\n");
                
        if( !query_temp("washed", me) )
                return notify_fail("你先在生命池中洗一下(washto)，选择好天赋你再投胎也不迟啊！\n");

        if (arg && arg[0] < 160)
                return notify_fail("你必须输入中文地名，比如born 扬州人氏，或者是born 欧阳世家以避免投错胎。\n");

        new_name = 0;
        if (arg) sscanf(arg, "%s %s", arg, new_name);

        if (! arg || (! stringp(dest = born[arg]) && ! mapp(dest)))
        {
                message_vision("有个声音恶狠狠的对$N说：你要干什么！投胎去哪里？\n", me);
                return 1;
        }

        if (mapp(dest) && stringp(dest["notice"]))
                return notify_fail(dest["notice"]);

        if (stringp(dest))
        {
                if (! objectp(obj = find_object(dest)))
                        obj = load_object(dest);
                set("startroom", dest, me);
                set("born", arg, me);
                set("born_family", "没有", me);
        } else
        {
                if (! objectp(obj = find_object(dest["startroom"])))
                        obj = load_object(dest["startroom"]);

                if (new_name)
                {
                        if (! sscanf(new_name, dest["surname"] + "%*s"))
                                new_name = dest["surname"] + new_name;

                        if (strlen(new_name) > 8)
                                return notify_fail("你的名字太长了。\n");

                        if (strlen(new_name) < 4)
                                return notify_fail("你的名字太短了。\n");

                        if (! is_chinese(new_name))
                                return notify_fail("请你用中文起名字。\n");
                }

                if( query("surname", me) != dest["surname"] )
                {
                        // 名字需要变化
                        NAME_D->remove_name(me->name(1),query("id", me));
                        if( !new_name)new_name=dest["surname"]+query("purename", me);
                        if (stringp(msg = NAME_D->invalid_new_name(new_name)))
                        {
                                write(msg);
                                write("你可以考虑在投入世家的时候重新选择名字：born <世家> <名字>\n");
                                return 1;
                        }
                        set("surname", dest["surname"], me);
                        set("purename", new_name[strlen(dest["surname"])..<1], me);
                        me->set_name();
                        NAME_D->map_name(me->name(1),query("id", me));
                }

                set("startroom", dest["startroom"], me);
                set("born", dest["born"], me);
                set("born_family", arg, me);

                if (mapp(dest["family"]))
                {
                        set("family", dest["family"], me);
                        me->assign_apprentice(dest["family"]["title"], 0);
                }
        }
        if (! objectp(obj))
        {
                message_vision("有个声音喃喃说道：怎么好像有问题...\n", me);
                return 1;
        }

        message_vision("一道金光闪过，$N消失得无影无踪。\n", me);
        
        foreach (item in all_inventory(me))
                if( !query("armor_type", item) )
                {
                        message_vision("$N丢下了$n。\n", me, item);
                        if( item->is_character() || query("value", item) )
                                item->move(environment(me));
                        else
                                destruct(item);
                }

        // 选择特殊技能
        UPDATE_D->born_player(me);

        me->move(obj);
        set("mud_age", 0, me);
        set("age", 14, me);
        me->save();
        HELP_CMD->main(me, "rules");
        message_vision("$N揉揉眼睛，迷惘的望着这个陌生的世界。\n", me);
        tell_object(me, HIY "新手导师：查看本人所在地的地图指令map，查看所有地图指令为map map\n" NOR);

        return 1;
}
