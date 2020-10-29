// This program is a part of NT MudLIB

#include <ansi.h>
 
int help(object me);
int update_viplevel(object me, int level);

mapping vip_levelup = 
([
        "vip1"  : 200,
        "vip2"  : 600,
        "vip3"  : 1500,         
        "vip4"  : 3000,
        "vip5"  : 5000,
        "vip6"  : 10000,
        "vip7"  : 20000,
        "vip8"  : 50000,
        "vip9"  : 90000,
]);

int main(object me, string arg)
{
        string arg1, arg2;
        int n, level, score;
        object ob;
        
        if( !arg ) return help(me);
        
        if( arg == "levelup" )
        {
                level = me->query_viplevel();
                if( sizeof(vip_levelup) <= level ) return notify_fail("已达到最高等级！\n");
                
                score = vip_levelup["vip" + sprintf("%d", level+1)];
                if( me->query_vipscore() < score )
                        return notify_fail("成长值不足，可通过充值商城币或特殊活动期间直接购买道具增加成长值！\n");
                           
                addn("vip/score", -1 * score, me);   
                addn("vip/level", 1, me);
                
                log_file("vip_uplevel", "玩家 " + me->query_idname() + " 升级为VIP" + sprintf("%d", me->query_viplevel()) + " at " + ctime(time()) + "\n");

                update_viplevel(me, level+1);
                
                return 1;
        }

        if( sscanf(arg, "show %s", arg) == 1 ||
            sscanf(arg, "check %s", arg) == 1 )
        {
                if( !wizardp(me) ) return 0;
                
                ob = UPDATE_D->global_find_player(arg); 
                
                if( !objectp(ob) ) 
                        return notify_fail("没有找到玩家：" + arg + "\n");    
                         
                help(ob);
                
                UPDATE_D->global_destruct_player(ob, 1);
                return 1;            
        }
                
        if( sscanf(arg, "addscore %s %d", arg, n) == 2 )
        {
                if( !SECURITY_D->valid_grant(this_player(), "(admin)" ))
                        return 0;
                
                ob = UPDATE_D->global_find_player(arg); 
                
                if( !objectp(ob) ) 
                        return notify_fail("没有找到玩家：" + arg + "\n");    
                
                if( n < -10000 || n > 10000 )
                        return notify_fail("输入金额须为-10000-10000之间。\n");
                        
                addn("vip/score", n, ob);
                
                log_file("vip_upscore", me->query_idname()+" 添加玩家 " + ob->query_idname() + " 成长值：" + sprintf("%d", n) + " at " + ctime(time()) + "\n");
                
                write("添加玩家 " + ob->query_idname() + " 成长值：" + sprintf("%d", n) + "\n");
                
                UPDATE_D->global_destruct_player(ob, 1);
                return 1;
        }
        
        return help(me);
        
}

int update_viplevel(object me, int level)
{
        object ob1, ob2, ob3, ob4;

        /*
        CHANNEL_D->channel_broadcast("news", HIG "恭喜" HIG + me->query_idname() + 
                HIG "VIP等级提升到" HIM + "VIP" + sprintf("%d", level) + HIG "。\n" NOR);
        */
        
        write(HIG "\n恭喜你升级为" HIM "VIP" + sprintf("%d", level) + HIG "，VIP福利请参见 help myvip\n" NOR);
        
        switch(level)
        {   
        case 1:
                addn("energy", 3, me);
                addn("ability", 5, me);
                set("vip/up1", 1, me);
                break;
        case 2:
                addn("energy", 3, me);
                addn("ability", 10, me);
                set("vip/up2", 1, me);
                break;
        case 3:
                addn("energy", 3, me);
                addn("ability", 15, me);
                set("vip/up3", 1, me);
                ob1 = new("/clone/goods/luck_charm");
                ob1->move(me, 1);
                write(HIC "获得" + ob1->name() + HIC "x1\n" NOR);     
                ob1 = new("/clone/goods/luck_neck");
                ob1->move(me, 1);
                write(HIC "获得" + ob1->name() + HIC "x1\n" NOR);     
                ob1 = new("/clone/goods/luck_ring");
                ob1->move(me, 1);
                write(HIC "获得" + ob1->name() + HIC "x1\n" NOR);     
                break;
        case 4:
                addn("energy", 3, me);
                addn("ability", 20, me);
                set("vip/up4", 1, me);
                ob1 = new("/clone/armor/zhanyao-xunzhang"); 
                ob1->move(me, 1);
                write(HIC "获得" + ob1->name() + HIC "x1\n" NOR);               
                
                ob2 = new("/clone/medal/vip_xunzhang"); 
                ob2->move(me, 1);
                write(HIC "获得" + ob2->name() + HIC "x1\n" NOR);               
                
                ob2 = new("/clone/medal/diamond_xunzhang"); 
                ob2->move(me, 1);
                write(HIC "获得" + ob2->name() + HIC "x1\n" NOR);               
                
                ob3 = new("/clone/medal/yongshi_xunzhang"); 
                ob3->move(me, 1);
                write(HIC "获得" + ob3->name() + HIC "x1\n" NOR);       
                
                ob4 = new("/clone/medal/daomu_xunzhang"); 
                ob4->move(me, 1);
                write(HIC "获得" + ob4->name() + HIC "x1\n" NOR);
                break;
        case 5:
                addn("energy", 3, me);
                addn("ability", 30, me);
                set("vip/up5", 1, me);
                addn("int", 5, me);
                addn("str", 5, me);
                addn("con", 5, me);
                addn("dex", 5, me);
                write(HIC "先天悟性，臂力，身法和根骨分别各永久增加5点！\n" NOR);
                break;
        case 6:
                addn("energy", 3, me);
                addn("ability", 50, me);
                set("vip/up6", 1, me);
                break;
        case 7:                    
                addn("energy", 12, me);
                addn("ability", 70, me);
                set("vip/up7", 1, me);
                break;  
        case 8:
                set("vip/up8", 1, me);
                write(HIM "拥有玄武护体神技。\n" NOR);
                write(HIY "拥有战神无敌神技。\n" NOR);
                write(HIR "浴血重生CD时间减少480秒。\n" NOR);
                break;
        case 9:
                set("vip/up9", 1, me);
                write(HIR "浴血重生CD时间减少540秒。\n" NOR);
                write(HIR "你的VIP等级达到至尊级别。\n" NOR);
                break;
        
        }
        
        return 1;
        
}

int help(object me)
{
        string str;
        int level;
        
        level = me->query_viplevel();
        
        str = HIY "\n==----------------VIP系统----------------==\n" NOR;
        str += "VIP 等  级：" + sprintf("%d", level) + "\n";
        str += "VIP 成长值：" + sprintf("%d", me->query_vipscore()) + "\n";
        
        if( sizeof(vip_levelup) < level )
        {
                str += "升级 所需：0\n";
        }
        else
        {
                str += "升级需消耗：" + sprintf("%d 点成长值", vip_levelup["vip" + sprintf("%d", level+1)]) + "\n";
        }
        
        str += HIY "==---------------------------------------==\n" NOR;
        str += HIC "指令：vip levelup 可升级VIP等级\n" NOR;
        str += HIG "每充值或直接购买1RMB可获得1点VIP成长值。\n" NOR;
        str += HIG "VIP相关福利请参见 help myvip\n" NOR;
 
        write(str);
        return 1;
}

