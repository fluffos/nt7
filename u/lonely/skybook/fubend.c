// 副本系统控制文件
#define MEMBER_D          "/adm/daemons/memberd"

#include <ansi.h>

void move_all_invalid_user(object me); //移出
int move_next_fb_room(object me, object ob_room, string into_msg, string into_msg_team, string fb_name, object last_room);

// 副本重置时间
mapping fb_reset_time = ([
        "天机"              : 6 * 3600,
        "布达拉宫宝藏"      : 6 * 3600,
        
]);

// 移动到指定副本 将当前PLAYER或PLAYER为首的队伍移动到新的副本场景
// me, 新副本OB，单人进入提示，组队进入提示
// 参数nWhere = 1代表从存档点进入 为0代表在副本中移动
// nWhere_save_point 代表存档点 如 /fuben/天机/save/冰火岛西岸
int move_new_fb(object me, object ob_room, string into_msg, string into_msg_team, string fb_name, int nWhere, string nWhere_save_point)
{
        object *t;
        object ob;
        object ob_shensheng, ob_huoyan;
        
        if (! objectp(me))return 0;
        if (! objectp(ob_room))return 0;        
        
        t = me->query_team();

        if (! MEMBER_D->is_valib_member(me->query("id")))
        {
                tell_object(me, "你还是非会员，无法进入副本！\n");
                return 1;
        }
        if (! me->query("scborn/ok"))
        {
                tell_object(me, "你还未转世，无法进入副本！\n");
                return 1;                       
        }
        
        if (me->query("combat_exp") < 10000000)
        {
                tell_object(me, "你实战经验不足，无法进入副本！\n");
                return 1;                               
        }

        // 未开启该副本则不能参与
        if (! me->query("fuben/" + fb_name + "/open"))
        {
                tell_object(me, "你还未开启" + fb_name + "副本，无法进入！\n");
                return 1;
        }

        // 代表在副本中移动
        if (! nWhere)
        {
                return move_next_fb_room(me, ob_room, into_msg, into_msg_team, fb_name, 0);
        }
        
        // 检查该玩家或组队玩家身上是否有其他玩家，有则任何人均不可进入
        if (! arrayp(t))
        {
        }
        t -= ({ 0 });
        if (! me->is_team_leader() || sizeof(t) < 1)
        {
        }
        else
        {
        }
        
        // 如果是从存档点进入，开启副本后再次从头进入也算是从存档点进入
        if (nWhere == 1)
        {
                // 没有该存档点则无法进入
                if (! me->query(nWhere_save_point))
                {
                        tell_object(me, "你没有该存档点，无法进入！\n");
                        return 1;
                }
        }
        
        // 查询上次进入副本的重置时间
        if (time() - me->query("fuben/" + fb_name + "/last_join_time")  < fb_reset_time[fb_name])
        {
                tell_object(me, "你距离上次进入" + fb_name + "副本的时限不够，无法进入， 指令 fb list 可查看详细情况。\n");
                return 1;
        }

        // 身上火焰之晶不足，则无法进入
        if (! me->query("fuben/" + fb_name + "/first_open"))
        {
                if (! objectp(ob_huoyan = present("huoyan zhijing", me)))
                {
                        tell_object(me, "你身上没有火焰之晶，无法从存档点或重新进入副本。\n");
                        return 1;
                }
        }
        else // 开启副本成功后，首次进入不扣除火焰之晶
        {
                
        }
                
        if (! arrayp(t))
        {               
                // 身上火焰之晶不足，则无法进入
                if (! me->query("fuben/" + fb_name + "/first_open"))
                {
                        if (! objectp(ob_huoyan = present("huoyan zhijing", me)))
                        {
                                tell_object(me, "你身上没有火焰之晶，无法从存档点或重新进入副本。\n");
                                return 1;
                        }
                        destruct(ob_huoyan);
                }
                else // 开启副本成功后，首次进入不扣除火焰之晶
                {
                        me->set("fuben/" + fb_name + "/first_open", 0);
                }
                                
                tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);
                
                me->move(ob_room);
                // 设置进入副本时间
                me->set("fuben/" + fb_name + "/last_join_time", time());
                me->save();
                return 1;
        }

        t -= ({ 0 });
        if (! me->is_team_leader() || sizeof(t) < 1)
        {
                // 身上火焰之晶不足，则无法进入
                if (! me->query("fuben/" + fb_name + "/first_open"))
                {
                        if (! objectp(ob_huoyan = present("huoyan zhijing", me)))
                        {
                                tell_object(me, "你身上没有火焰之晶，无法从存档点或重新进入副本。\n");
                                return 1;
                        }
                        destruct(ob_huoyan);
                }
                else // 开启副本成功后，首次进入不扣除火焰之晶
                {
                        me->set("fuben/" + fb_name + "/first_open", 0);
                }               

                tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);
                
                me->move(ob_room);
                // 设置进入副本时间
                me->set("fuben/" + fb_name + "/last_join_time", time());
                me->save();
                return 1;               
        }

        foreach ( ob in t)
        {
                if (! MEMBER_D->is_valib_member(ob->query("id")))
                {
                        tell_object(ob, "非会员，无法进入副本！\n");
                        continue;
                }
                if (! ob->query("scborn/ok"))
                {
                        tell_object(ob, "你还未转世，无法进入副本！\n");
                        continue;
                }
                if (ob->query("combat_exp") < 10000000)
                {
                        tell_object(ob, "你实战经验不足，无法进入副本！\n");    
                        continue;                       
                }
                // 未开启该副本则不能参与
                if (! ob->query("fuben/" + fb_name + "/open"))
                {
                        tell_object(ob, "你还未开启" + fb_name + "副本，无法进入！\n");
                        return 1;
                }

                // 如果已经开启了该副本，从头进入则算作从存档点进入
                if (! nWhere)
                {
                        if (ob->query("fuben/" + fb_name + "/open"))
                        {
                                nWhere = 1;
                                nWhere_save_point = "/fuben/" + fb_name + "/save/重新开始";
                        }
                }
                // 如果是从存档点进入
                if (nWhere == 1)
                {
                        // 没有该存档点则无法进入
                        if (! ob->query(nWhere_save_point))
                        {
                                tell_object(ob, "你没有该存档点，无法进入！\n");
                                continue;
                        }
                }       
                
                // 查询上次进入副本的重置时间
                if (time() - ob->query("fuben/" + fb_name + "/last_join_time")  < fb_reset_time[fb_name])
                {
                        tell_object(ob, "你距离上次进入" + fb_name + "副本的时限不够，无法进入， 指令 fb list 可查看详细情况。\n");
                        continue;
                }

                // 身上火焰之晶不足，则无法进入
                if (! ob->query("fuben/" + fb_name + "/first_open"))
                {
                        if (! objectp(ob_huoyan = present("huoyan zhijing", ob)))
                        {
                                tell_object(ob, "你身上没有火焰之晶，无法从存档点或重新进入副本。\n");
                                continue;
                        }
                        destruct(ob_huoyan);
                }
                else // 开启副本成功后，首次进入不扣除火焰之晶
                {
                        ob->set("fuben/" + fb_name + "/first_open", 0);                 
                }

                tell_object(ob, HIG "\n组队：" + into_msg_team + "\n\n" NOR);
                
                ob->move(ob_room);
                // 设置进入副本时间
                ob->set("fuben/" + fb_name + "/last_join_time", time());
                ob->save();
        }
        return 1;
}
// 副本中移动，用于将指定队长及所有队伍成员一起移动到下一房间
int move_next_fb_room(object me, object ob_room, string into_msg, string into_msg_team, string fb_name, object last_room)
{
        object *t;
        object ob;
        
        if (! objectp(me))return 0;
        if (! objectp(ob_room))return 0;        
        
        t = me->query_team();

        if (! arrayp(t))
        {
                tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);

                me->move(ob_room);
                
                if (objectp(last_room))destruct(last_room);
                
                return 1;
        }

        t -= ({ 0 });
        if (! me->is_team_leader() || sizeof(t) < 1)
        {

                tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);
                
                me->move(ob_room);

                if (objectp(last_room))destruct(last_room);
                
                return 1;               
        }

        foreach ( ob in t)
        {

                tell_object(ob, HIG "\n组队：" + into_msg_team + "\n\n" NOR);
                
                ob->move(ob_room);

        }
        
        if (objectp(last_room))destruct(last_room);
        return 1;
}

// 挑战BOSS -- HELP BOSS，用于将指定队长及所有队伍成员一起移动到下一房间
// time_limit 时间限制，表示该BOSS副本限制time_limit内只能挑战一次
int move_boss_fb_room(object me, object ob_room, string into_msg, string into_msg_team, string fb_name, object last_room, int time_limit, int cost)
{
        object *t;
        object ob;
        
        if (! objectp(me))return 0;
        if (! objectp(ob_room))return 0;        
        
        t = me->query_team();

        if (! arrayp(t))
        {
                if (time() - me->query(fb_name + "/last_time") < time_limit)
                {
                        tell_object(me, HIG "\n你还需要再等待" + sprintf("%d", time_limit + me->query(fb_name + "/last_time") -time()) + 
                                              "秒后才能再次进入该空间！\n" NOR);
                        return 1;
                }
                
                if (me->query("stocks/balance") < cost)
                {
                        tell_object(me, HIG "\n你无法支付进入空间的费用，将被阻止进入空间。\n" NOR);
                        return 1;
                }
                else
                {
                        me->add("stocks/balance", -1 * cost);
                        me->save();
                }
                
                tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);

                move_all_invalid_user(me);
                
                me->move(ob_room);
                me->set(fb_name + "/last_time", time());

                if (ob_room->query("id") == "huashan zhidian")
                        MYGIFT_D->check_mygift(me, "newbie_mygift/joinfuben");
                
                me->save();
                if (objectp(last_room))destruct(last_room);
                
                return 1;
        }

        t -= ({ 0 });
        if (! me->is_team_leader() || sizeof(t) < 1)
        {

                if (time() - me->query(fb_name + "/last_time") < time_limit)
                {
                        tell_object(me, HIG "\n你还需要再等待" + sprintf("%d", time_limit + me->query(fb_name + "/last_time") -time()) + 
                                              "秒后才能再次进入该空间！\n" NOR);
                        return 1;
                }
                
                if (me->query("stocks/balance") < cost)
                {
                        tell_object(me, HIG "\n你无法支付进入空间的费用，将被阻止进入空间。\n" NOR);
                        return 1;
                }
                else
                {
                        me->add("stocks/balance", -1 * cost);
                        me->save();
                }
                                
                tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);
                
                move_all_invalid_user(me);
                
                me->move(ob_room);
                me->set(fb_name + "/last_time", time());
                
                if (ob_room->query("id") == "huashan zhidian")
                        MYGIFT_D->check_mygift(me, "newbie_mygift/joinfuben");
                
                
                me->save();
                if (objectp(last_room))destruct(last_room);
                
                return 1;               
        }

        // 首先判断队长是否可以进入，如果队长不能进入则整个队伍不能进入

        if (time() - me->query(fb_name + "/last_time") < time_limit)
        {
                tell_object(me, HIG "\n你还需要再等待" + sprintf("%d", time_limit + me->query(fb_name + "/last_time") -time()) + 
                                      "秒后才能再次进入该空间！\n" NOR);
                return 1;
        }
        if (me->query("stocks/balance") < cost)
        {
                tell_object(me, HIG "\n你无法支付进入空间的费用，将被阻止进入空间。\n" NOR);
                return 1;
        }

        foreach ( ob in t)
        {
                // 非队长重新计算time_limit
                if (! ob->is_team_leader())
                {
                        object obj;
                        mapping boss_list;
                        string *keys_boss_list;
                        int new_time_limit;
                        
                        if (! objectp(obj = find_object("/kungfu/class/misc/fuben/boss/jieyinshi")))
                                obj = load_object("/kungfu/class/misc/fuben/boss/jieyinshi");
                        
                        boss_list = obj->show_time_delay(1);
                        keys_boss_list = explode(boss_list[fb_name], ":");
                        sscanf(keys_boss_list[3], "%d", new_time_limit);
                        time_limit = new_time_limit * 3600;
                        
                        // vip缩短冷却时间
                        switch(ob->GetVipLevel())
                        {
                        case 1:
                                time_limit = time_limit - time_limit / 10;
                        break;
                        case 2:
                                time_limit = time_limit - time_limit * 2 / 10;
                        break;
                        case 3:
                                time_limit = time_limit - time_limit * 3 / 10;  
                        break;
                        case 4:
                                time_limit = time_limit - time_limit * 4 / 10;  
                        break;
                        case 5:
                                time_limit = time_limit - time_limit * 5 / 10;  
                        break;
                        case 6:
                                time_limit = time_limit - time_limit * 6 / 10;  
                        break;                                  
                        }
                        // 酷爽夏日活动
                        if (MEMBER_D->ifdatein("2013-5-25", "2013-6-20") == 1)
                        {
                                time_limit /= 2;
                        }
                        
                }

                if (time() - ob->query(fb_name + "/last_time") < time_limit)
                {
                        tell_object(ob, HIG "\n你还需要再等待" + sprintf("%d", time_limit + ob->query(fb_name + "/last_time") -time()) + 
                                              "秒后才能再次进入该空间！\n" NOR);
                        continue;
                }
                
                if (ob->query("stocks/balance") < cost)
                {
                        tell_object(ob, HIG "\n你无法支付进入空间的费用，将被阻止进入空间。\n" NOR);
                        continue;
                }
                else
                {
                        ob->add("stocks/balance", -1 * cost);
                        ob->save();
                }

                tell_object(ob, HIG "\n组队：" + into_msg_team + "\n\n" NOR);
                
                move_all_invalid_user(ob);
                
                ob->move(ob_room);
                ob->set(fb_name + "/last_time", time());
                
                if (ob_room->query("id") == "huashan zhidian")
                        MYGIFT_D->check_mygift(ob, "newbie_mygift/joinfuben");
                
                ob->save();
        }
        
        if (objectp(last_room))destruct(last_room);
        return 1;
}

void move_all_invalid_user(object me)
{
        int i;
        object *inv;

                        
        // 把背起的用户放下来
        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人背起的用户
                inv[i]->move(environment(me));                
        }
        
}

// 单人副本，只移动当前player,身上，背上，和组队中的player均不移动
int move_lonely_fb_room(object me, object ob_room, string into_msg, string into_msg_team, string fb_name)
{
        object ob;
        
        if (! objectp(me))return 0;
        if (! objectp(ob_room))return 0;        
        
        tell_object(me, HIG "\n" + into_msg + "\n\n" NOR);

        // 移除所有非法连带用户
        move_all_invalid_user(me);

        me->move(ob_room);
        me->save();
        
        return 1;


        return 1;
}
