// ride.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_ride(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, env;
        object horse, person;
        string who, s1, s2;
        int i, level, rec_n, max_rec;
        mapping self_flag;
        string *ps;

        if( !arg ) return notify_fail("你要骑什么东西？\n");
        
        env = environment(me);
        // 邀请人上坐骑
        sscanf(arg, "%s %s", s1, s2);
        if( s1 == "up" ) // s1 == arg;
        {
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return notify_fail("对不起，只有会员才能邀请别人上坐骑。\n");

                if( sscanf(arg, "up %s", who) == 1 )
                {
                        if( !objectp(horse=query_temp("is_riding", me)) )
                                return notify_fail("你连坐骑都没有，怎么要求别人上坐骑？\n");

                        if( !objectp(person = present(who, env)) )
                                return notify_fail("这里没有这个人！\n");

                        if( query_temp("is_riding", person) )
                                return notify_fail("别人已经有坐骑了。\n");

                        if( objectp(query_temp("is_rided_follow", horse)) )
                                return notify_fail("你的坐骑上已经有人了。\n");

                        message_vision(HIW "$N勒坐骑于前，对$n说道：请上坐骑一叙！\n" NOR, me, person);
                        set_temp("ride_up",query("id", me), person);
                        tell_object(person, HIG + me->name() + "邀请你上坐骑，如果同意请输入 ride ok 。\n" NOR);                  
                        return 1;
                }

                return notify_fail("你要邀请谁上坐骑？\n");
        }

        // 同意邀请上坐骑
        if( arg == "ok" )
        {
                if( !stringp(who=query_temp("ride_up", me)) )
                        return notify_fail("没有人邀请你上坐骑。\n");

                if( query_temp("is_riding_follow", me) )
                        return notify_fail("你还是先下坐骑（ride down）再说吧。\n");
        
                person = find_player(who);
        
                if( !objectp(person) ) return notify_fail("这里没有这个人。\n");

                if( environment(me) != environment(person) )
                        return notify_fail("这里没有这个人。\n");
                
                if( !objectp(horse=query_temp("is_riding", person)) )
                        return notify_fail(person->name() + "似乎没有坐骑吧！\n");

                if( query_temp("is_rided_follow", horse) )
                        return notify_fail(person->name() + "的" + horse->name() + NOR "已经有人在乘坐了。\n");

                delete_temp("ride_up", me);
                MAP_D->me_ride(me, horse);
                
                return 1;
                
        }
        
        // follower 强行下坐骑
        if( arg == "down" )
        {
                if( objectp(horse=query_temp("is_riding_follow", me)) )
                {
                        delete_temp("is_riding_follow", me);
                        delete_temp("is_rided_follow", horse);
                
                        message_vision("$N一翻身， 从" + horse->name() + NOR "跳了下来。\n" NOR, me);

                        return 1;
                }
                
                return notify_fail("OK.\n");            
        }

        if (arg == "kick")
        {
                if( objectp(horse=query_temp("is_riding", me)) )
                {                       
                        if( objectp(person=query_temp("is_rided_follow", horse)) )
                                delete_temp("is_riding_follow", person);

                        delete_temp("is_rided_follow", horse);

                        message_vision("$N强行要求所有人下坐骑。\n", me);

                        return 1;               
                }

                return notify_fail("你并没有骑坐骑。\n"); 
        }
        
        if( arg == "?" )
        {
                self_flag = query("horse/flags", me);
                if( mapp(self_flag) && sizeof(self_flag) )
                {
                        ps = keys(self_flag);
                        for (i = 0; i < sizeof(ps); i ++)
                                write(sprintf(HIG "%-20s%-20s\n" NOR, ps[i], get_object(self_flag[ps[i]])->short()));
                } else
                        write("你目前没有记录地点。\n");

                return 1;
        }

        if( sscanf(arg, "rec %s", who) == 1 )
        {
                env = environment(me);

                // 判断记录是否已经超过限制
                if( !MEMBER_D->is_valid_member(query("id", me))) max_rec = 0;
                else
                {
                        level = MEMBER_D->db_query_member(me, "vip");
                        switch( level )
                        {
                                case 3:
                                        max_rec = 4;
                                        break;
                                case 2:
                                        max_rec = 3;
                                        break;
                                case 1:
                                        max_rec = 2;
                                        break;
                                default:
                                        max_rec = 1;
                                        break;                          
                        }
                }

                rec_n=sizeof(query("horse/flags", me));
                max_rec+=query("horse/stone", me);

                if( rec_n >= max_rec )
                {
                        write(HIR "你的记录已达到 " + sprintf("%d", rec_n) + " 条，已满！\n" NOR);
                        write(HIR "你可以尝试使用以献锞径来增加你的记录数：\n\n" NOR);

                        write(HIC "普通玩家：         Max = 0 条\n" NOR);
                        write(HIM "普通会员：         Max = 1 条\n" NOR);
                        write(WHT "白银会员：         Max = 2 条\n" NOR);
                        write(HIY "黄金会员：         Max = 3 条\n" NOR);
                        write(HIW "白金会员：         Max = 4 条\n" NOR);
                        write(HIG "册 坐骑 石：         每个册坐骑石增加 1 条 Max\n" NOR);
                        
                        return 1;
                }
 
                if( !objectp(horse=query_temp("is_riding", me)) )
                        return notify_fail("你还是先找匹坐骑再说吧？\n"); 

                if( stringp(MAP_D->get_trans_path(who)) )
                        return notify_fail("对不起，编号 " + who + " 已经存在，请另取一个编号。\n");

                if( stringp(query("horse/flags/"+who, me)) )
                        return notify_fail("对不起，编号 " + who + " 已经存在，请另取一个编号。\n");

                // 如果房间没有出口不能记录
                if( !sizeof(query("exits", env)) )
                        return notify_fail("此地点不能记录。\n");

                // no_magic 不能记录
                if( query("no_magic", env) || query("maze", env) )
                        return notify_fail("此地点不能记录。\n");

                if( clonep(env) || !env->is_room() || query("no_rideto", env) )
                        return notify_fail("此地点不能记录。\n");

                if( domain_file(base_name(environment(me))) == "city2" )
                        return notify_fail("此地点不能记录。\n");

                if( sscanf(base_name(environment(me)), "/data/%*s" ) ||
                    sscanf(base_name(environment(me)), "/d/newbie/%*s" ) ||
                    sscanf(base_name(environment(me)), "/d/city2/%*s" ) ||
                    sscanf(base_name(environment(me)), "/d/death/%*s" ) ||
                    sscanf(base_name(environment(me)), "/d/dongtian/%*s" ) ||
                    sscanf(base_name(environment(me)), "/maze/%*s" ) ||
                    sscanf(base_name(environment(me)), "/f/%*s" ) )
                        return notify_fail("此地点不能记录。\n");

                //if( !query("outdoors", env) )
                //        return notify_fail("此地点不能记录。\n");
                        
                set("horse/flags/"+who, base_name(env), me);
                //me->save();
                write(HIG "记录成功！\n" NOR);

                return 1;

        } 

        if( sscanf(arg, "unrec %s", who) == 1 )
        {
                if( !objectp(horse=query_temp("is_riding", me)) )
                        return notify_fail("你还是先找匹坐骑再说吧？\n"); 

                if( !stringp(query("horse/flags/"+who, me)) )
                        return notify_fail("对不起，编号 " + who + " 不存在，请使用 rideto 查看。\n");

                delete("horse/flags/"+who, me);
                me->save();

                write(HIG "删除记录成功。\n" NOR);

                return 1;
                
        }
        
        if( query_temp("is_riding", me) )
                return notify_fail("你已经有座骑了！\n");

        if( query_temp("is_riding_follow", me) )
                return notify_fail("你先下马（ride down）再说吧！\n");

        if( me->is_busy() )
                return notify_fail("你上一个动作还没有完成！\n");

        if( me->is_fighting() )
                return notify_fail("你还在战斗中！没空骑上去。\n");

        // Check if a container is specified.

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("你没有这样东西可骑。\n");

        if( !query("ridable", obj) )
                return notify_fail("这个东西你也要骑？当心你的屁股！\n");

        if( query("owner", obj) && query("owner", obj) != query("id", me) )
                return notify_fail("它已经有主人了，你无法驾驭它！\n");

        return do_ride(me, obj);
        write("骑上去了。\n");
}

int do_ride(object me, object obj)
{
        object /*old_env,*/ *guard;

        if( !obj ) return 0;

        if( guard=query_temp("guarded", obj)){
                guard = filter_array(guard, (: objectp($1) && present($1, environment($2)) && living($1) && ($1!=$2) :), me);
                if( sizeof(guard) )
                        return notify_fail( guard[0]->name()
                                + "正守在" + obj->name() + "一旁，防止任何人骑走。\n");
        }

        obj->set_weight(1);
        if( obj->move(me) )
        {
                message_vision( "$N飞身跃上$n，身手很是矫捷。\n", me, obj );
                set_temp("is_rided_by", me, obj);
                set_temp("is_riding", obj, me);
        }
        else
        {
                message_vision( "$N身上带的东西太重了，无法骑到$n身上去。\n", me, obj );
        }

        return 1;
}

int help(object me)
{
	write(@HELP
指令格式 :

ride <生物名>        骑上代步的已驯养的动物。
ride up <id>         邀请别人上马（会员指令）。
ride ok              同意别人的邀请。
ride down            从别人的马上下马（此指令是专为同乘他人的马的玩家设置的）。
ride kick            让马上的同乘者下马。            
ride rec <代号>      可以让你记录当前地点到rideto列表中去，以后可以直接骑上马
                     使用 rideto <代号> 到达这个地方。

                     普通玩家：               可记录 0 条。
                     普通会员：		      可记录 1 条。
                     白银会员：		      可记录 2 条。
                     黄金会员：		      可记录 3 条。
                     白金会员：		      可记录 4 条。
                     使用册马石一次：	      可增加最大可记录空间 1 条。

ride unrec <代号>    删除指令代号的记录。
                       
HELP
    );
    return 1;
}