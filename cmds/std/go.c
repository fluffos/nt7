// go.c

#include <config.h>

inherit F_CLEAN_UP;

mapping default_dirs = ([
        "north":        "北方",
        "south":        "南方",
        "east":         "东方",
        "west":         "西方",
        "northup":      "北边",
        "southup":      "南边",
        "eastup":       "东边",
        "westup":       "西边",
        "northdown":    "北边",
        "southdown":    "南边",
        "eastdown":     "东边",
        "westdown":     "西边",
        "northeast":    "东北",
        "northwest":    "西北",
        "southeast":    "东南",
        "southwest":    "西南",
        "up":           "上面",
        "down":         "下面",
        "enter":        "里面",
        "out":          "外面",
]);

nosave mapping empty_mapping = ([ ]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string dest, mout, min, dir/*, blk, gud, skill*/, thing_msg;
        object env, obj/*, blocker*/, thing;
//      mapping block;
//      mixed old_target;
        int result;
//      int sen_cost;
        mapping exit;
        object *f_obs, *ob;
//      object temp_ob;
        mixed flee;
        mapping my, my_temp;
        mapping my_env, my_armor;
        object user;
        object *users;
        object riding;

//      int i,my_dex,count = 0;

        if (! arg) return notify_fail("你要往哪个方向走？\n");

        if (me->over_encumbranced() && userp(me))
                return notify_fail("你的负荷过重，动弹不得。\n");

        if (me->query_encumbrance() < 0 && userp(me))
                return notify_fail("你的负荷出现故障，动弹不得。\n");

        if( me->is_busy() || (query("doing", me) && query("doing", me) != "trigger") )
                return notify_fail("你的动作还没有完成，不能移动。\n");
        
        if( query_temp("is_riding_follow", me) )
                return notify_fail("你还是先下坐骑（ride down）后再移动。\n");
                
        env = environment(me);
        if (! env) return notify_fail("你哪里也去不了。\n");

        if (me->is_fighting())
        {
                me->clean_up_enemy();
                f_obs = me->query_enemy();
        } else
                f_obs = ({ });

        if( arrayp(ob=query_temp("guarded/"+arg, env)) )
                f_obs += ob;

        my = me->query_entire_dbase();
        my_temp = me->query_entire_temp_dbase();
        if (! my_temp) my_temp = empty_mapping;

        my_armor = my_temp["armor"];
        if (! my_armor) my_armor = empty_mapping;

        my_env = my["env"];
        if (! my_env) my_env = empty_mapping;

        if (sizeof(f_obs))
        {
                int fp, gp;
                int force_power;
                int target_power;
                object g_ob;

                fp  = (int)me->query_skill("dodge");
                fp += my["dex"] * 15;
                force_power = me->query_skill("force") + me->query_str() * 2;
                if (flee = my_temp["success_flee"])
                {
                        if (stringp(flee)) write(flee);
                        f_obs = ({ });
                }
                foreach (g_ob in f_obs)
                {
                        if (! g_ob) continue;
                        if (! living(g_ob) || g_ob == me) continue;

                        // calculate flee power & guard power
                        gp  = g_ob->query_skill("dodge");
                        gp += query("dex", g_ob) * 15;

                        if( !query("not_living", g_ob) && (fp / 2 + random(fp)) < (gp * 3 / 4) )
                        //等铜人统一后恢复上面判断公式
                        //if( 5+random(query("dex", me)) <= random(query("dex", g_ob)) )
                        {
                                me->start_busy(1);
                                if (me->is_fighting(g_ob))
                                {
                                        message_vision("$N见势不好，转身要走，"
                                                       "被$n一把拦在面前。想走"
                                                       "？可没那么容易！\n",
                                                       me, g_ob);
                                        tell_object(me, "你逃跑失败。\n");
                                } else
                                {
                                        message_vision("$N刚想离开，被$n一把"
                                                       "拦住：慢着！想打我这"
                                                       "儿过，没门！\n",
                                                       me, g_ob);
                                        tell_object(me, "你被拦住了去路。\n");
                                }

                                if (userp(g_ob))
                                {
                                        target_power=g_ob->query_skill("force")+g_ob->query_str()*2;

                                        /*
                                        if (userp(me))
                                                g_ob->want_kill(me);
                                        */

                                        if (force_power > target_power * 3)
                                        {
                                                message_vision("$N纵声长笑：“鼠辈！安敢欺吾？”说罢"
                                                               "往前一冲，将$n带出数步，跌倒在地。\n",
                                                               me, g_ob);
                                                g_ob->unconcious();
                                        } else
                                        if (force_power > target_power * 2)
                                        {
                                                message_vision("$N理都没有理$n，只是旁若无人往前走去"
                                                               "，将$n撞得鼻青脸肿。",
                                                               me, g_ob);
                                                g_ob->receive_wound("qi", 100 + random(100));
                                        } else
                                        if (force_power > target_power)
                                        {
                                                message_vision("$N一声冷笑，大踏步的向前冲"
                                                               "去，乓的一下将$n撞到了一边。",
                                                               me, g_ob);
                                                g_ob->receive_wound("qi", 50 + random(50));
                                        }
                                        // else
                                                // return 1;
                                } else
                                        return 1;
                                // 没有阻挡成功，继续前进
                        }
                }
        }
        map_delete(my_temp, "success_flee");

        if( !mapp(exit=query("exits", env)) || undefinedp(exit[arg]) )
        {
                if (query_verb() == "go")
                        notify_fail("这个方向没有出路。\n");
                return 0;
        }

        notify_fail("你过不去。\n");
        result = env->valid_leave(me, arg);
        if (! objectp(me))
                return 1;

        if (! result) return 0;
        if (result < 0 || environment(me) != env)
                // I needn't let the character do anymore,
                // because everything has been dong in the
                // fucntion::valid_leave()
                return 1;

        dest = exit[arg];
        if (! (obj = find_object(dest)))
                if (! objectp(obj = load_object(dest)))
                        return notify_fail(sprintf("目标物件无法找到，无"
                                                   "法向 %s 移动。\n", dest ) );
        
        if (function_exists("valid_enter", obj) && ! obj->valid_enter(me))
                return notify_fail(obj->short() + "那里现在不允许你进入。\n"); 

        /*
        if (my_temp["is_riding"] &&
            arg != "north"     && arg != "south" &&
            arg != "east"      && arg != "west" &&
            arg != "northeast" && arg != "southeast" &&
            arg != "northwest" && arg != "southwest")
        */
        if (objectp(riding = my_temp["is_riding"]) && member_array(arg, keys(default_dirs)) == -1)
                return notify_fail("这个方向没法骑在座骑上过去。\n");

        if (! undefinedp(default_dirs[arg]))
                dir = default_dirs[arg];
        else
        {
                if (stringp(env->query_room_id(arg)))
                        dir = env->query_room_id(arg);
                else
                        dir = arg;
        }

        if (me->is_fighting())
        {
                mout = me->name() + "往" + dir + "落荒而逃了。\n";
                min = me->name() + "跌跌撞撞地跑了过来，模样有些狼狈。\n";
        } else
        {
                //if (objectp(thing = my_armor["cloth"]))
                if (objectp(thing = me->query_equipped_object("cloth")))
                        thing_msg="身着"+query("name", thing);
                else
                if (userp(me))
                        thing_msg = "一丝不挂的";
                else
                        thing_msg = "";

                if (objectp(thing = my_temp["weapon"]))
                        thing_msg+="手执"+query("name", thing);

                if (my["race"] == "野兽")
                {
                        if( mout = query("leave_msg", me) )
                                mout = me->name() + "往" + dir + mout +" 。\n";
                        else
                                mout = me->name() + "呼地往" + dir + "一窜就消失了。\n";
                        if( min = query("arrive_msg", me) )
                                min = me->name() + min + " 。\n";
                        else
                                min = me->name() + "呼地窜了出来，警惕地四周张望着。\n";
                } else
                {
                        //if (objectp(riding = my_temp["is_riding"]))
                        if (objectp(riding))
                        {
                                mout = me->name() + "骑着" + riding->name() +
                                       "向" + dir + "疾驰而去。\n";
                                min = me->name() + thing_msg + "骑着" +
                                      riding->name() + "一路疾驰而来。\n";
                        } else
                        {
                                if( mout = query("leave_msg", me) )
                                        mout = me->name() + "往" + dir + mout +" 。\n";
                                else
                                        mout = me->name() + "往" + dir + "离开。\n";
                                if( min = query("arrive_msg", me) )
                                        min = me->name() + thing_msg + min + " 。\n";
                                else
                                        min = me->name() + thing_msg + "走了过来。\n";
                        }
                }
        }

        if (! wizardp(me) || ! my_env["invisible"])
                // message("vision", mout, environment(me), ({me}) );
        {
                users = filter_array(all_inventory(environment(me)), 
                                    (: (userp($1) || $1->want_receive_msg()) &&
                                    !query("env/no_moutmsg", $1):))-({me});
                if (sizeof(users) > 0)
                        foreach (user in users) 
                                message("tell_object", mout, user); 
        }

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif

        // move I to dest
        me->remove_all_enemy(1);
        map_delete(my_temp, "pending");
        if (objectp(obj) && ! my_env["invisible"])
                // message("vision", min, dest, ({ me }));
        {
                users = filter_array(all_inventory(obj), 
                                    (: (userp($1) || $1->want_receive_msg()) &&
                                    !query("env/no_minmsg", $1):))-({me});
                if (sizeof(users) > 0)
                        foreach (user in users) 
                                message("tell_object", min, user); 
        }

        me->move(dest);
        if (! objectp(me))
                return 1;

        if (objectp(riding)) 
        {
                object p_follow; 
                if (objectp(p_follow = query_temp("is_rided_follow", riding))) 
                {
                        if (environment(p_follow) && interactive(p_follow)) 
                                p_follow->move(dest); 
                }
                if (random(2)) me->improve_skill("riding", 1);
        }

        if (environment(me) != env)
        {
                object competitor;
                if (competitor = me->query_competitor())
                {
                        me->lost();
                        competitor->win();
                }
                if( objectp(env) )
                        all_inventory(env)->follow_me(me, arg);
                me->test_array();
                // me->check_team();
        }

        if (me->query_weak())
        {
                tell_object(me,"你虚弱的身体好像每迈出一步都要用出全身的力气。\n");
                me->start_busy(1);
        }               

        return 1;
}

void do_flee(object me)
{
        mapping exits;
        string *directions;

        if (! environment(me) || ! living(me)) return;
        exits=query("exits", environment(me));
        if (! mapp(exits) || ! sizeof(exits)) return;
        directions = keys(exits);
        tell_object(me, "看来该找机会逃跑了...\n");
        main(me, directions[random(sizeof(directions))]);
}

nosave mapping r_dirs = ([
        "north":        "south",
        "south":        "north",
        "east":         "west",
        "west":         "east",
        "northup":      "southdown",
        "southup":      "northdown",
        "eastup":       "westdown",
        "westup":       "eastdown",
        "northdown":    "southup",
        "southdown":    "northup",
        "eastdown":     "westup",
        "westdown":     "eastup",
        "northeast":    "southwest",
        "northwest":    "southeast",
        "southeast":    "northwest",
        "southwest":    "northeast",
        "up":           "down",
        "down":         "up",
        "enter":        "out",
        "out":          "enter",
]);

string query_reverse(string dir)
{
        if (undefinedp(r_dirs[dir]))
                return 0;

        return r_dirs[dir];
}

string query_chinese_dir(string dir)
{
        return default_dirs[dir];
}

int help(object me)
{
        write(@HELP
指令格式 : go <方向>
 
让你往指定的方向移动。
 
HELP );
        return 1;
}