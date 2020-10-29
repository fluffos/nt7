// This program is a part of NT MudLIB

#include <ansi.h>

int main(object me, string arg)
{
        mapping buff_list,buff;
        string *lists, name;
        string msg;
        int i,time,warn_time,idx;
        object ob;
        
        mapping cont_list, vend_list;
        string *show_cont, color;
        mixed num;
        mixed busy_list;
        mixed data;
        string *bf;
        
        MYGIFT_D->check_mygift(me, "newbie_mygift/stat"); 

        if( arg && wizardp(me) )
        {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的状态？\n");
        } else
                ob = me;
        
        buff_list = query_temp("buff_list", ob);
        cont_list = ob->query_condition();
        vend_list = query("vendetta", ob);
        busy_list = ob->query_busy();
        
        msg  = WHT"\n当前状态\n"NOR;
        msg += HIR BLK"────────────────────────────────\n"NOR;

        if( (!mapp(buff_list) || !sizeof(buff_list)) && 
            (!mapp(cont_list) || !sizeof(cont_list)) && 
            (!mapp(vend_list) || !sizeof(vend_list)) &&
             !busy_list ) {
                msg += "没有任何异常状态作用中。\n";
                msg += HIR BLK"────────────────────────────────\n"NOR;
                write(msg);
                return 1;
        }
        
        seteuid(getuid());
        if( mapp(buff_list) && sizeof(buff_list) )
        {       lists = keys(buff_list);
                for( i=0; i<sizeof(lists); i++ )
                {
                        if( !sscanf(lists[i],"%d", idx) ) continue;
                        buff = query_temp("buff_list/"+lists[i], ob);
                        color = "";
                        if( buff["attr"] == "bless" )
                                color = CYN;
                        if( buff["attr"] == "curse" )
                                color = MAG;
        
                        msg += color+sprintf("%-22s", buff["name"])+NOR;
        
                        time = buff["time"];
                        warn_time = time / 40;
                        if( warn_time < 2 )
                                warn_time = 2;
                        time = time + query_temp("buff_time/"+lists[i], ob)-time();
                        /*
                        if( time < 0 ) {
                                BUFF_D->debuff(ob, buff["type"], buff["attr"]);
                                continue;
                        }
                        */

                        if( time > warn_time )
                                color = YEL;
                        else
                                color = RED;
                        msg += color+sprintf("%-9d%s%-4s",time,NOR,"秒");
                        
                        data = buff["buff_data"];
                        if( mapp(data) ) {
                                int j;
                                int value;

                                bf = keys(data);
                                for( j = 0; j<sizeof(bf); j++) { 
                                        value = data[bf[j]]; 
                                        msg += EQUIPMENT_D->chinese(bf[j], value); 
                                }
                                msg += "\n";
                        }
                        else
                        if( stringp(data) ) {
                                msg += data +"\n";
                        }
                        else
                                msg += "\n";
                }
        }
        
        if( mapp(cont_list) && sizeof(cont_list) )
        {
                msg += HIR BLK"────────────────────────────────\n"NOR;
                lists = keys(cont_list);
                num  = values(cont_list);
                for( i=0; i< sizeof(lists);i++ )
                {
                        num = cont_list[lists[i]];
                        if( !stringp(name = CONDITION_D(lists[i])->chinese_name()) )
                                name = CONDITION_D(lists[i])->name();
                        if( stringp(name) &&  mapp(num) && num["remain"]>0 )
                        {
                                msg += sprintf(MAG"%-22s%-9d次\n", name, num["remain"]);
                        }       
                        else
                        if( intp(cont_list[lists[i]]) )
                                msg += sprintf(MAG"%-22s%-9d次\n", lists[i], cont_list[lists[i]]);
                } 
        }       
        
        if( mapp(vend_list) && sizeof(vend_list) )
        {
                msg += HIR BLK"────────────────────────────────\n"NOR;
                lists = keys(vend_list);
                num  = values(vend_list); 
                for (i=0; i< sizeof(lists);i++)
                {
                        if(lists[i] == "shaolin" && num[i])
                                msg += sprintf(HIB"%-22s%-9d\n", "少林匪", num[i]);
                        else if(lists[i] == "authority" && num[i])
                                msg += sprintf(HIB"%-22s%-9d\n", "官匪", num[i]);
                        else if(lists[i] == "demon" && num[i])
                                msg += sprintf(HIB"%-22s%-9d\n", "魔教匪", num[i]);
                                                        
                } 
        }       

        if( busy_list )
        {
                msg += HIR BLK"────────────────────────────────\n"NOR;
                if( intp(busy_list) )
                        msg += sprintf(HIB"%-22s%-9d\n", "忙乱中", busy_list);
                else
                        msg += sprintf(HIB"%-22s%-9s\n", "忙乱中", "……");
        }
         
        msg += HIR BLK"────────────────────────────────\n"NOR;

        write(msg);
        return 1;
}


int help(object me)
{
write(@HELP

[0;1;37m────────────────────────────────────────────────────────────────[0m
指令格式 :     stat
[0;1;37m────────────────────────────────────────────────────────────────[0m   

这个指令可以让你知道你目前所拥有的所有异常状态与持续时间。

[0;1;37m────────────────────────────────────────────────────────────────[0m  
HELP
    );
    return 1;
}
 
 
